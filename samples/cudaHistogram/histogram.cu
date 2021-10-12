
/**
 * Based on CUB histogram code: https://github.com/NVlabs/cub/tree/master/experimental/histogram
 */

#include <stdio.h>
#include "histogram.h"

// First-pass histogram kernel (binning into privatized counters)
template <
    int         NUM_PARTS,
    int         NUM_BINS>
__global__ void histogram_smem_atomics(
    CUsurfObject surface,
    unsigned int width,
    unsigned int height,
    unsigned int *out)
{
    // global position and size
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int nx = blockDim.x * gridDim.x;
    int ny = blockDim.y * gridDim.y;

    // threads in workgroup
    int t = threadIdx.x + threadIdx.y * blockDim.x; // thread index in workgroup, linear in 0..nt-1
    int nt = blockDim.x * blockDim.y; // total threads in workgroup

    // group index in 0..ngroups-1
    int g = blockIdx.x + blockIdx.y * gridDim.x;

    // initialize smem
    __shared__ unsigned int smem[NUM_BINS];
    for (int i = t; i < NUM_BINS; i += nt)
        smem[i] = 0;

    // process pixels (updates our group's partial histogram in smem)
    for (int col = x; col < width; col += nx)
    {
        for (int row = y; row < height; row += ny)
        {
            uchar1 data;
            surf2Dread(&data, surface, col, row);

            atomicAdd(&smem[((unsigned int)data.x) % NUM_BINS], 1);
        }
    }

    __syncthreads();

    // move to our workgroup's slice of output
    out += g * NUM_PARTS;

    // store local output to global
    for (int i = t; i < NUM_BINS; i += nt)
    {
        out[i] = smem[i];
    }
}

// Second pass histogram kernel (accumulation)
template <
    int         NUM_PARTS,
    int         NUM_BINS>
__global__ void histogram_smem_accum(
    const unsigned int *in,
    int n,
    unsigned int *out)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i > NUM_BINS)
        return; // out of range

    unsigned int total = 0;
    for (int j = 0; j < n; j++)
        total += in[i + NUM_PARTS * j];

    out[i] = total;
}

template <
    int         NUM_BINS>
float run_smem_atomics(
    CUsurfObject surface,
    unsigned int width,
    unsigned int height,
    unsigned int *h_hist)
{
    enum
    {
        NUM_PARTS = 1024
    };
    cudaError_t err = cudaSuccess;
    dim3 block(32, 4);
    dim3 grid(16, 16);
    int total_blocks = grid.x * grid.y;

    // allocate device histogram
    unsigned int *d_hist;
    err = cudaMalloc(&d_hist, NUM_BINS * sizeof(unsigned int));
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device d_hist (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    // allocate partial histogram
    unsigned int *d_part_hist;
    err = cudaMalloc(&d_part_hist, total_blocks * NUM_PARTS * sizeof(unsigned int));
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device d_part_hist (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    dim3 block2(128);
    dim3 grid2((NUM_BINS + block.x - 1) / block.x);

    cudaEvent_t start;
    cudaEvent_t stop;

    cudaEventCreate(&stop);
    cudaEventCreate(&start);

    cudaEventRecord(start, 0);

    histogram_smem_atomics<NUM_PARTS, NUM_BINS><<<grid, block>>>(
        surface,
        width,
        height,
        d_part_hist);
    err = cudaGetLastError();
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch histogram_smem_atomics kernel (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    histogram_smem_accum<NUM_PARTS, NUM_BINS><<<grid2, block2>>>(
        d_part_hist,
        total_blocks,
        d_hist);
    err = cudaGetLastError();
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch histogram_smem_accum kernel (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    cudaEventRecord(stop, 0);

    cudaEventSynchronize(stop);
    float elapsed_millis;
    cudaEventElapsedTime(&elapsed_millis, start, stop);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    err = cudaMemcpy(h_hist, d_hist, NUM_BINS * sizeof(unsigned int), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy into h_hist (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaFree(d_part_hist);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector d_part_hist (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaFree(d_hist);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector d_hist (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    return elapsed_millis;
}

float histogram(CUsurfObject surface, unsigned int width, unsigned int height,
    unsigned int *histogram)
{
    return run_smem_atomics<HISTOGRAM_BINS>(surface, width, height, histogram);
}

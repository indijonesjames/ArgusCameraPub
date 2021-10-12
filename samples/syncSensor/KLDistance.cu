
#ifndef _KLDISTANCE_KERNEL_H_
#define _KLDISTANCE_KERNEL_H_

#include <stdio.h>
#include "KLDistance.h"

/**
 * CUDA Kernel Device code
 *
 * Computes the KL ratio from probability ratios.
 *
 */
__global__ void
vectorKLRatio(const unsigned int *A,
              const unsigned int *B,
              float *C,
              const int numElements,
              const int size)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements)
    {
        float a = A[i];
        float b = B[i];
        a = a/(float)size;
        b = b/(float)size;
        if ( b == 0.0f) b+= .0001; // add sigma
        if ( a != 0)
            C[i] = a * log(a/b);
        else
            C[i] = 0.0f;
    }
}

float computeKLDistance(unsigned int *histOne,
                        unsigned int *histTwo,
                        const unsigned int bins,
                        const unsigned int size,
                        float *distance)
{
    cudaError_t err = cudaSuccess;
    int threadsPerBlock = 256;
    int blocksPerGrid =(bins + threadsPerBlock - 1) / threadsPerBlock;

    cudaEvent_t start;
    cudaEvent_t stop;

    cudaEventCreate(&stop);
    cudaEventCreate(&start);

    cudaEventRecord(start, 0);
    unsigned int *d_histOne = NULL;
    err = cudaMalloc((void **)&d_histOne, bins * sizeof(int));
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device histOne (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    unsigned int *d_histTwo = NULL;
    err = cudaMalloc((void **)&d_histTwo, bins * sizeof(int));
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device histTwo (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Allocate the ratio bins
    float *ratio = NULL;
    err = cudaMalloc((void **)&ratio, bins * sizeof(float));
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector ratio (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_histOne, histOne, bins, cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy into device vector histOne (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_histTwo, histTwo, bins, cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy into device vector histTwo (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    vectorKLRatio<<<blocksPerGrid, threadsPerBlock>>>(d_histOne, d_histTwo, ratio, bins, size);
    err = cudaGetLastError();
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    float *dispRatio = (float *)malloc(bins * sizeof(float));
    err = cudaMemcpy(dispRatio, ratio, bins * sizeof(float), cudaMemcpyDeviceToHost);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy into device vector dispRatio (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // just sum up the vector.
    *distance = 0.0f;
    for (unsigned int i = 0; i < bins; ++i)
    {
        *distance += dispRatio[i];
    }

    err = cudaFree(d_histOne);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector histOne (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaFree(d_histTwo);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector histTwo (error code %s)!\n",
                         cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaFree(ratio);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector ratio (error code %s)!\n",
                        cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    free(dispRatio);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsed_millis;
    cudaEventElapsedTime(&elapsed_millis, start, stop);
    return elapsed_millis;
}
#endif

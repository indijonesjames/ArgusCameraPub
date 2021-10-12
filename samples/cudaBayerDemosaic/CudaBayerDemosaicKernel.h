
#ifndef CUDA_BAYER_DEMOSAIC_KERNEL_H
#define CUDA_BAYER_DEMOSAIC_KERNEL_H

#include <cuda.h>

extern int cudaBayerDemosaic(CUdeviceptr bayerSrc,
                             int bayerWidth,
                             int bayerHeight,
                             int bayerPitch,
                             int bayerFormat,
                             CUdeviceptr rgbaDst);

#endif // CUDA_BAYER_DEMOSAIC_KERNEL_H

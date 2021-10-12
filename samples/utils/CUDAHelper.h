
#ifndef CUDAHELPER_H
#define CUDAHELPER_H

#include <cuda.h>
#include <cudaEGL.h>

#ifndef CU_EGL_COLOR_FORMAT_BAYER_RGGB
#define CU_EGL_COLOR_FORMAT_BAYER_RGGB (0x2D)
#define CU_EGL_COLOR_FORMAT_BAYER_BGGR (0x2E)
#define CU_EGL_COLOR_FORMAT_BAYER_GRBG (0x2F)
#define CU_EGL_COLOR_FORMAT_BAYER_GBRG (0x30)
#endif

#ifndef CU_EGL_COLOR_FORMAT_YUV422_PLANAR_ER
#define CU_EGL_COLOR_FORMAT_YUV422_PLANAR_ER     (0x22)
#define CU_EGL_COLOR_FORMAT_YUV420_PLANAR_ER     (0x23)
#define CU_EGL_COLOR_FORMAT_YUV422_SEMIPLANAR_ER (0x25)
#define CU_EGL_COLOR_FORMAT_YUV420_SEMIPLANAR_ER (0x26)
#endif

namespace ArgusSamples
{

/**
 * Returns a readable error string from a given CUResult enum
 *
 * @param [in] cuResult, the enum to convert to string.
 */
const char *getCudaErrorString(const CUresult cuResult);

/**
 * Sets up the CUDA library and opens the CUDA device
 *
 * @param [in][out] the global CUDA context.
 */
bool initCUDA(CUcontext *context);

/**
 * Cleans up the CUDA libraries and closes the CUDA device.
 *
 * @param [in][out] the global CUDA context.
 */
bool cleanupCUDA(CUcontext *context);

/**
 * Checks if the format specified is YUV
 * @param [in] cudaEGLFormat to check the eglColorFormat.
 */
bool isCudaFormatYUV(const CUeglColorFormat cudaEGLFormat);

/**
 * Prints out the CUDA frame information.
 *
 * @param [in] cudaEGLFrame, the frame to display information for.
 */
bool printCUDAEGLFrame(const CUeglFrame &cudaEGLFrame);

} // namespace ArgusSamples

#endif // CUDAHELPER_H

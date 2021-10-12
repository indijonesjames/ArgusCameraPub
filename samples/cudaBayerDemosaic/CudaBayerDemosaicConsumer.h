
#ifndef CUDA_BAYER_DEMOSAIC_CONSUMER_H
#define CUDA_BAYER_DEMOSAIC_CONSUMER_H

#include "CUDAHelper.h"
#include "Error.h"
#include "PreviewConsumer.h"

#include "CudaBayerDemosaicKernel.h"

namespace ArgusSamples
{

/**
 * The CudaBayerDemosaicConsumer acts as an EGLStream consumer for Bayer buffers output
 * from argus (RAW16), and uses a CUDA kernel to perform simple Bayer demosaic on the
 * input in order to output RGBA data. This component then acts as a producer to another
 * EGLStream, pushing the RGBA results buffer into a PreviewConsumer so that its
 * contents are rendered on screen using OpenGL.
 *
 * This sample effectively chains two EGLStreams together as follows:
 *   Argus --> [Bayer EGLStream] --> CUDA Demosaic --> [RGBA EGLStream] --> OpenGL
 */
class CudaBayerDemosaicConsumer : public Thread
{
public:

    explicit CudaBayerDemosaicConsumer(EGLDisplay display, EGLStreamKHR stream,
                                       Argus::Size2D<uint32_t> size, uint32_t frameCount);
    ~CudaBayerDemosaicConsumer();

private:
    /** @name Thread methods */
    /**@{*/
    virtual bool threadInitialize();
    virtual bool threadExecute();
    virtual bool threadShutdown();
    /**@}*/

    static const uint32_t RGBA_BUFFER_COUNT = 2; // Number of buffers to alloc in RGBA stream.

    EGLDisplay m_eglDisplay;            // EGLDisplay handle.
    EGLStreamKHR m_bayerInputStream;    // EGLStream between Argus and CUDA.
    EGLStreamHolder m_rgbaOutputStream; // EGLStream between CUDA and OpenGL.

    Argus::Size2D<uint32_t> m_bayerSize;  // Size of Bayer input.
    Argus::Size2D<uint32_t> m_outputSize; // Size of RGBA output.

    uint32_t m_frameCount;              // Number of frames to process.

    CUcontext m_cudaContext;
    CUeglStreamConnection m_cudaBayerStreamConnection; // CUDA handle to Bayer stream.
    CUeglStreamConnection m_cudaRGBAStreamConnection;  // CUDA handle to RGBA stream.

    CUdeviceptr m_rgbaBuffers[RGBA_BUFFER_COUNT]; // RGBA buffers used for CUDA output.

    PreviewConsumerThread* m_previewConsumerThread; // OpenGL consumer thread.
};

}; // namespace ArgusSamples

#endif // CUDA_BAYER_DEMOSAIC_CONSUMER_H

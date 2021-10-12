
#include "NativeBuffer.h"

#if defined(ANDROID)
#include "android/NvRmSurfaceBuffer.h"
#elif defined(NVMMAPI_SUPPORTED)
#include "nvmmapi/NvNativeBuffer.h"
#endif

namespace ArgusSamples
{

NativeBuffer::NativeBuffer(const Argus::Size2D<uint32_t>& size)
    : m_size(size)
{
}

NativeBuffer::~NativeBuffer()
{
}

/* static */
NativeBuffer* NativeBuffer::create(const Argus::Size2D<uint32_t>& size, ColorFormat colorFormat)
{
    // Currently only support YUV420 generic format
    if (colorFormat != COLOR_FORMAT_YUV420)
        return NULL;

#if defined(ANDROID)
    return NvRmSurfaceBuffer::create(size, NvColorFormat_U8_V8);
#elif defined(NVMMAPI_SUPPORTED)
    return NvNativeBuffer::create(size, NvBufferColorFormat_NV12);
#else
    return NULL;
#endif
}

}; // namespace ArgusSamples

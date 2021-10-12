
#include "nvmmapi/NvNativeBuffer.h"

namespace ArgusSamples
{

    NvNativeBuffer::NvNativeBuffer(const Argus::Size2D<uint32_t>& size)
    : NativeBuffer(size)
    , m_fd(-1)
{
}

NvNativeBuffer::~NvNativeBuffer()
{
    if (m_fd >= 0)
        NvBufferDestroy(m_fd);
}

/* static */
NvNativeBuffer* NvNativeBuffer::create(const Argus::Size2D<uint32_t>& size,
                                       NvBufferColorFormat colorFormat,
                                       NvBufferLayout layout)
{
    NvNativeBuffer* buffer = new NvNativeBuffer(size);
    if (!buffer)
        return NULL;

    NvBufferCreateParams inputParams = {0};

    inputParams.width = size.width();
    inputParams.height = size.height();
    inputParams.layout = layout;
    inputParams.colorFormat = colorFormat;
    inputParams.payloadType = NvBufferPayload_SurfArray;
    inputParams.nvbuf_tag = NvBufferTag_CAMERA;

    if (NvBufferCreateEx(&buffer->m_fd, &inputParams))
    {
        delete buffer;
        return NULL;
    }

    return buffer;
}

EGLImageKHR NvNativeBuffer::createEGLImage(EGLDisplay eglDisplay)
{
    return NvEGLImageFromFd(eglDisplay, m_fd);
}

} // namespace ArgusSamples

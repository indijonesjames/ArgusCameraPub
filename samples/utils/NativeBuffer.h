
#ifndef NATIVE_BUFFER_H
#define NATIVE_BUFFER_H

#include <Argus/Argus.h>

#include "IEGLImageSource.h"

namespace ArgusSamples
{

/**
 * Base NativeBuffer class. Static create method may be used directly rather than platform-specific
 * native type creation methods when generic buffer allocations are sufficient. All native buffer
 * types must support EGLImage creation.
 */
class NativeBuffer : public IEGLImageSource
{
public:
    virtual ~NativeBuffer();

    /**
     * Generic color format that may be used for generic NativeBuffer creation.
     */
    enum ColorFormat
    {
        COLOR_FORMAT_YUV420
    };

    /**
     * Generic NativeBuffer allocator, used when platform format specifics aren't needed.
     * @param[in] size Size of the native buffer.
     * @param[in] colorFormat Color format of the native buffer.
     * @returns A new NativeBuffer, or NULL on error.
     */
    static NativeBuffer* create(const Argus::Size2D<uint32_t>& size,
                                ColorFormat colorFormat = COLOR_FORMAT_YUV420);

    /**
     * Creates an EGLImage with this native buffer's resources as the source.
     * @param[in] eglDisplay The EGLDisplay to create the image with.
     * @returns an EGLImage handle, or EGL_NO_IMAGE on failure.
     */
    virtual EGLImageKHR createEGLImage(EGLDisplay eglDisplay) = 0;

    /**
     * Returns the size of the buffer.
     */
    virtual const Argus::Size2D<uint32_t>& getSize() const { return m_size; }

protected:
    NativeBuffer(const Argus::Size2D<uint32_t>& size);

    Argus::Size2D<uint32_t> m_size;
};


}; // namespace ArgusSamples

#endif // NATIVE_BUFFER_H

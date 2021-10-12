
#ifndef IEGLIMAGE_SOURCE_H
#define IEGLIMAGE_SOURCE_H

#include "EGLGlobal.h"

namespace ArgusSamples
{

/**
 * Interface for objects that may act as EGLImage sources. These objects
 * provide a method for creating an EGLImage from their resources.
 */
class IEGLImageSource
{
public:

    /**
     * Creates an EGLImage with this object's resources as the source.
     * @param[in] eglDisplay The EGLDisplay to create the image with.
     * @returns an EGLImage handle, or EGL_NO_IMAGE on failure.
     */
    virtual EGLImageKHR createEGLImage(EGLDisplay eglDisplay) = 0;

protected:
    virtual ~IEGLImageSource() { }
};

} // namespace ArgusSamples

#endif // IEGLIMAGE_SOURCE_H

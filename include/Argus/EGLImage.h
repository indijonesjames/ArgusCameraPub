
/**
 * @file
 * <b>Libargus API: EGLImage API</b>
 *
 * @b Description: Defines a BufferType that wraps an EGLImage resource.
 */

#ifndef _ARGUS_EGL_IMAGE_H
#define _ARGUS_EGL_IMAGE_H

namespace Argus
{

/**
 * @defgroup ArgusEGLImageBuffer EGLImageBuffer
 * @ingroup ArgusBufferBuffer
 * @ref ArgusBuffer type that wraps an EGLImage resource (BUFFER_TYPE_EGL_IMAGE).
 */
/**
 * @defgroup ArgusEGLImageBufferSettings EGLImageBufferSettings
 * @ingroup ArgusBufferBufferSettings
 * Settings type used to configure/create @ref ArgusEGLImageBuffer Buffers (BUFFER_TYPE_EGL_IMAGE).
 */

/**
 * @ref ArgusBuffer type that wraps an EGLImage resource.
 * @ingroup ArgusBufferBuffer ArgusBufferBufferSettings
 */
DEFINE_UUID(BufferType, BUFFER_TYPE_EGL_IMAGE, c723d966,5231,11e7,9598,18,00,20,0c,9a,66);

/**
 * @class IEGLImageBufferSettings
 *
 * Interface that provides the settings used to configure EGLImage Buffer creation.
 * These Buffers act as siblings for the EGLImage, providing libargus write access
 * to the underlying buffer resources for the destination of capture requests.
 *
 * @ingroup ArgusEGLImageBufferSettings
 */
DEFINE_UUID(InterfaceID, IID_EGL_IMAGE_BUFFER_SETTINGS, c723d967,5231,11e7,9598,18,00,20,0c,9a,66);
class IEGLImageBufferSettings : public Interface
{
public:
    static const InterfaceID& id() { return IID_EGL_IMAGE_BUFFER_SETTINGS; }

    /**
     * Sets the EGLDisplay which owns the EGLImage.
     * @param[in] eglDisplay The EGLDisplay that owns the EGLImage.
     */
    virtual Status setEGLDisplay(EGLDisplay eglDisplay) = 0;

    /**
     * Returns the EGLDisplay which owns the EGLImage.
     */
    virtual EGLDisplay getEGLDisplay() const = 0;

    /**
     * Sets the EGLImage to use as the sibling for this Buffer.
     * @param[in] eglImage The EGLImage to use as the sibling for this Buffer.
     */
    virtual Status setEGLImage(EGLImageKHR eglImage) = 0;

    /**
     * Returns the EGLImage to use as the sibling for this Buffer.
     */
    virtual EGLImageKHR getEGLImage() const = 0;

protected:
    ~IEGLImageBufferSettings() {}
};

/**
 * @class IEGLImageBuffer
 *
 * Interface that provides methods to EGLImage Buffers.
 *
 * @ingroup ArgusEGLImageBuffer
 */
DEFINE_UUID(InterfaceID, IID_EGL_IMAGE_BUFFER, c723d968,5231,11e7,9598,18,00,20,0c,9a,66);
class IEGLImageBuffer : public Interface
{
public:
    static const InterfaceID& id() { return IID_EGL_IMAGE_BUFFER; }

    /**
     * Returns the EGLDisplay that owns the EGLImage.
     */
    virtual EGLDisplay getEGLDisplay() const = 0;

    /**
     * Returns the EGLImage being used for this Buffer.
     */
    virtual EGLImageKHR getEGLImage() const = 0;

protected:
    ~IEGLImageBuffer() {}
};

} // namespace Argus

#endif // _ARGUS_EGL_IMAGE_H

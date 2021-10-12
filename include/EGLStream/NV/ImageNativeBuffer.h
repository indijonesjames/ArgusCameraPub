
#ifndef _EGLSTREAM_NV_IMAGE_NATIVE_BUFFER_H
#define _EGLSTREAM_NV_IMAGE_NATIVE_BUFFER_H

#include <nvbuf_utils.h>

namespace EGLStream
{

/**
 * The NV::ImageNativeBuffer extension adds an interface to create and/or
 * copy EGLStream Images to NvBuffers (see nvbuf_utils.h).
 */
DEFINE_UUID(Argus::ExtensionName, NV_IMAGE_NATIVE_BUFFER, ce9e8c60,1792,11e6,bdf4,08,00,20,0c,9a,66);

namespace NV
{

/*
 * Counterclockwise rotation value, in degree
 */
enum Rotation
{
    ROTATION_0,
    ROTATION_90,
    ROTATION_180,
    ROTATION_270,
    ROTATION_COUNT
};

/**
 * @class IImageNativeBuffer
 *
 * Interface that supports creating new NvBuffers and/or copying Image contents
 * to existing NvBuffers.
 */
DEFINE_UUID(Argus::InterfaceID, IID_IMAGE_NATIVE_BUFFER, 2f410340,1793,11e6,bdf4,08,00,20,0c,9a,66);
class IImageNativeBuffer : public Argus::Interface
{
public:
    static const Argus::InterfaceID& id() { return IID_IMAGE_NATIVE_BUFFER; }

    /**
     * Creates a new NvBuffer, copies the image contents to the new buffer, then
     * returns the dmabuf-fd. Ownership of this dmabuf-fd is given to the caller
     * and must be destroyed using NvBufferDestroy (see nvbuf_utils.h).
     *
     * Note that the size, format, and layout of the new buffer can be different from
     * what is being used for the EGLStream, and if this is the case then scaling
     * and format conversion will be performed when the image is copied to the
     * new buffer. Details of this scaling and conversion are left up to the
     * implementation, but the application should consider and account for any
     * measured performance penalties associated with such operations.
     *
     * @param[in] size the size of the NvBuffer to create.
     * @param[in] format the color format to use for the new NvBuffer.
     * @param[in] layout the buffer layout to use for the new NvBuffer.
     * @param[in] rotation flag that could be 0/90/180/270 degree.
     * @param[out] status optional status return code.
     * @returns -1 on failure, or a valid dmabuf-fd on success.
     */
    virtual int createNvBuffer(Argus::Size2D<uint32_t> size,
                               NvBufferColorFormat format,
                               NvBufferLayout layout,
                               Rotation rotation = ROTATION_0,
                               Argus::Status* status = NULL) const = 0;

    /**
     * Copies the image contents to the given NvBuffer. This performs an uncropped
     * (full-surface) copy of the image to the provided buffer, which is permitted
     * to have different size, format, and layout attributes than those of the buffer
     * backing this EGLStream image. If this is the case, scaling and format conversion
     * will be performed when the image is copied to the buffer. Details of this scaling
     * and conversion are left up to the implementation, but the application should
     * consider and account for any measured performance penalties associated with such
     * operations.
     *
     * @param[in] fd the dmabuf-fd of the NvBuffer to copy to.
     * @param[in] rotation flag that could be 0/90/180/270 degree.
     */
    virtual Argus::Status copyToNvBuffer(int fd, Rotation rotation = ROTATION_0) const = 0;

protected:
    ~IImageNativeBuffer() {}
};

} // namespace NV

} // namespace EGLStream

#endif // _EGLSTREAM_NV_IMAGE_NATIVE_BUFFER_H

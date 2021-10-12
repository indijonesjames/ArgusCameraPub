
#ifndef _EGLSTREAM_METADATA_CONTAINER_H
#define _EGLSTREAM_METADATA_CONTAINER_H

namespace EGLStream
{

/**
 * @class MetadataContainer
 *
 * When image frames are presented to EGLStreams, private metadata may be
 * embedded in the frame data. This class provides a means for consumer-side
 * applications to extract and access this metadata directly from the EGLStream
 * without needing to initialize the producer library.
 */
class MetadataContainer : public Argus::InterfaceProvider, public Argus::Destructable
{
public:
    enum MetadataFrame
    {
        CONSUMER,
        PRODUCER
    };

    /**
     * Create and return a MetadataContainer object from the metadata embedded
     * in the EGLStream frame.
     * @param[in] eglDisplay The EGL display that owns the stream.
     * @param[in] eglStream The EGL stream.
     * @param[in] frame The frame for which the metadata should be extracted.
     *                  This can be either CONSUMER or PRODUCER, corresponding to the last
     *                  frame acquired by the consumer or presented by the producer, respectively.
     * @param[out] status Optional pointer to return success/status of the call.
     */
    static MetadataContainer* create(EGLDisplay eglDisplay,
                                     EGLStreamKHR eglStream,
                                     MetadataFrame frame = CONSUMER,
                                     Argus::Status* status = NULL);
protected:
    ~MetadataContainer() {}
};

} // namespace EGLStream

#endif // _EGLSTREAM_METADATA_CONTAINER_H


#ifndef _EGLSTREAM_ARGUS_CAPTURE_METADATA_H
#define _EGLSTREAM_ARGUS_CAPTURE_METADATA_H

namespace EGLStream
{

/**
 * @class IArgusCaptureMetadata
 *
 * This interface is used to access Argus::CaptureMetadata from an object.
 * Objects that may support this interface are EGLStream::Frame objects
 * originating from an Argus producer, or a MetadataContainer object
 * created directly from an EGLStream frame's embedded metadata.
 */
DEFINE_UUID(Argus::InterfaceID, IID_ARGUS_CAPTURE_METADATA, b94aa2e0,c3c8,11e5,a837,08,00,20,0c,9a,66);
class IArgusCaptureMetadata : public Argus::Interface
{
public:
    static const Argus::InterfaceID& id() { return IID_ARGUS_CAPTURE_METADATA; }

    /**
     * Returns the CaptureMetadata associated with the object.. The lifetime of this
     * metadata is equivalent to that of the object being called. NULL may be returned
     * if there is no metadata available.
     */
    virtual Argus::CaptureMetadata* getMetadata() const = 0;

protected:
    ~IArgusCaptureMetadata() {}
};

} // namespace EGLStream

#endif // _EGLSTREAM_ARGUS_CAPTURE_METADATA_H

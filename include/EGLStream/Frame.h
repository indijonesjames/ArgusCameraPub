
#ifndef _EGLSTREAM_FRAME_H
#define _EGLSTREAM_FRAME_H

namespace EGLStream
{

class Image;

/**
 * Frame objects are acquired and returned by a FrameConsumer, and correspond
 * to frames that have been written to the stream. Frames contain metadata
 * corresponsing to the stream frame as well as the Image data of the frame.
 * Destroying a Frame will return its image buffers back to the stream for reuse.
 */
class Frame : public Argus::InterfaceProvider, public Argus::Destructable
{
protected:
    ~Frame() {}
};

/**
 * @class IFrame
 *
 * Interface that provides core access to a Frame.
 */
DEFINE_UUID(Argus::InterfaceID, IID_FRAME, 546F4520,87EF,11E5,A837,08,00,20,0C,9A,66);
class IFrame : public Argus::Interface
{
public:
    static const Argus::InterfaceID& id() { return IID_FRAME; }

    /**
     * Returns the frame number.
     */
    virtual uint64_t getNumber() const = 0;

    /**
     * Returns the timestamp of the frame, in nanoseconds.
     */
    virtual uint64_t getTime() const = 0;

    /**
     * Returns the Image contained in the Frame. The returned Image object is
     * owned by the Frame and is valid as long as the Frame is valid. (that is, while
     * the Frame is acquired).
     */
    virtual Image* getImage() = 0;

protected:
    ~IFrame() {}
};

} // namespace EGLStream

#endif // _EGLSTREAM_FRAME_H

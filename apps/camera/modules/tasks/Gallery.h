
#ifndef CAMERA_MODULES_GALLERY_H
#define CAMERA_MODULES_GALLERY_H

#include "ITask.h"
#include "Util.h"

namespace ArgusSamples
{

class GalleryThread;

/**
 * This task implements a gallery to review images and videos
 */
class TaskGallery : public ITask
{
public:
    TaskGallery();
    virtual ~TaskGallery();

    /** @name ITask methods */
    /**@{*/
    virtual bool initialize();
    virtual bool shutdown();

    virtual bool start();
    virtual bool stop();
    /**@}*/

    /**
     * Toggle playback
     */
    bool togglePlayBack();

    /**
     * Rewind
     */
    bool rewind();

    /**
     * Display next item.
     */
    bool prevItem();

    /**
     * Display previous item.
     */
    bool nextItem();

private:
    bool m_initialized;                 ///< set if initialized
    bool m_running;                     ///< set if running
    GalleryThread *m_thread;            ///< gallery thread
};

}; // namespace ArgusSamples

#endif // CAMERA_MODULES_GALLERY_H

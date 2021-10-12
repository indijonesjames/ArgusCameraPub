
#ifndef ARGUS_APPS_CAMERA_UI_APP_MODULE_GALLERY_H
#define ARGUS_APPS_CAMERA_UI_APP_MODULE_GALLERY_H

#include "IAppModule.h"
#include "tasks/Gallery.h"

namespace ArgusSamples
{

/**
 * The gallery app module adds functionality to review images and videos.
 */
class AppModuleGallery : public IAppModule, public Window::IKeyObserver
{
public:
    AppModuleGallery();
    virtual ~AppModuleGallery();

    /** @name IAppModule methods */
    /**@{*/
    virtual bool initialize(Options &options);
    virtual bool shutdown();
    virtual bool start(Window::IGuiMenuBar *iGuiMenuBar = NULL,
        Window::IGuiContainer *iGuiContainerConfig = NULL);
    virtual bool stop();
    /**@}*/

    /** @name option callbacks */
    /**@{*/
    static bool prevItem(void *userPtr, const char *optArg);
    static bool nextItem(void *userPtr, const char *optArg);
    static bool togglePlayBack(void *userPtr, const char *optArg);
    static bool rewind(void *userPtr, const char *optArg);
    /**@}*/

private:
    bool m_initialized;         ///< set if initialized
    bool m_running;             ///< set if running
    TaskGallery m_gallery;      ///< gallery task

    Window::IGuiContainer *m_guiContainerConfig; ///< configuration GUI container
    Window::IGuiContainerGrid *m_guiConfig; ///< configuration GUI

    /** @name IKeyObserver methods */
    /**@{*/
    virtual bool onKey(const Key &key);
    /**@}*/
};

}; // namespace ArgusSamples

#endif // ARGUS_APPS_CAMERA_UI_APP_MODULE_GALLERY_H

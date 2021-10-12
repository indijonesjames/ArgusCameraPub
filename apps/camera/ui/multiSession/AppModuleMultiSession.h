
#ifndef ARGUS_APPS_CAMERA_UI_APP_MODULE_MULTI_SESSION_H
#define ARGUS_APPS_CAMERA_UI_APP_MODULE_MULTI_SESSION_H

#include "../common/IAppModule.h"
#include "tasks/MultiSession.h"

namespace ArgusSamples
{

/**
 * The multi session app module adds functionality for adding multiple sessions where
 * each session uses a different sensor.
 */
class AppModuleMultiSession : public IAppModule
{
public:
    AppModuleMultiSession();
    virtual ~AppModuleMultiSession();

    /** @name IAppModule methods */
    /**@{*/
    virtual bool initialize(Options &options);
    virtual bool shutdown();
    virtual bool start(Window::IGuiMenuBar *iGuiMenuBar = NULL,
        Window::IGuiContainer *iGuiContainerConfig = NULL);
    virtual bool stop();
    /**@}*/

private:
    bool m_initialized;                 ///< set if initialized
    TaskMultiSession m_multiSession;    ///< multi session task
};

}; // namespace ArgusSamples

#endif // ARGUS_APPS_CAMERA_UI_APP_MODULE_MULTI_SESSION_H

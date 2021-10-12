
#ifndef ARGUS_APPS_CAMERA_UI_COMMON_APP_MODULE_H
#define ARGUS_APPS_CAMERA_UI_COMMON_APP_MODULE_H

#include "Window.h"

namespace ArgusSamples
{

class Options;

/**
 * A application module exposes command line options, GUI elements and executes tasks.
 */
class IAppModule
{
public:
    IAppModule() { }
    virtual ~IAppModule() { };

    /**
     * Initialize
     *
     * @param [in] options  each app module can add options
     */
    virtual bool initialize(Options &options) = 0;

    /**
     * Shut down
     */
    virtual bool shutdown() = 0;

    /**
     * Start the module
     *
     * @param [in] iGuiMenuBar  optional, the module can add menu items to this menu bar
     * @param [in] iGuiContainerConfig  optional, the module can add configuration options to this
     *                                  container
     */
    virtual bool start(Window::IGuiMenuBar *iGuiMenuBar = NULL,
        Window::IGuiContainer *iGuiContainerConfig = NULL) = 0;

    /**
     * Stop the module
     */
    virtual bool stop() = 0;
};

}; // namespace ArgusSamples

#endif // ARGUS_APPS_CAMERA_UI_COMMON_APP_MODULE_H

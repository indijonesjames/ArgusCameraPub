
#ifndef ARGUS_APPS_CAMERA_UI_COMMON_APP_H
#define ARGUS_APPS_CAMERA_UI_COMMON_APP_H

#include "Options.h"
#include "Window.h"

namespace ArgusSamples
{

/**
 * Base class for apps.
 */
class App : public Window::IKeyObserver
{
public:
    explicit App(const char *appName);
    virtual ~App();

    virtual bool initialize();
    virtual bool shutdown();
    virtual bool start() = 0;

    bool run(int argc, char **argv);

protected:
    /** @name IKeyObserver methods */
    /**@{*/
    virtual bool onKey(const Key &key);
    /**@}*/

    Options m_options;

private:
    /**
     * Hide default constructor
     */
    App();
};

}; // namespace ArgusSamples

#endif // ARGUS_APPS_CAMERA_UI_COMMON_APP_H

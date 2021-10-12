
#ifndef WINDOW_H
#define WINDOW_H

#include "WindowBase.h"

/// The window supports GLX
#define WINDOW_GUI_SUPPORT WINDOW_GUI_GLX

namespace ArgusSamples
{

/**
 * GLX implementation of the window class
 */
class Window : public WindowBase
{
public:
    /**
     * Get the window instance.
     */
    static Window &getInstance();

    /** @name WindowBase methods */
    /**@{*/
    virtual bool shutdown();
    virtual bool pollEvents();
    virtual bool eventLoop();
    virtual bool requestExit();
    virtual EGLNativeDisplayType getEGLNativeDisplay() const;
    virtual EGLNativeWindowType getEGLNativeWindow() const;
    virtual uint32_t getWidth() const;
    virtual uint32_t getHeight() const;
    virtual bool setWindowRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    using WindowBase::setWindowRect;
    /**@}*/

private:
    Window();
    virtual ~Window();

    // this is a singleton, hide copy constructor etc.
    Window(const Window&);
    Window& operator=(const Window&);

    virtual bool initialize();

    class PrivateData;
    PrivateData *m_private;     ///< hide private data
};

}; // namespace ArgusSamples

#endif // WINDOW_H

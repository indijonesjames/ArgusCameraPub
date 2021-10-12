
#ifndef ARGUS_SAMPLES_UTILS_GTK_WINDOW_H
#define ARGUS_SAMPLES_UTILS_GTK_WINDOW_H

#include "WindowBase.h"

/// The window supports GTK
#define WINDOW_GUI_SUPPORT WINDOW_GUI_GTK

namespace ArgusSamples
{

/**
 * GTK implementation of the window class
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
    virtual bool setWindowGui(IGuiContainer *iGuiContainer = NULL,
        IGuiElement *iGuiElementWindow = NULL, IGuiElement *iGuiElementView = NULL);
    /**@}*/

    /**
     * A GUI builder is a special container initialized with a builder string.
     */
    class IGuiBuilder : public IGuiContainer
    {
    public:
        virtual ~IGuiBuilder() {}

        /**
         * Create a GUI builder using 'builderString'.
         *
         * @param builderString [in]    GTK builder string
         * @param iGuiBuilder [out]   the created GUI builder
         */
        static bool create(const char *builderString, IGuiBuilder **iGuiBuilder);

        /**
         * Create an element with 'name' from the builder. This creates a new IGuiElement
         * referencing the element in the builder. The caller is responsible to destroy the new
         * IGuiElement when it's no longer used.
         */
        virtual IGuiElement *createElement(const char *name) = 0;
    };

private:
    Window();
    virtual ~Window();

    // this is a singleton, hide copy constructor etc.
    Window(const Window&);
    Window& operator=(const Window&);

    virtual bool initialize();

    // Allow GTK call backs to access private data
    class gtkCallBacks;
    friend class gtkCallBacks;

    // Allow signal call backs to access private data
    class SignalCallbacks;
    friend class SignalCallBacks;

    class PrivateData;
    PrivateData *m_private;     ///< hide private data
};

}; // namespace ArgusSamples

#endif // ARGUS_SAMPLES_UTILS_GTK_WINDOW_H

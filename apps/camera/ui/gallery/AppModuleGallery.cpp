
#include <stdlib.h>

#include "AppModuleGallery.h"
#include "Error.h"

namespace ArgusSamples
{

/* static */ bool AppModuleGallery::prevItem(void *userPtr, const char *optArg)
{
    AppModuleGallery *module = reinterpret_cast<AppModuleGallery*>(userPtr);

    PROPAGATE_ERROR(module->m_gallery.prevItem());

    return true;
}

/* static */ bool AppModuleGallery::nextItem(void *userPtr, const char *optArg)
{
    AppModuleGallery *module = reinterpret_cast<AppModuleGallery*>(userPtr);

    PROPAGATE_ERROR(module->m_gallery.nextItem());

    return true;
}

/* static */ bool AppModuleGallery::togglePlayBack(void *userPtr, const char *optArg)
{
    AppModuleGallery *module = reinterpret_cast<AppModuleGallery*>(userPtr);

    PROPAGATE_ERROR(module->m_gallery.togglePlayBack());

    return true;
}

/* static */ bool AppModuleGallery::rewind(void *userPtr, const char *optArg)
{
    AppModuleGallery *module = reinterpret_cast<AppModuleGallery*>(userPtr);

    PROPAGATE_ERROR(module->m_gallery.rewind());

    return true;
}

AppModuleGallery::AppModuleGallery()
    : m_initialized(false)
    , m_running(false)
    , m_guiContainerConfig(NULL)
    , m_guiConfig(NULL)
{
}

AppModuleGallery::~AppModuleGallery()
{
    shutdown();
}

bool AppModuleGallery::initialize(Options &options)
{
    if (m_initialized)
        return true;

    PROPAGATE_ERROR(m_gallery.initialize());

    m_initialized = true;

    return true;
}

bool AppModuleGallery::shutdown()
{
    if (!m_initialized)
        return true;

    PROPAGATE_ERROR_CONTINUE(stop());

    PROPAGATE_ERROR_CONTINUE(m_gallery.shutdown());

    m_initialized = false;

    return true;
}

bool AppModuleGallery::start(Window::IGuiMenuBar *iGuiMenuBar,
    Window::IGuiContainer *iGuiContainerConfig)
{
    if (m_running)
        return true;

    // register key observer
    PROPAGATE_ERROR(Window::getInstance().registerObserver(this));

    // initialize the GUI
    if (iGuiContainerConfig && !m_guiConfig)
    {
        // initialize the GUI

        // create a grid container
        PROPAGATE_ERROR(Window::IGuiContainerGrid::create(&m_guiConfig));

        // create the elements
        UniquePointer<Window::IGuiElement> element;
        unsigned int column = 0;

        PROPAGATE_ERROR(Window::IGuiElement::createAction("Previous Item",
            AppModuleGallery::prevItem, this, Window::IGuiElement::FLAG_NONE,
            Window::IGuiElement::ICON_PREVIOUS, &element));
        PROPAGATE_ERROR(m_guiConfig->attach(element.get(), column++, 0));
        element.release();

        PROPAGATE_ERROR(Window::IGuiElement::createAction("Rewind",
            AppModuleGallery::rewind, this, Window::IGuiElement::FLAG_NONE,
            Window::IGuiElement::ICON_MEDIA_REWIND, &element));
        PROPAGATE_ERROR(m_guiConfig->attach(element.get(), column++, 0));
        element.release();

        PROPAGATE_ERROR(Window::IGuiElement::createAction("Toggle Playback",
            AppModuleGallery::togglePlayBack, this, Window::IGuiElement::FLAG_BUTTON_TOGGLE,
            Window::IGuiElement::ICON_MEDIA_PLAY, &element));
        PROPAGATE_ERROR(m_guiConfig->attach(element.get(), column++, 0));
        element.release();

        PROPAGATE_ERROR(Window::IGuiElement::createAction("Next Item",
            AppModuleGallery::nextItem, this, Window::IGuiElement::FLAG_NONE,
            Window::IGuiElement::ICON_NEXT, &element));
        PROPAGATE_ERROR(m_guiConfig->attach(element.get(), column++, 0));
        element.release();

        m_guiContainerConfig = iGuiContainerConfig;
    }

    if (m_guiContainerConfig)
        PROPAGATE_ERROR(m_guiContainerConfig->add(m_guiConfig));

    PROPAGATE_ERROR(m_gallery.start());

    m_running = true;

    return true;
}

bool AppModuleGallery::stop()
{
    if (!m_running)
        return true;

    PROPAGATE_ERROR(m_gallery.stop());

    if (m_guiContainerConfig)
        PROPAGATE_ERROR(m_guiContainerConfig->remove(m_guiConfig));

    // unregister key observer
    PROPAGATE_ERROR(Window::getInstance().unregisterObserver(this));

    m_running = false;

    return true;
}

bool AppModuleGallery::onKey(const Key &key)
{
    if (key == Key("Left"))
    {
        PROPAGATE_ERROR(m_gallery.prevItem());
    }
    else if (key == Key("Right"))
    {
        PROPAGATE_ERROR(m_gallery.nextItem());
    }
    else if (key == Key("space"))
    {
        PROPAGATE_ERROR(m_gallery.togglePlayBack());
    }

    return true;
}

}; // namespace ArgusSamples

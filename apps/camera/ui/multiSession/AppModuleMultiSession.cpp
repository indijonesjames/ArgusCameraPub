
#include "AppModuleMultiSession.h"

#include <stdlib.h>

#include "Options.h"
#include "Error.h"

namespace ArgusSamples
{

AppModuleMultiSession::AppModuleMultiSession()
    : m_initialized(false)
{
}

AppModuleMultiSession::~AppModuleMultiSession()
{
    shutdown();
}

bool AppModuleMultiSession::initialize(Options &options)
{
    if (m_initialized)
        return true;

    PROPAGATE_ERROR(m_multiSession.initialize());

    m_initialized = true;

    return true;
}

bool AppModuleMultiSession::shutdown()
{
    if (!m_initialized)
        return true;

    PROPAGATE_ERROR_CONTINUE(m_multiSession.shutdown());

    m_initialized = false;
    return true;
}

bool AppModuleMultiSession::start(Window::IGuiMenuBar *iGuiMenuBar,
    Window::IGuiContainer *iGuiContainerConfig)
{
    PROPAGATE_ERROR(m_multiSession.start());
    return true;
}

bool AppModuleMultiSession::stop()
{
    PROPAGATE_ERROR(m_multiSession.stop());
    return true;
}

}; // namespace ArgusSamples

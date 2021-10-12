
#include "Mutex.h"
#include "Error.h"

namespace ArgusSamples
{

Mutex::Mutex()
    : m_initialized(false)
{
}

Mutex::~Mutex()
{
    shutdown();
}

bool Mutex::initialize()
{
    if (!m_initialized)
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
            ORIGINATE_ERROR("Failed to initialize mutex");
        m_initialized = true;
    }

    return true;
}

bool Mutex::shutdown()
{
    if (m_initialized)
    {
        if (pthread_mutex_destroy(&m_mutex) != 0)
            ORIGINATE_ERROR("Failed to destroy mutex");
        m_initialized = false;
    }

    return true;
}

bool Mutex::lock() const
{
    if (!m_initialized)
        ORIGINATE_ERROR("Not initialized");

    if (pthread_mutex_lock(&m_mutex) != 0)
        ORIGINATE_ERROR("Failed to lock mutex");

    return true;
}

bool Mutex::unlock() const
{
    if (!m_initialized)
        ORIGINATE_ERROR("Not initialized");

    if (pthread_mutex_unlock(&m_mutex) != 0)
        ORIGINATE_ERROR("Failed to unlock mutex");

    return true;
}

}; // namespace ArgusSamples

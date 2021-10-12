
#include "ConditionVariable.h"
#include "Mutex.h"
#include "Error.h"

namespace ArgusSamples
{

ConditionVariable::ConditionVariable()
    : m_initialized(false)
{
}

ConditionVariable::~ConditionVariable()
{
    shutdown();
}

bool ConditionVariable::initialize()
{
    if (!m_initialized)
    {
        if (pthread_cond_init(&m_cond, NULL) != 0)
            ORIGINATE_ERROR("Failed to initialize condition variable");
        m_initialized = true;
    }

    return true;
}

bool ConditionVariable::shutdown()
{
    if (m_initialized)
    {
        if (pthread_cond_destroy(&m_cond) != 0)
            ORIGINATE_ERROR("Failed to destroy condition variable");
        m_initialized = false;
    }

    return true;
}

bool ConditionVariable::broadcast() const
{
    if (!m_initialized)
        ORIGINATE_ERROR("Not initialized");

    if (pthread_cond_broadcast(&m_cond) != 0)
        ORIGINATE_ERROR("pthread_cond_broadcast failed");
    return true;
}

bool ConditionVariable::signal() const
{
    if (!m_initialized)
        ORIGINATE_ERROR("Not initialized");

    if (pthread_cond_signal(&m_cond) != 0)
        ORIGINATE_ERROR("pthread_cond_signal failed");
    return true;
}

bool ConditionVariable::wait(const Mutex& mutex) const
{
    if (!m_initialized)
        ORIGINATE_ERROR("Not initialized");

    if (pthread_cond_wait(&m_cond, mutex.getPThreadMutex()) != 0)
        ORIGINATE_ERROR("pthread_cond_signal failed");
    return true;
}

}; // namespace ArgusSamples

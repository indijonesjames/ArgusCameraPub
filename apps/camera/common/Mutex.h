
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

#include "Error.h"

namespace ArgusSamples
{

class ConditionVariable;

/**
 * Mutex
 */
class Mutex
{
public:
    Mutex();
    ~Mutex();

    /**
     * Create the underlying mutex. This method must be called before any other methods.
     */
    bool initialize();

    /**
     * Destroy the underlying mutex. After this call, this object can no longer be used
     * (until and unless a future call to @c initialize()). Calling this method if the
     * object is not initialized generates no error, but silently returns.
     */
    bool shutdown();

    /**
     * Lock the mutex. This method is declared @c const for convenience.
     */
    bool lock() const;

    /**
     * Unlock the mutex. This method is declared @c const for convenience.
     */
    bool unlock() const;

private:
    bool m_initialized;
    /**
     * pthread mutex, this is 'mutable' so that 'const' functions can be used.
     */
    mutable pthread_mutex_t m_mutex;

    /**
     * Hide copy constructor and assignment operator
     */
    Mutex(Mutex &other);
    const Mutex& operator = (const Mutex&);

    friend class ConditionVariable;

    pthread_mutex_t* getPThreadMutex() const
    {
        return &m_mutex;
    }
};

/**
 * An RAII-style class for acquiring a Mutex.
 * The mutex is acquired in the constructor and released in the destructor.
 * This class is NOT to be subclassed.
 */
class ScopedMutex
{
public:
    explicit ScopedMutex(Mutex& mutex)
        : m_mutex(&mutex)
        , m_isLocked(false)
    {
        m_isLocked = m_mutex->lock();
    }

    ~ScopedMutex()
    {
        if (m_isLocked)
            m_mutex->unlock();
    }

    bool expectLocked() const
    {
        if (!m_isLocked)
            ORIGINATE_ERROR("Expected mutex to be locked");
        return true;
    }

private:
    Mutex *m_mutex;
    bool m_isLocked;

    /**
     * Hide default/copy constructor and assignment operator
     */
    ScopedMutex();
    ScopedMutex(ScopedMutex &other);
    ScopedMutex& operator = (const ScopedMutex&);
};

} // namespace ArgusSamples

#endif // MUTEX_H

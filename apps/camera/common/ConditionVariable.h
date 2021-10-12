
#ifndef CAMERA_COMMON_CONDITION_VARIABLE_H
#define CAMERA_COMMON_CONDITION_VARIABLE_H

#include <pthread.h>

namespace ArgusSamples
{

class Mutex;

/**
 * Conditional
 */
class ConditionVariable
{
public:
    ConditionVariable();
    ~ConditionVariable();

    /**
     * Create the underlying condition variable. This method must be called before any other
     * methods.
     */
    bool initialize();

    /**
     * Destroy the underlying condition variable. After this call, this object can no longer be used
     * (until and unless a future call to @c initialize()). Calling this method if the
     * object is not initialized generates no error, but silently returns.
     */
    bool shutdown();

    /**
     * Broadcast the condition variable.  This method is declared @c const for convenience.
     */
    bool broadcast() const;

    /**
     * Signal the condition variable.  This method is declared @c const for convenience.
     */
    bool signal() const;

    /**
     * Wait on the condition variable.  This method is declared @c const for convenience.
     * @param [in] mutex The mutex that will be released while waiting. When multiple threads
     *                   are waiting concurrently, they must all be using the same mutex.
     */
    bool wait(const Mutex& mutex) const;

private:
    bool m_initialized;
    /**
     * pthread conditional variable, this is 'mutable' so that 'const' functions can be used.
     */
    mutable pthread_cond_t m_cond;

    /**
     * Hide copy constructor and assignment operator
     */
    ConditionVariable(ConditionVariable &other);
    const ConditionVariable& operator = (const ConditionVariable&);
};

} // namespace ArgusSamples

#endif // CAMERA_COMMON_CONDITION_VARIABLE_H

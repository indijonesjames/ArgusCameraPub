
#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <unistd.h> // for useconds_t

#include "Ordered.h"

namespace ArgusSamples
{

/**
 * Base class for threads. Derived classes need to implement 'threadInitialize', 'threadExecute'
 * and 'threadShutdown'. This class handles the transition between the thread states.
 */
class Thread
{
public:
    Thread();
    virtual ~Thread();

    /**
     * Initialize
     */
    bool initialize();
    /**
     * Shutdown
     */
    bool shutdown();

    /**
     * Wait until the thread is in 'running' state
     *
     * @param timeout [in] timeout in us
     */
    bool waitRunning(useconds_t timeoutUs = 5 * 1000 * 1000);

 protected:
    virtual bool threadInitialize() = 0;
    virtual bool threadExecute() = 0;
    virtual bool threadShutdown() = 0;

    /**
     * Request thread shutdown
     */
    bool requestShutdown()
    {
        m_doShutdown = true;
        return true;
    }

    Ordered<bool> m_doShutdown; ///< set to request shutdown of the thread

private:
    pthread_t m_threadID;       ///< thread ID

    /**
     * Thread states
     */
    enum ThreadState
    {
        THREAD_INACTIVE,        ///< is inactive
        THREAD_INITIALIZING,    ///< is initializing
        THREAD_RUNNING,         ///< is running
        THREAD_FAILED,          ///< has failed
        THREAD_DONE,            ///< execution done
    };
    Ordered<ThreadState> m_threadState;

    bool threadFunction();

    static void *threadFunctionStub(void *dataPtr);
};

} // namespace ArgusSamples

#endif // THREAD_H

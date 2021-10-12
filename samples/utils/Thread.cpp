
#include "Thread.h"
#include "Error.h"

namespace ArgusSamples
{

Thread::Thread()
    : m_doShutdown(false)
    , m_threadID(0)
    , m_threadState(THREAD_INACTIVE)

{
}

Thread::~Thread()
{
    (void)shutdown();
}

bool Thread::initialize()
{
    if (m_threadID)
        return true;

    if (pthread_create(&m_threadID, NULL, threadFunctionStub, this) != 0)
        ORIGINATE_ERROR("Failed to create thread.");

    // wait for the thread to start up
    while (m_threadState == THREAD_INACTIVE)
        usleep(100);

    return true;

}

bool Thread::shutdown()
{
    if (m_threadID)
    {
        m_doShutdown = true;
        if (pthread_join(m_threadID, NULL) != 0)
            ORIGINATE_ERROR("Failed to join thread");
        m_threadID = 0;
        m_doShutdown = false;
        m_threadState = THREAD_INACTIVE;
    }

   return true;
}

bool Thread::waitRunning(useconds_t timeoutUs)
{
    // Can only wait for a thread which is initializing or already running
    if ((m_threadState != THREAD_INITIALIZING) && (m_threadState != THREAD_RUNNING))
        ORIGINATE_ERROR("Invalid thread state %d", m_threadState.get());

    // wait for the thread to run
    const useconds_t sleepTimeUs = 100;
    while (m_threadState != THREAD_RUNNING)
    {
        usleep(sleepTimeUs);
#ifdef DEBUG
        // in debug mode wait indefinitely
#else
        if (timeoutUs < sleepTimeUs)
            return false;
        timeoutUs -= sleepTimeUs;
#endif
    }

    return true;
}

/**
 * Thread function stub, calls the real thread function.
 *
 * @param [in] dataPtr  Pointer to user data
 */
/* static */ void *Thread::threadFunctionStub(void *dataPtr)
{
    Thread *thread = static_cast<Thread*>(dataPtr);

    if (!thread->threadFunction())
        thread->m_threadState = Thread::THREAD_FAILED;
    else
        thread->m_threadState = Thread::THREAD_DONE;

    return NULL;
}

/**
 * Thread function
 */
bool Thread::threadFunction()
{
    m_threadState = THREAD_INITIALIZING;

    PROPAGATE_ERROR(threadInitialize());

    m_threadState = THREAD_RUNNING;

    while (!m_doShutdown)
    {
        PROPAGATE_ERROR(threadExecute());
    }

    PROPAGATE_ERROR(threadShutdown());

    return true;
}

}; // namespace ArgusSamples

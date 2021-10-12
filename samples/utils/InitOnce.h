
#ifndef CAMERA_MODULES_INITONCE_H
#define CAMERA_MODULES_INITONCE_H

#include <unistd.h> // for usleep()
#include <assert.h>

#include "Ordered.h"

namespace ArgusSamples
{

/**
 * This class supports one-time initialization. Example usage:
 *
 * void func()
 * {
 *     static InitOnce initOnce;
 *
 *     if (initOnce.begin())
 *     {
 *         if (doInitialization())
 *             initOnce.complete();
 *         else
 *             initOnce.failed();
 *     }
 * }
 *
 */
class InitOnce
{
private:
    /// state values
    enum State
    {
        STATE_INIT = 0,         ///< default state
        STATE_BEGIN = 1,        ///< one thread began one-time initialization
        STATE_COMPLETE = 2,     ///< one-time initialization
    };

    Ordered<State> m_state;   ///< Initialization state

public:
    /**
     * Constructor
     */
    InitOnce() :
        m_state(STATE_INIT)
    {
    }

    /**
     * Call at the begin of the initialization code.
     *
     * @return true if initialization needs to be done, false if it already had been done
     */
    bool begin()
    {
        while (m_state != STATE_COMPLETE)
        {
            if (m_state.compareExchange(STATE_INIT, STATE_BEGIN))
                return true;

            // wait and check again
            usleep(100);
        }

        return false;
    }

    /**
     * Call at the end of the initialization code.
     */
    void complete()
    {
        assert(m_state == STATE_BEGIN);
        m_state = STATE_COMPLETE;
    }

    /**
     * Call if initialization code failed.
     */
    void failed()
    {
        assert(m_state == STATE_BEGIN);
        m_state = STATE_INIT;
    }
};

} // namespace ArgusSamples

#endif // CAMERA_MODULES_INITONCE_H

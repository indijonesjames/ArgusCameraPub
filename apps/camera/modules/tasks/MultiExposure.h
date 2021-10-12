
#ifndef TASK_MULTI_EXPOSURE_H
#define TASK_MULTI_EXPOSURE_H

#include <list>

#include <Argus/Argus.h>

#include "ITask.h"
#include "Value.h"
#include "IObserver.h"
#include "TrackedUniqueObject.h"

namespace ArgusSamples
{

/**
 * This task captures multiple streams with different exposure compensation values.
 */
class TaskMultiExposure : public ITask, public IObserver
{
public:
    TaskMultiExposure();
    virtual ~TaskMultiExposure();

    /** @name ITask methods */
    /**@{*/
    virtual bool initialize();
    virtual bool shutdown();
    virtual bool start();
    virtual bool stop();
    /**@}*/

private:
    // the range values need to be initialized first, some Value<> members below use them
    // for the validator
    Value<Argus::Range<uint32_t> > m_exposureStepsRange;    ///< allowed exposure steps

public:
    Value<uint32_t> m_exposureSteps;    ///< steps within the exposure range
    Value<Argus::Range<float> > m_exposureRange;  ///< in eV, e.g. -1,2 results in exposures from
                                        /// -1 eV to +2 eV

private:
    bool m_initialized;                 ///< set if initialized
    bool m_running;                     ///< set if preview is running
    bool m_wasRunning;                  ///< set if was running before the device had been closed
    bool m_prevRunning;                 ///< set if was running before the sensorModeValid is set to false

    /**
     * For each exposure level there is one request where the exposure compensation is set to the
     * correct value. Each request outputs to a stream which is rendered.
     */
    class ExpLevel
    {
    public:
        ExpLevel();
        ~ExpLevel();

        bool shutdown();
        bool initialize(float exposureCompensation);

        TrackedUniqueObj<Argus::Request> m_request; ///< Argus request
        Argus::UniqueObj<Argus::OutputStream> m_outputStream; ///< Argus output stream
    };

    std::list<ExpLevel*> m_expLevels;   ///< exposure level

    /**
     * Callback when the device is opened/closed.
     */
    bool onDeviceOpenChanged(const Observed &source);

    /**
     * Callback when the sensorModeValid is changed.
     */
    bool onSensorModeValidChanged(const Observed &source);

    /**
     * Callback when the exposure range or steps changes.
     */
    bool onParametersChanged(const Observed &source);

    /**
     * Shut down the exposure level streams.
     */
    bool shutdownExpLevels();

    /**
     * Restart when output size changes
     */
    bool restartStreams(const Observed &source);
};

}; // namespace ArgusSamples

#endif // TASK_MULTI_EXPOSURE_H

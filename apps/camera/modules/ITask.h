
#ifndef ITASK_H
#define ITASK_H

namespace ArgusSamples
{

/**
 * Base class for tasks.
 * Tasks provide functionality like capturing of still images or video recording.
 *
 */
class ITask
{
public:
    ITask() { };
    virtual ~ITask() { };

    /**
     * Initialize
     */
    virtual bool initialize() = 0;
    /**
     * Shutdown
     */
    virtual bool shutdown() = 0;

    /**
     * Start
     */
    virtual bool start() = 0;
    /**
     * Stop
     */
    virtual bool stop() = 0;
};

}; // namespace ArgusSamples

#endif // ITASK_H

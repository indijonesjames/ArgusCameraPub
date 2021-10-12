
#ifndef IOBSERVER_H
#define IOBSERVER_H

namespace ArgusSamples
{

class Observed;

/**
 * Interface for classes to get notified from observed classes.
 */
class IObserver
{
public:
    /**
     * Callback function type.
     *
     * @param [in] source
     */
    typedef bool (IObserver::*CallbackFunction)(const Observed &source);

protected:
    virtual ~IObserver() { }
};

};

#endif // IOBSERVER_H

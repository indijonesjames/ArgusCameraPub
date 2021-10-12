
#ifndef OBSERVED_H
#define OBSERVED_H

#include <list>

#include "IObserver.h"

namespace ArgusSamples
{

/**
 * Interface for observed classes. Observers register to observed objects and get called
 * through a callback function.
 */
class Observed
{
public:
    Observed();

    virtual ~Observed();

    /**
     * Register an observer notified when the value has changed. It's an error to register the
     * same observer/callback combination twice.
     *
     * @param observer [in] The observer to register
     * @param callback [in] The callback to register
     */
    bool registerObserver(IObserver *observer, IObserver::CallbackFunction callback);

    /**
     * Unregister an observer
     *
     * @param observer [in] The observer to unregister
     * @param callback [in] The callback to unregister
     */
    bool unregisterObserver(IObserver *observer, IObserver::CallbackFunction callback);

protected:
    bool notifyObservers() const;

private:
    struct Registered
    {
        Registered(IObserver *observer, IObserver::CallbackFunction callback)
            : m_observer(observer)
            , m_callback(callback)
        {
        }
        IObserver *m_observer;
        IObserver::CallbackFunction m_callback;
    };
    std::list<Registered> m_observers;
};

}; // namespace ArgusSamples

#endif // OBSERVED_H

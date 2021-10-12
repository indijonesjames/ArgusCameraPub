
#include "Observed.h"

#include "Error.h"

namespace ArgusSamples
{

Observed::Observed()
{
}

Observed::~Observed()
{
}

bool Observed::registerObserver(IObserver *observer, IObserver::CallbackFunction callback)
{
    // iterate through the registered observers, check if the observer/callback function already
    // exists
    for (std::list<Registered>::const_iterator it = m_observers.begin();
         it != m_observers.end(); ++it)
    {
        const Registered &registered = *it;
        if ((registered.m_observer == observer) && (registered.m_callback == callback))
        {
            ORIGINATE_ERROR("Observer with 'callback' already registered");
        }
    }

    // add to the observer list
    m_observers.push_front(Registered(observer, callback));

    // initial callback to feed with current value
    PROPAGATE_ERROR((observer->*callback)(*this));

    return true;
}

bool Observed::unregisterObserver(IObserver *observer, IObserver::CallbackFunction callback)
{
    // iterate through the registered observers, search for the observer/callback combination and
    // erase
    for (std::list<Registered>::iterator it = m_observers.begin();
         it != m_observers.end(); ++it)
    {
        const Registered &registered = *it;
        if ((registered.m_observer == observer) && (registered.m_callback == callback))
        {
            m_observers.erase(it);
            return true;
        }
    }

    ORIGINATE_ERROR("Observer and callback not found");
}

bool Observed::notifyObservers() const
{
    // iterate through the registered observers, and trigger callback on observers
    for (std::list<Registered>::const_iterator it = m_observers.begin();
         it != m_observers.end(); ++it)
    {
        const Registered &registered = *it;
        PROPAGATE_ERROR(((registered.m_observer)->*(registered.m_callback))(*this));
    }

    return true;
}

}; // namespace ArgusSamples

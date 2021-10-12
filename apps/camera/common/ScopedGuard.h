
#ifndef SCOPED_GUARD_H
#define SCOPED_GUARD_H

namespace ArgusSamples
{

/**
 * RAII-syle class performing an action when control flow leaves the scope. Typically the action
 * to be performed is to undo a previous action in case of an error.
 */
template <typename T> class ScopedGuard
{
public:
    /**
     * Action function type.
     */
    typedef bool (T::*ActionType)();

    /**
     * Constructor
     *
     * @param object [in]   the object to perform the action on
     * @param action [in]   the action to perform
     */
    ScopedGuard(T *object, ActionType action)
        : m_object(object)
        , m_action(action)
    {
    }
    /**
     * Destructor
     */
    ~ScopedGuard()
    {
        leaveScope();
    }

    /**
     * Cancel the action associated with this instance.
     */
    void cancel()
    {
        m_action = NULL;
    }

private:
    T *m_object;
    ActionType m_action;

    /**
     * Called when leaving the scope. Calls action and resets the action.
     */
    void leaveScope()
    {
        if (m_action && m_object)
        {
            if (!(m_object->*m_action)())
                REPORT_ERROR("Action call failed");
            m_object = NULL;
            m_action = NULL;
        }
    }

    /**
     * Hide default/copy constructor and assignment operator
     */
    ScopedGuard();
    ScopedGuard(ScopedGuard &other);
    const ScopedGuard& operator = (const ScopedGuard&);
};

} // namespace ArgusSamples

#endif // SCOPED_GUARD_H

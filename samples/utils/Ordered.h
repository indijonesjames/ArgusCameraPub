
#ifndef CAMERA_MODULES_ORDERED_H
#define CAMERA_MODULES_ORDERED_H

namespace ArgusSamples
{

/**
 * Used for variables shared by threads. Atomic access does inter-thread synchronization, writes
 * from one thread are guaranteed to be visible by other threads.
 */
template <typename T> class Ordered
{
public:
    Ordered(T value)
        : m_value(value)
    {
    }

    void set(T newValue)
    {
        m_value = newValue;
        __sync_synchronize();
    }

    T operator = (T newValue)
    {
        set(newValue);
        return m_value;
    }

    T get() const
    {
        return m_value;
    }

    operator T() const
    {
        return get();
    }

    T operator++()
    {
        return __sync_add_and_fetch(&m_value, 1);
    }

    T operator--()
    {
        return __sync_add_and_fetch(&m_value, -1);
    }

    bool compareExchange(T expectedValue, T newValue)
    {
        return (__sync_val_compare_and_swap(&m_value, expectedValue, newValue) == expectedValue);
    }

private:
    volatile T m_value;

    Ordered(Ordered &other);
    Ordered& operator=(const Ordered&);
};

} // namespace ArgusSamples

#endif // CAMERA_MODULES_ORDERED_H

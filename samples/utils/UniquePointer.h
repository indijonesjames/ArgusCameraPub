
#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include <assert.h>

namespace ArgusSamples
{

/**
 * Gneric unique pointer implementation. A unique pointer owns an object through a pointer and
 * destroys that pointer when UniquePointer goes out of scope
 */
template <typename T> class UniquePointer
{
public:
    /**
     * Constructor
     */
    UniquePointer()
        : m_ptr(NULL)
    {
    }

    /**
     * Constructor of object owning 'ptr'.
     */
    explicit UniquePointer(T *ptr)
        : m_ptr(ptr)
    {
    }

    /**
     * Destructor, Destructs the owned object if such is present.
     */
    ~UniquePointer()
    {
        reset();
    }

    /**
     * Dereferences pointer to the owned object
     */
    T* operator->() const
    {
        return m_ptr;
    }

    /**
     * Dereferences pointer to the owned object
     */
    T* get() const
    {
        return m_ptr;
    }

    /**
     * Returns true if there is an owned object.
     */
#if (__cplusplus > 201100L)
    explicit operator bool() const
#else
    operator bool() const
#endif
    {
        return (m_ptr != NULL);
    }

    /**
     * Release the ownership of the object. Return the owned object.
     */
    T* release()
    {
        T *ptr = m_ptr;
        m_ptr = NULL;
        return ptr;
    }

    /**
     * Replace the owned object, the previously owned object is destructed.
     */
    void reset(T *ptr = NULL)
    {
        delete m_ptr;
        m_ptr = ptr;
    }

    /**
     * Get pointer to pointer to the owned object
     */
    T ** operator &()
    {
        // This is a special addition to be able to use this class with functions creating objects
        // e.g. 'bool func(Type **newObj)'. Make sure this is only used if there is no owned
        // object yet.
        assert(m_ptr == NULL);
        return &m_ptr;
    }

private:
    T *m_ptr;       ///< owned object

    /**
     * Hide copy constructor and assignment operator
     */
    UniquePointer(UniquePointer &right);
    UniquePointer& operator=(const UniquePointer &right);
};

} // namespace ArgusSamples

#endif // UNIQUE_POINTER_H

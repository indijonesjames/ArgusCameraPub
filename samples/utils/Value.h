
#ifndef VALUE_H
#define VALUE_H

#include <string>

#include "Observed.h"
#include "Validator.h"
#include "Error.h"

namespace ArgusSamples
{

/**
 * Value class. Validates the value when it's set. Notify observers when the value change.
 */
template<typename T> class Value : public Observed
{
public:
    Value(const T &value)
        : m_validator(new ValidatorNull<T>())
        , m_value(value)
    {
    }
    Value(IValidator<T> *validator, const T &value)
        : m_validator(validator)
        , m_value(value)
    {
    }
    ~Value()
    {
        delete m_validator;
    }

    /**
     * Implicit conversion back to T
     */
    operator T const & () const
    {
        return m_value;
    }

    /**
     * Get the value.
     */
    const T & get() const
    {
        return m_value;
    }

    /**
     * Set the value. Check if the new value is valid, notify observers if the new value is
     * different from the old value.
     *
     * @param value [in] new value
     * @param forceNotify [in] notify observers even if the value has not changed
     */
    bool set(const T &value, bool forceNotify = false)
    {
        PROPAGATE_ERROR(m_validator->checkValid(value));
        if (!(value == m_value) || forceNotify)
        {
            m_value = value;
            PROPAGATE_ERROR(notifyObservers());
        }
        return true;
    }

    /**
     * Set the value using a string.
     *
     * @param valueString [in] new value represented by a string
     */
    bool setFromString(const char *valueString)
    {
        T value = m_value;
        PROPAGATE_ERROR(m_validator->toValue(valueString, value));
        PROPAGATE_ERROR(set(value));
        return true;
    }

    /**
     * Get the validator.
     */
    IValidator<T> *getValidator()
    {
        return m_validator;
    }

    /**
     * Convert to string
     */
    std::string toString() const
    {
        return m_validator->toString(m_value);
    }

private:
    IValidator<T> *m_validator;
    T m_value;

    // can't be copied
    Value(Value &other);
    const Value& operator = (const Value&);
};

}; // namespace ArgusSamples

#endif // VALUE_H

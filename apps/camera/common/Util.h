
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h> // for uint64_t
#include <limits>   // for numeric_limits

namespace ArgusSamples
{

/**
 * A time value. Supports conversion to different time units.
 */
class TimeValue
{
public:
    TimeValue()
        : m_nSec(0)
    {
    }

    /**
     * Types used for values with various units
     */
    typedef uint64_t SecType;
    typedef uint64_t MSecType;
    typedef uint64_t USecType;
    typedef uint64_t NSecType;
    typedef float CyclesPerSecType;

    // construct a infinite time value
    static TimeValue infinite()
    {
        return TimeValue(std::numeric_limits<NSecType>::max());
    }

    // functions to construct from various time units
    static TimeValue fromSec(float sec)
    {
        return TimeValue(static_cast<NSecType>(sec * 1e9));
    }

    static TimeValue fromSec(SecType sec)
    {
        return TimeValue(sec * 1000000000);
    }

    static TimeValue fromMSec(MSecType mSec)
    {
        return TimeValue(mSec * 1000000);
    }

    static TimeValue fromUSec(USecType uSec)
    {
        return TimeValue(uSec * 1000);
    }

    static TimeValue fromNSec(NSecType nSec)
    {
        return TimeValue(nSec);
    }

    static TimeValue fromCycelsPerSec(CyclesPerSecType cyclesPerSec)
    {
        return TimeValue(static_cast<NSecType>(1e9 / static_cast<double>(cyclesPerSec)));
    }

    // functions to set from various time uints
    void setFromSec(SecType sec)
    {
        m_nSec = sec * 1000000000;
    }

    void setFromMSec(MSecType mSec)
    {
        m_nSec = mSec * 1000000;
    }

    void setFromUSec(USecType uSec)
    {
        m_nSec = uSec * 1000;
    }

    void setFromNSec(NSecType nSec)
    {
        m_nSec = nSec;
    }

    // functions to convert to various time units
    SecType toSec() const
    {
        return m_nSec / 1000000000;
    }

    MSecType toMSec() const
    {
        return m_nSec / 1000000;
    }

    USecType toUSec() const
    {
        return m_nSec / 1000;
    }

    NSecType toNSec() const
    {
        return m_nSec;
    }

    CyclesPerSecType toCyclesPerSec() const
    {
        if (m_nSec == 0.0f)
            return std::numeric_limits<CyclesPerSecType>::max();

        return static_cast<CyclesPerSecType>(1e9 / static_cast<double>(m_nSec));
    }

    // comparision and equality operators
    bool operator == (const TimeValue& rhs) const
    {
        return (m_nSec == rhs.m_nSec);
    }

    bool operator != (const TimeValue &rhs) const
    {
        return !(operator == (rhs));
    }

    bool operator < (const TimeValue& rhs) const
    {
        return (m_nSec < rhs.m_nSec);
    }

    bool operator >= (const TimeValue &rhs) const
    {
        return !(operator < (rhs));
    }

    bool operator <= (const TimeValue &rhs) const
    {
        return (m_nSec <= rhs.m_nSec);
    }

    bool operator > (const TimeValue &rhs) const
    {
        return !(operator <= (rhs));
    }

    TimeValue operator + (const TimeValue& rhs) const
    {
        return (m_nSec + rhs.m_nSec);
    }

    TimeValue operator - (const TimeValue& rhs) const
    {
        return (m_nSec - rhs.m_nSec);
    }

private:
    TimeValue(NSecType value)
        : m_nSec(value)
    {
    }

    NSecType m_nSec;
};

/*!
 * Get the current time.
 */
TimeValue getCurrentTime();

/*
 * Validate filename by attempting to open file for writing
 */
bool validateOutputPath(const char* filename);

/*!
 * Supported still image file formats
 */
typedef enum
{
    STILL_FILE_TYPE_JPG,
    STILL_FILE_TYPE_HEADERLESS
} StillFileType;

}; // namespace ArgusSamples

#endif // UTIL_H

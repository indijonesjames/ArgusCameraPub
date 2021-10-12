
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define LOG_ERROR(_file, _func, _line, _str, ...) \
    do { \
        fprintf(stderr, "Error generated. %s, %s:%d ", _file, _func, _line); \
        fprintf(stderr, _str, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } \
    while (0)

/**
 * Simply report an error.
 */
#define REPORT_ERROR(_str, ...) \
    do { \
        LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, (_str), ##__VA_ARGS__); \
    } while (0)

/**
 * Report and return an error that was first detected in the current method.
 */
#define ORIGINATE_ERROR(_str, ...) \
    do { \
        LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, (_str), ##__VA_ARGS__); \
        return false; \
    } while (0)

/**
 * Report an error that was first detected in the current method, then jumps to the "fail:" label.
 */
#define ORIGINATE_ERROR_FAIL(_str, ...) \
    do { \
        LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, (_str), ##__VA_ARGS__); \
        goto fail; \
    } while (0)

/**
 * Report and return an error that was first detected in some method
 * called by the current method.
 */
#define PROPAGATE_ERROR(_err) \
    do { \
        bool peResult = (_err); \
        if (peResult != true) \
        { \
            LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, "(propagating)"); \
            return false; \
        } \
    } while (0)

/**
 * Calls another function, and if an error was returned it is reported before jumping to the
 * "fail:" label.
 */
#define PROPAGATE_ERROR_FAIL(_err, ...) \
    do { \
        bool peResult = (_err); \
        if (peResult != true) \
        { \
            LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, "(propagating)"); \
            goto fail; \
        } \
    } while (0)

/**
 * Calls another function, and if an error was returned it is reported. The caller does not return.
 */
#define PROPAGATE_ERROR_CONTINUE(_err) \
    do { \
        bool peResult = (_err); \
        if (peResult != true) \
        { \
            LOG_ERROR(__FILE__, __FUNCTION__, __LINE__, "(propagating)"); \
        } \
    } while (0)

#endif // ERROR_H

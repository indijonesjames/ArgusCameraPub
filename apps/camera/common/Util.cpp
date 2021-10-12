
#include <sys/time.h>
#include <stddef.h>
#include <cerrno>

#include <stdio.h>

#include "Util.h"
#include "Error.h"
#include "string.h"

namespace ArgusSamples
{

TimeValue getCurrentTime()
{
    struct timeval val;

    gettimeofday(&val, NULL);

    return
        TimeValue::fromUSec(val.tv_usec) +
        TimeValue::fromSec(static_cast<TimeValue::SecType>(val.tv_sec));
}

bool validateOutputPath(const char* filename)
{
    // Test ability to write to indicated filename
    FILE *fp = fopen(filename,"w");
    if (fp)
    {
        fclose(fp);
        return true;
    }
    else
    {
        fprintf(stderr, "--------------------------------------------------------------------\n");
        fprintf(stderr, "Failure to open file '%s' for writing.\n", filename);
        fprintf(stderr, "Error return code:%d (%s)\n", errno, strerror(errno));
        if (errno == EACCES)
        {
            fprintf(stderr, "Use command line parameter --outputpath to\n");
            fprintf(stderr, "point to a directory you have permission to write into.\n");
#ifdef __ANDROID__
            fprintf(stderr, "As in: argus_camera --outputpath='/sdcard/DCIM' -s1 -x\n");
#else
            fprintf(stderr, "As in: argus_camera --outputpath='/tmp' -s1 -x\n");
#endif
        }
        fprintf(stderr, "--------------------------------------------------------------------\n");
        return false;
    }
}

}; // namespace ArgusSamples

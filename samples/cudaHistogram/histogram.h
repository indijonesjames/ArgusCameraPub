
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cuda.h>

#define HISTOGRAM_BINS 64

extern float histogram(CUsurfObject surface, unsigned int width, unsigned int height,
    unsigned int *histogram);

#endif // HISTOGRAM_H

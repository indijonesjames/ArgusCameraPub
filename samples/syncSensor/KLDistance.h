
#ifndef KLDISTANCE_H
#define KLDISTANCE_H

#include <cuda.h>

/*
 * Computes the KL divergence of two histograms from each other.
 * @param[in] histOne a vector of size bins, containing the not normalized histogram.
 * @param[in] histTwo a vector of size bins, containing the not normalized histogram.
 * @param[in] bins the number of entrys in both histograms
 * @param[in] size the sum of the histograms bins.
 * @param[out] distance, the computed kl distance between the two histograms.
 */
extern float computeKLDistance(unsigned int *histOne,
                               unsigned int *histTwo,
                               const unsigned int bins,
                               const unsigned int size,
                               float *disparity);

#endif // KLDISTANCE_H

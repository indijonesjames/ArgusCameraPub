
#ifndef ARGUS_SAMPLES_UTILS_RECTUTILS_H_
#define ARGUS_SAMPLES_UTILS_RECTUTILS_H_

#include "Argus/Argus.h"

namespace ArgusSamples
{

namespace RectUtils
{

using namespace Argus;

/**
 * Function to get aspect-ratio-preserving clip rectangle given input and output resolutions.
 * Outputting to a stream with an aspect ratio that does not match the input (sensor) aspect ratio
 * leads to a non-square scaling operation in libargus that should generally be avoided due to
 * performance and image quality reasons. This method will return a clipping rectangle that may be
 * used for the stream settings of a capture request so that the input will be clipped to match the
 * aspect ratio of the output, maintaining square pixels throughout the pipeline.
 * @param[in] inputRes: input resolution
 * @param[in] outputRes: output resolution
 * @returns Rectangle<float>: the aspect-ratio-preserving clip rectangle with either the right
 * and left equally clipped, or the top and bottom equally clipped.  No clipping is done if the
 * input and output aspect ratios are equal.
 */
Rectangle<float> arPreservingClip(const Size2D<uint32_t> &inputRes,
                                  const Size2D<uint32_t> &outputRes);

/**
 * Helper function to get the default clip rectangle.
 */
inline Rectangle<float> defaultClip()
{
    return Rectangle<float>(0.0F, 0.0F, 1.0F, 1.0F);
}

#endif /* ARGUS_SAMPLES_UTILS_RECTUTILS_H_ */

} // namespace RectUtils

} // namespace ArgusSamples

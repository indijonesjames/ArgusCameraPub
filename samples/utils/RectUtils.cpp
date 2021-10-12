
#include "RectUtils.h"
#include "Error.h"

namespace ArgusSamples
{

namespace RectUtils
{

Rectangle<float> arPreservingClip(const Size2D<uint32_t> &inputRes,
                                  const Size2D<uint32_t> &outputRes)
{
    // Prevent divide-by-zero.
    if (inputRes.width() == 0 || inputRes.height() == 0 ||
        outputRes.width() == 0 || outputRes.height() == 0)
    {
        REPORT_ERROR("Bad params: inputRes[%u x %u], outputRes[%u x %u]",
                inputRes.width(), inputRes.height(), outputRes.width(), outputRes.height());

        return defaultClip();
    }

    const float inputAspectRatio = inputRes.width() / static_cast<float>(inputRes.height());

    const float outputAspectRatio = outputRes.width() / static_cast<float>(outputRes.height());

    // Determine the side and top clips from the sensor and output aspect ratios.
    float sideClip = 0.0F;
    float topClip = 0.0F;

    if (outputAspectRatio < inputAspectRatio)
    {
        // Output is skinnier than input -- clip away sides to preserve square pixels.
        sideClip = (1.0F - outputAspectRatio/inputAspectRatio) / 2.0F;
    }
    else
    {
        // Output is wider or same as input -- clip away top/bottom.
        topClip = (1.0F - inputAspectRatio/outputAspectRatio) / 2.0F;
    }

    return Rectangle<float>(sideClip, topClip, 1.0F - sideClip, 1.0F - topClip);
}

} // namespace RectUtils

} // namespace ArgusSamples





/**
 * @file
 * <b>Libargus Extension: Non Linear Histogram</b>
 *
 * @b Description: This file defines the Non Linear Histogram extension, and provide
 * methods to interpret non linear data in case of compressed data
 */

#ifndef _ARGUS_NON_LINEAR_HISTOGRAM_H
#define _ARGUS_NON_LINEAR_HISTOGRAM_H

namespace Argus
{

/**
 * This adds a method to interpret the compressed histogram data correctly
 * It introduces one new interface:
 *  -INonLinearHistogram -returns a list of bin indices that have been normalized. In case
 *                        of WDR sensors, we compress 16 bit output data as ISP4 has
 *                        a max support for 14 bit data. Hence these introduced non-linearities
 *                        should be inverted. The indices are first corrected for the
 *                        PreispCompression and then for the white balance gains. Eventually
 *                        the getHistogram() API will incorporate this, but untill the new
 *                        API design is finalized, this will be a temporary solution.
 * @defgroup ArgusExtNonLinearHistogram Ext::NonLinearHistogram
 * @ingroup ArgusExtensions
 */
DEFINE_UUID(ExtensionName, EXT_NON_LINEAR_HISTOGRAM, 45b6a850,e801,11e8,b568,08,00,20,0c,9a,66);

namespace Ext
{

/**
 * @class INonLinearHistogram
 *
 * Interface used to query the metadata to correctly interpret the compressed histogram data.
 * Returns the normalized bin values to correctly interpret the compressed bayer histogram
 * data. This interface will only be exposed in case the histogram is compressed.
 *
 * This interface is available from:
 *   - Histogram child objects returned by ICaptureMetadata::getBayerHistogram()
 *
 * @ingroup ArgusCaptureMetadata ArgusExtNonLinearHistogram
 */
DEFINE_UUID(InterfaceID, IID_NON_LINEAR_HISTOGRAM, 6e337ec0,e801,11e8,b568,08,00,20,0c,9a,66);
class INonLinearHistogram : public Interface
{
public:
    static const InterfaceID& id() { return IID_NON_LINEAR_HISTOGRAM; }

    /**
     * Returns the average bayer values of bins for bayer histogram data.
     *
     * @param[out] binValues Returns the normalized average bin values (float in [0,1]) for
     *             bins provided by IBayerHistogram interface.
     *             In case the histogram data provided by IBayerHistogram::getHistogram()
     *             is non-linear, this method will return a vector having the same size as
     *             histogram (i.e. IBayerHistogram::getBinCount()), and will contain
     *             normalized bayer colour values to which the histogram bin of the same
     *             index corresponds.
     *
     *             For Example, in case of Non Linear Histogram
     *
     *             IBayerHistogram->getHistogram(&histogram);
     *             INonLinearHistogram->getBinValues(&values);
     *
     *             for(int i = 0 ; i < histogram.size() ; i++)
     *             {
     *                  cout<<" bin: " << i
     *                      <<" normalized bin Value: " << values[i]
     *                      <<" frequency: " << histogram[i];
     *             }
     */
    virtual Status getHistogramBinValues(std::vector< BayerTuple<float> >* binValues) const = 0;

protected:
    ~INonLinearHistogram() {}
};

} // namespace Ext

} // namespace Argus

#endif // _ARGUS_NON_LINEAR_HISTOGRAM_H

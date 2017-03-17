#include "parameters/disparitymapparameters.hpp"

#include "widgets/disparitymapparameterswidget.hpp"

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
DisparityMapParameters::DisparityMapParameters() :
    Parameters(),
    algorithm(0),
    prefilterType(0),
    preFilterSize(9),
    preFilterCap(31),
    SADWindowSize(21),
    minDisparity(0),
    numberOfDisparities(64),
    textureThreshold(10),
    uniquenessRatio(15),
    speckleWindowSize(0),
    speckleRange(0),
    disp12MaxDiff(-1),
    averageTextureThreshold(0.0f),
    fullDP(false) {}

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
DisparityMapParameters::DisparityMapParameters(QWidget* view) :
    Parameters(view),
    algorithm(0),
    prefilterType(0),
    preFilterSize(9),
    preFilterCap(31),
    SADWindowSize(21),
    minDisparity(0),
    numberOfDisparities(64),
    textureThreshold(10),
    uniquenessRatio(15),
    speckleWindowSize(0),
    speckleRange(0),
    disp12MaxDiff(-1),
    averageTextureThreshold(0.0f),
    fullDP(false) {}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
DisparityMapParameters::~DisparityMapParameters() {}

/**************************************************************
 **************************************************************
 *
 * Sets disparity map algorithm.
 *
 **************************************************************/
void DisparityMapParameters::setAlgorithm(int value)
{
    algorithm = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets Pre-filter type.
 *
 **************************************************************/
void DisparityMapParameters::setPreFilterType(int value)
{
    prefilterType = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets Pre-filter size.
 *
 **************************************************************/
void DisparityMapParameters::setPrefilterSize(int value)
{
    preFilterSize = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * sets truncation value for the prefiltered image pixels.
 *
 **************************************************************/
void DisparityMapParameters::setPreFilterCap(int value)
{
    preFilterCap = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets Sum of Absolute Difference.
 *
 **************************************************************/
void DisparityMapParameters::setSADWindowSize(int value)
{
    SADWindowSize = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets minimum disparity.
 *
 **************************************************************/
void DisparityMapParameters::setMinDisparity(int value)
{
    minDisparity = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets number of disparities.
 *
 **************************************************************/
void DisparityMapParameters::setNumberOfDisparities(int value)
{
    numberOfDisparities = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets post filtering computation for pixels with textured
 * enough neighborhood.
 *
 **************************************************************/
void DisparityMapParameters::setTextureThreshold(int value)
{
    textureThreshold = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets uniqueness ratio. Accepts the computed disparity d*
 * only if SAD(d) >= SAD(d*)*(1 + uniquenessRatio/100.) for
 * any d != d*+/-1 within the search range.
 *
 **************************************************************/
void DisparityMapParameters::setUniquenessRatio(int value)
{
    uniquenessRatio = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets disparity variation window.
 *
 **************************************************************/
void DisparityMapParameters::setSpeckleWindowSize(int value)
{
    speckleWindowSize = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets acceptable range of variation in window.
 *
 **************************************************************/
void DisparityMapParameters::setSpeckleRange(int value)
{
    speckleRange = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets the maximum allowed difference (in integer pixel
 * units) in the left-right disparity check.
 *
 **************************************************************/
void DisparityMapParameters::setDisp12MaxDiff(int value)
{
    disp12MaxDiff = value;
    notify();
}

void DisparityMapParameters::setAverageTextureThreshold(float value)
{
    averageTextureThreshold = value;
    notify();
}

/**************************************************************
 **************************************************************
 *
 * Sets Full-scale two-pass dynamic.
 *
 **************************************************************/
void DisparityMapParameters::setFullDP(bool value)
{
    fullDP = value;
    notify();
}

int DisparityMapParameters::getAlgorithm() const
{
    return algorithm;
}

int DisparityMapParameters::getPreFilterType() const
{
    return prefilterType;
}

int DisparityMapParameters::getPrefilterSize() const
{
    return preFilterSize;
}

int DisparityMapParameters::getPreFilterCap() const
{
    return preFilterCap;
}

int DisparityMapParameters::getSADWindowSize() const
{
    return SADWindowSize;
}

int DisparityMapParameters::getMinDisparity() const
{
    return minDisparity;
}

int DisparityMapParameters::getNumberOfDisparities() const
{
    return numberOfDisparities;
}

int DisparityMapParameters::getTextureThreshold() const
{
    return textureThreshold;
}

int DisparityMapParameters::getUniquenessRatio() const
{
    return uniquenessRatio;
}

int DisparityMapParameters::getSpeckleWindowSize() const
{
    return speckleWindowSize;
}

int DisparityMapParameters::getSpeckleRange() const
{
    return speckleRange;
}

int DisparityMapParameters::getDisp12MaxDiff() const
{
    return disp12MaxDiff;
}

float DisparityMapParameters::getAverageTextureThreshold() const
{
    return averageTextureThreshold;
}

bool DisparityMapParameters::getFullDP() const
{
    return fullDP;
}

void DisparityMapParameters::update()
{
    DisparityMapParametersWidget* dpw = static_cast<DisparityMapParametersWidget*>(view());
    setRealTime(dpw->hasRealTime());
    algorithm = dpw->getAlgorithm();
    prefilterType = dpw->getPreFilterType();
    preFilterSize = dpw->getPrefilterSize();
    preFilterCap = dpw->getPreFilterCap();
    SADWindowSize = dpw->getSADWindowSize();
    minDisparity = dpw->getMinDisparity();
    numberOfDisparities = dpw->getNumberOfDisparities();
    textureThreshold = dpw->getTextureThreshold();
    uniquenessRatio = dpw->getUniquenessRatio();
    speckleWindowSize = dpw->getSpeckleWindowSize();
    speckleRange = dpw->getSpeckleRange();
    disp12MaxDiff = dpw->getDisp12MaxDiff();
    averageTextureThreshold = dpw->getAverageTextureThreshold();
    fullDP = dpw->getFullDP();
}

void DisparityMapParameters::notify()
{
    if(view())
    {
        view()->update();
    }
}

/*!
 * \file disparitymapparameters.hpp
 * \brief Header containing the declaration of the DisparityMapParameters class which provides the needed parameters for the disparity map computation.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef DISPARITYMAPPARAMETERS_HPP
#define DISPARITYMAPPARAMETERS_HPP

#include "parameters/parameters.hpp"

/*!
 * \class DisparityMapParameters
 * \inherits Parameters
 * \brief The DisparityMapParameters class is used to retrieve the required parameters for the disparity map computation.
 *        This class is Model class which is designed to be used in conjunction with the DisparityMapParametersWidget object.
 *        The DisparityMapParameters class is a part of the Observer pattern evocated in the
 */
class DisparityMapParameters : public Parameters
{
public:
    DisparityMapParameters();
    DisparityMapParameters(QWidget* view);
    ~DisparityMapParameters();

    void setAlgorithm(int value);
    void setPreFilterType(int value);
    void setPrefilterSize(int value);
    void setPreFilterCap(int value);
    void setSADWindowSize(int value);
    void setMinDisparity(int value);
    void setNumberOfDisparities(int value);
    void setTextureThreshold(int value);
    void setUniquenessRatio(int value);
    void setSpeckleWindowSize(int value);
    void setSpeckleRange(int value);
    void setDisp12MaxDiff(int value);
    void setAverageTextureThreshold(float value);
    void setFullDP(bool value);

    int getAlgorithm() const;
    int getPreFilterType() const;
    int getPrefilterSize() const;
    int getPreFilterCap() const;
    int getSADWindowSize() const;
    int getMinDisparity() const;
    int getNumberOfDisparities() const;
    int getTextureThreshold() const;
    int getUniquenessRatio() const;
    int getSpeckleWindowSize() const;
    int getSpeckleRange() const;
    int getDisp12MaxDiff() const;

    float getAverageTextureThreshold() const;

    bool getFullDP() const;

    void update();
    void notify();

private:
    int algorithm;

private:
    int prefilterType;
    int preFilterSize;
    int preFilterCap;
    int SADWindowSize;
    int minDisparity;
    int numberOfDisparities;
    int textureThreshold;
    int uniquenessRatio;
    int speckleWindowSize;
    int speckleRange;
    int disp12MaxDiff;

    float averageTextureThreshold;

    bool fullDP;
};

#endif // DISPARITYMAPPARAMETERS_HPP

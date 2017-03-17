#ifndef DISPARITYMAPPARAMETERSWIDGET_HPP
#define DISPARITYMAPPARAMETERSWIDGET_HPP

#include "widgets/parameterswidget.hpp"

class QComboBox;
class QSlider;
class QLabel;
class QDoubleSpinBox;

class DisparityMapParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    DisparityMapParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);
    ~DisparityMapParametersWidget();

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

    void notify();
    void update();

private slots:
    void enableRealtime();
    void enableItems(int index);

private slots:
    void setAlgorithm(int);
    void setPreFilterType(int);
    void setPrefilterSize(int);
    void setPreFilterCap(int);
    void setSADWindowSize(int);
    void setMinDisparity(int);
    void setNumberOfDisparities(int);
    void setTextureThreshold(int);
    void setUniquenessRatio(int);
    void setSpeckleWindowSize(int);
    void setSpeckleRange(int);
    void setDisp12MaxDiff(int);
    void setAverageTextureThreshold(double);
    void setFullDP(int);

private:
    QComboBox* algorithmComboBox;
    QComboBox* preFilterTypeComboBox;

    QSlider* preFilterSizeSlider;
    QSlider* preFilterCapSlider;
    QSlider* SADWindowSizeSlider;
    QSlider* minDisparitySlider;
    QSlider* numberOfDisparitiesSlider;
    QSlider* textureThresholdSlider;
    QSlider* uniquenessRatioSlider;
    QSlider* speckleWindowSizeSlider;
    QSlider* speckleRangeSlider;
    QSlider* disp12MaxDiffSlider;

    QDoubleSpinBox* averageTextureThresholdSpinBox;

    QCheckBox* fullDPCheckBox;

private:
    QLabel* algorithmLabel;
    QLabel* preFilterTypeLabel;
    QLabel* preFilterSizeLabel;
    QLabel* preFilterCapLabel;
    QLabel* SADWindowSizeLabel;
    QLabel* minDisparityLabel;
    QLabel* numberOfDisparitiesLabel;
    QLabel* textureThresholdLabel;
    QLabel* uniquenessRatioLabel;
    QLabel* speckleWindowSizeLabel;
    QLabel* speckleRangeLabel;
    QLabel* disp12MaxDiffLabel;
    QLabel* averageTextureThresholdLabel;

    QLabel* preFilterSizeValueLabel;
    QLabel* preFilterCapValueLabel;
    QLabel* SADWindowSizeValueLabel;
    QLabel* minDisparityValueLabel;
    QLabel* numberOfDisparitiesValueLabel;
    QLabel* textureThresholdValueLabel;
    QLabel* uniquenessRatioValueLabel;
    QLabel* speckleWindowSizeValueLabel;
    QLabel* speckleRangeValueLabel;
    QLabel* disp12MaxDiffValueLabel;
};

#endif // DISPARITYMAPPARAMETERSWIDGET_HPP

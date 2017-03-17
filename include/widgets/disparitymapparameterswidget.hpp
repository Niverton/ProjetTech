/*!
 * \file disparitymapparameterswidget.hpp
 * \brief Header containing the declaration of the DisparityMapParametersWidget class which allows to manipulate <i>disparity map</i> parameters.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef DISPARITYMAPPARAMETERSWIDGET_HPP
#define DISPARITYMAPPARAMETERSWIDGET_HPP

#include "widgets/parameterswidget.hpp"

class QComboBox;
class QSlider;
class QLabel;
class QDoubleSpinBox;

/*!
 * \class DisparityMapParametersWidget
 * \inherits ParametersWidget
 * \brief The DisparityMapParametersWidget class allows the user to manipulate <i>disparity map</i> related parameters in order to generate a
 *        <i>disparity map</i> from a stereo pair.
 *
 *        This class is a member of the ParameterWidget family of objects. It is an <i>observable</i> object which is meant to
 *        be bound to its corresponding <i>Model</i>: the DisparityMapParameters object.
 *
 *        This class allows the user to select a specific algorithm which has to be applied to a stereo pair:
 *          - Stereo Block Matching
 *          - Stereo Semi-Global Block Matching
 *          - Stereo Block Matching (GPU)
 *
 *        Depending on the selected algorithm, the content of the <i>widget</i> is dynamically adapted.
 *
 *        Without considering the chosen algorithm, this class will give the user an access to:
 *          - The <i>prefilter type</i> parameter;
 *          - The <i>prefilter cap</i> parameter;
 *          - The <i>prefilter size</i> parameter;
 *          - The <i>Sum of Absolute Differences (SAD) window size</i> parameter;
 *          - The <i>minimum disparity</i> parameter;
 *          - The <i>number of disparities</i> parameter;
 *          - The <i>texture threshold</i> parameter;
 *          - The <i>uniqueness ratio</i> parameter;
 *          - The <i>speckle window</i> size parameter;
 *          - The <i>speckle range</i> parameter;
 *          - The <i>maximum allowed difference (in integer pixel units) in the left-right disparity check</i> parameter;
 *          - The <i>average texture threshold</i> parameter;
 *          - The <i>full dynamic pass</i> parameter.
 *
 *        If no <i>Model</i> is specified during the instance of this object, default values are affected to the manipulated
 *        paramters. Consequently, a call to the ParametersWidget::attach() method will be required.
 *
 *        The <i>Real Time Rendering</i> check box will be only available once the <i>Apply</i> button will be clicked.
 *        The <i>Apply</i> button is designed to trigger the instance of a StereoTransformWidget object which will render
 *        the disparity map from a stereo pair.
 * \see The \ref observermodule for more details about the relation between <i>observers</i> and <i>observables</i>.
 * \see The ParametersWidget class to get more details about the relation between the Paramaters family of objects and the
 *      ParametersWidget family of objects.
 * \see The ImageProcessor class for more details about the <i>disparity map</i> transformation.
 * \see ParametersWidget::attach()
 * \see The StereoTransformWidget class
 */
class DisparityMapParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instanciate a DisparityMapParametersWidget.
     *        The DisparityMapParametersWidget is designed to manipulate <i>disparity map</i> related parameters
     *        before applying any image transformation. This object is a member of the <i>observable</i> family
     *        of objects. It is meant to be bound to the BlurParameters object which is corresponding to
     *        its <i>observer</i>.
     *
     *        All the <i>GUI</i> components are built during the process.
     * \param parent    Parent widget.
     * \param model     BlurParameters <i>observer</i>.
     * \see ParametersWidget::attach()
     */
    DisparityMapParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);

    /*!
     * \brief Default destructor.
     */
    ~DisparityMapParametersWidget();

    /*!
     * \brief Gets the algorithm.
     * \return The alorithm selected by the user. This method returns:
     *          - 0 if the selected algorithm is the Stereo Block Matching one;
     *          - 1 if the selected algorithm is the Stereo Semi-Global Block Matching one;
     *          - 2 if the selected algorithm is the Stereo Block Matching (GPU) one.
     */
    int getAlgorithm() const;

    /*!
     * \brief Gets the <i>prefilter type</i>.
     * \return The <i>prefilter type</i> selected by the user. This method returns:
     *          - 0 if the selected <i>prefilter type</i> is corresponding to <i>normalized response</i>;
     *          - 1 if the selected <i>prefilter type</i> is corresponding to <i>Sobel</i>;
     *          - 2 if the selected <i>prefilter type</i> is corresponding to <i>narrow preset</i>.
     */
    int getPreFilterType() const;

    /*!
     * \brief Gets the <i>prefilter size</i>.
     * \return The <i>prefilter size</i> entered by the user.
     */
    int getPrefilterSize() const;

    /*!
     * \brief Gets the <i>prefilter cap</i>.
     * \return The <i>prefilter cap</i> entered by the user.
     */
    int getPreFilterCap() const;

    /*!
     * \brief Gets the <i>Sum of Absolute Differences (SAD) window size</i>.
     * \return The <i>Sum of Absolute Differences (SAD) window size</i> entered by the user.
     */
    int getSADWindowSize() const;

    /*!
     * \brief Gets the <i>minimum disparity</i>.
     * \return The <i>minimum disparity</i> entered by the user.
     */
    int getMinDisparity() const;

    /*!
     * \brief Gets the <i>number of disparities</i>.
     * \return The <i>number of disparities</i> entered by the user.
     */
    int getNumberOfDisparities() const;

    /*!
     * \brief Gets the <i>texture threshold</i>.
     * \return The <i>texture threshold</i> entered by the user.
     */
    int getTextureThreshold() const;

    /*!
     * \brief Gets the <i>uniqueness ratio</i>.
     * \return The <i>uniqueness ratio</i> entered by the user.
     */
    int getUniquenessRatio() const;

    /*!
     * \brief Gets the <i>speckle window size</i>.
     * \return The <i>speckle window size</i> entered by the user.
     */
    int getSpeckleWindowSize() const;

    /*!
     * \brief Gets the <i>speckle range</i>.
     * \return The <i>speckle range</i> entered by the user.
     */
    int getSpeckleRange() const;

    /*!
     * \brief Gets the <i>maximum allowed difference (in integer pixel units) in the left-right disparity check</i>.
     * \return The <i>maximum allowed difference (in integer pixel units) in the left-right disparity check</i> entered by the user.
     */
    int getDisp12MaxDiff() const;

    /*!
     * \brief Gets the <i>average texture threshold</i>.
     * \return The <i>average texture threshold</i> entered by the user.
     */
    float getAverageTextureThreshold() const;

    /*!
     * \brief Gets the <i>full dynamic pass</i> status.
     * \return The <i>full dynamic pass</i> status selected by the user.
     */
    bool getFullDP() const;

    /*!
     * \brief Pulls the data from the <i>observable</i> and inserts them in the attached DisparityMapParameters <i>observer</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see DisparityMapParametersWidget::DisparityMapParametersWidget()
     * \see ParametersWidget::attach()
     */
    void notify();

    /*!
     * \brief Pulls the data from the DisparityMapParameters <i>observer</i> and inserts them in the <i>observable</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see DisparityMapParametersWidget::DisparityMapParametersWidget()
     * \see ParametersWidget::attach()
     */
    void update();

private slots:
    /*!
     * \brief Allows to enable the <i>Real Time Rendering</i> check box once the <i>Apply</i> button has been clicked.
     *        The <i>Apply</i> button is designed to trigger the instance of a StereoTransformWidget object which will render
     *        the disparity map from a stereo pair.
     */
    void enableRealtime();

    /*!
     * \brief Allows to dynamically display <i>disparity map</i> related paramters according to the selected algorithm.
     * \param index Algorithm identifier:
     *                  - 0 for the Stereo Block Matching one;
     *                  - 1 for the Stereo Semi-Global Block Matching one;
     *                  - 2 for the Stereo Block Matching (GPU) one.
     */
    void enableItems(int index);

private slots:
    /*!
     * \brief Sets the algorithm.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     *        Depending on the selected algorithm, the <i>GUI</i> may be dynamically adapted.
     * \param value Algorithm identifier:
     *                  - 0 for the Stereo Block Matching one;
     *                  - 1 for the Stereo Semi-Global Block Matching one;
     *                  - 2 for the Stereo Block Matching (GPU) one.
     */
    void setAlgorithm(int value);

    /*!
     * \brief Sets the <i>prefilter type</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>prefilter type</i> identifier:
     *                  - 0 for <i>normalized response</i>;
     *                  - 1 for <i>Sobel</i>;
     *                  - 2 for <i>narrow preset</i>.
     */
    void setPreFilterType(int value);

    /*!
     * \brief Sets the <i>prefilter size</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>prefilter size</i>.
     */
    void setPrefilterSize(int value);

    /*!
     * \brief Sets the <i>prefilter cap</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>prefilter cap</i>.
     */
    void setPreFilterCap(int value);

    /*!
     * \brief Sets the <i>Sum of Absolute Differences (SAD) window size</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>Sum of Absolute Differences (SAD) window size</i>.
     */
    void setSADWindowSize(int value);

    /*!
     * \brief Sets the <i>minimum disparity</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>minimum disparity</i>.
     */
    void setMinDisparity(int value);

    /*!
     * \brief Sets the <i>number of disparities</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>number of disparities</i>.
     */
    void setNumberOfDisparities(int value);

    /*!
     * \brief Sets the <i>texture threshold</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>texture threshold</i>.
     */
    void setTextureThreshold(int value);

    /*!
     * \brief Sets the <i>uniqueness ratio</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>uniqueness ratio</i>.
     */
    void setUniquenessRatio(int value);

    /*!
     * \brief Sets the <i>speckle window size</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>speckle window size</i>.
     */
    void setSpeckleWindowSize(int value);

    /*!
     * \brief Sets the <i>speckle range</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>speckle range</i>.
     */
    void setSpeckleRange(int value);

    /*!
     * \brief Sets the <i>maximum allowed difference (in integer pixel units) in the left-right disparity check</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>maximum allowed difference (in integer pixel units) in the left-right disparity check</i>.
     */
    void setDisp12MaxDiff(int value);

    /*!
     * \brief Sets the <i>average texture threshold</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>average texture threshold</i>.
     */
    void setAverageTextureThreshold(double value);

    /*!
     * \brief Sets the <i>full dynamic pass</i> status.
     * \param value The <i>full dynamic pass</i> status.
     */
    void setFullDP(int value);

private:
    QComboBox* algorithmComboBox;                           /*!< Algorithm combo box. */
    QComboBox* preFilterTypeComboBox;                       /*!< <i>Prefilter type</i> combo box. */

    QSlider* preFilterSizeSlider;                           /*!< <i>Prefilter size</i> slider. */
    QSlider* preFilterCapSlider;                            /*!< <i>Prefilter cap</i> slider. */
    QSlider* SADWindowSizeSlider;                           /*!< <i>Sum of Absolute Differences (SAD) window size</i> slider. */
    QSlider* minDisparitySlider;                            /*!< <i>Minimum disparity</i> slider. */
    QSlider* numberOfDisparitiesSlider;                     /*!< <i>Number of disparities</i> slider. */
    QSlider* textureThresholdSlider;                        /*!< <i>Texture threshold</i> slider. */
    QSlider* uniquenessRatioSlider;                         /*!< <i>Uniqueness ratio</i> slider. */
    QSlider* speckleWindowSizeSlider;                       /*!< <i>Speckle window size</i> slider. */
    QSlider* speckleRangeSlider;                            /*!< <i>Speckle range</i> slider. */
    QSlider* disp12MaxDiffSlider;                           /*!< <i>Maximum allowed difference (in integer pixel units) in the left-right disparity check</i> slider. */

    QDoubleSpinBox* averageTextureThresholdSpinBox;         /*!< <i>Average texture threshold</i> spin box. */

    QCheckBox* fullDPCheckBox;                              /*!< <i>Full dynamic pass</i> check box. */

private:
    QLabel* algorithmLabel;                                 /*!< Algorithm label. */
    QLabel* preFilterTypeLabel;                             /*!< <i>Prefilter type</i> label.*/
    QLabel* preFilterSizeLabel;                             /*!< <i>Prefilter size</i> label.*/
    QLabel* preFilterCapLabel;                              /*!< <i>Prefilter cap</i> label. */
    QLabel* SADWindowSizeLabel;                             /*!< <i>Sum of Absolute Differences (SAD) window size</i> label. */
    QLabel* minDisparityLabel;                              /*!< <i>Minimum disparity</i> label. */
    QLabel* numberOfDisparitiesLabel;                       /*!< <i>Number of disparities</i> label. */
    QLabel* textureThresholdLabel;                          /*!< <i>Texture threshold</i> label. */
    QLabel* uniquenessRatioLabel;                           /*!< <i>Uniqueness ratio</i> label. */
    QLabel* speckleWindowSizeLabel;                         /*!< <i>Speckle window size</i> label. */
    QLabel* speckleRangeLabel;                              /*!< <i>Speckle range</i> label. */
    QLabel* disp12MaxDiffLabel;                             /*!< <i>Maximum allowed difference (in integer pixel units) in the left-right disparity check</i> label. */
    QLabel* averageTextureThresholdLabel;                   /*!< <i>Average texture threshold</i> label. */

    QLabel* preFilterSizeValueLabel;                        /*!< Label allowing to display the <i>Prefilter size</i> value. */
    QLabel* preFilterCapValueLabel;                         /*!< Label allowing to display the <i>Prefilter cap</i> value. */
    QLabel* SADWindowSizeValueLabel;                        /*!< Label allowing to display the <i>Sum of Absolute Differences (SAD) window size</i> value. */
    QLabel* minDisparityValueLabel;                         /*!< Label allowing to display the <i>Minimum disparity</i> value. */
    QLabel* numberOfDisparitiesValueLabel;                  /*!< Label allowing to display the <i>Number of disparities</i> value. */
    QLabel* textureThresholdValueLabel;                     /*!< Label allowing to display the <i>Texture threshold</i> value. */
    QLabel* uniquenessRatioValueLabel;                      /*!< Label allowing to display the <i>Uniqueness ratio</i> value. */
    QLabel* speckleWindowSizeValueLabel;                    /*!< Label allowing to display the <i>Speckle window size</i> value. */
    QLabel* speckleRangeValueLabel;                         /*!< Label allowing to display the <i>Speckle range</i> value. */
    QLabel* disp12MaxDiffValueLabel;                        /*!< Label allowing to display the <i>Maximum allowed difference (in integer pixel units) in the left-right disparity check</i> value. */
};

#endif // DISPARITYMAPPARAMETERSWIDGET_HPP

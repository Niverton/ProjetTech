/*!
 * \file blurparameterswidget.hpp
 * \brief Header containing the declaration of the BlurParametersWidget class which contains blur parameters.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef BLURPARAMETERSWIDGET_HPP
#define BLURPARAMETERSWIDGET_HPP

#include <widgets/parameterswidget.hpp>

class QSpinBox;

/*!
 * \class BlurParametersWidget
 * \brief The BlurParametersWidget class contains blur parameters which are used to apply a blur filter to an image.
 *        This class gathers two <a href="http://doc.qt.io/qt-5/qspinbox.html">QSpinBox</a> which allows to set
 *        the kernel width and height of a normalized box blur filter.
 *        With this kind of filter, each output pixel is the mean of its kernel neighbors (all of them contribute with equal weights).
 *        The kernel is obtain as below:
 * \image html normalized-box-blur-kernel.png
 *        The BlurParametersWidget is meant to be used with the BlurParameters Observer.
 */
class BlurParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor wich allows to build all the components of the GUI.
     *        If a Model is specified, the default data, or the previous data stored in the Model will be
     *        retrieved and injected into the View. If no Model is specified, default parameters are set for
     *        the kernel size and a model will have to be attached later with the use of the attach() method.
     * \param parent    Parent widget.
     * \param model     Observer.
     */
    BlurParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);

    /*!
     * \brief Default destructor.
     */
    ~BlurParametersWidget();

    /*!
     * \brief Gets the kernel width of the normalized box blur filter.
     * \return The kernel width of the ormalized box blur filter
     */
    int getKSizeW() const;

    /*!
     * \brief Gets the kernel height of the normalized box blur filter.
     * \return The kernel height of the normalized box blur filter.
     */
    int getKSizeH() const;

    /*!
     * \brief Updates the Model.
     *        The values manipulated in the View are injected into the Model.
     *        The corresponding Model of this class is the BlurParameters Observer.
     */
    void notify();

    /*!
     * \brief update
     */
    void update();

private slots:
    void setKSizeW(int kW);
    void setKSizeH(int kH);
    void setKSize(int kW, int kH);

private:
    QSpinBox* kWSpinBox;
    QSpinBox* kHSpinBox;
};

#endif // BLURPARAMETERSWIDGET_HPP

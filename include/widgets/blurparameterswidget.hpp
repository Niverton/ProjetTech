/*!
 * \file blurparameterswidget.hpp
 * \brief Header containing the declaration of the BlurParametersWidget class which allows to manipulate Canny parameters.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef BLURPARAMETERSWIDGET_HPP
#define BLURPARAMETERSWIDGET_HPP

#include <widgets/parameterswidget.hpp>

class QSpinBox;

/*!
 * \class BlurParametersWidget
 * \inherits ParametersWidget
 * \brief The BlurParametersWidget class allows the user to manipulate blur related parameters in order to apply a
 *        normalized box blur filter to an image.
 *
 *        This class is a member of the ParameterWidget family of objects. It is an <i>observable</i> object which is meant to
 *        be bound to its corresponding <i>Model</i>: the BlurParameters object.
 *
 *        Basically, this class will give the user an access to the <i>convolution matrix</i> size parameters.
 *        If no <i>Model</i> is specified during the instance of this object, default values are affected to
 *        the manipulated paramters. Consequently, a call to the ParametersWidget::attach() method will be required.
 * \see The \ref observermodule for more details about the relation between <i>observers</i> and <i>observables</i>.
 * \see The ParametersWidget class to get more details about the relation between the Paramaters family of objects and the
 *      ParametersWidget family of objects.
 * \see The ImageProcessor class for more details about the Blur filter.
 * \see ParametersWidget::attach()
 */
class BlurParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instanciate a BlurParametersWidget.
     *        The BlurParametersWidget is designed to manipulate blur related parameters before applying any image transformation.
     *        This object is a member of the <i>observable</i> family of objects. It is meant to be bound to the BlurParameters object
     *        which is corresponding to its <i>observer</i>.
     *
     *        All the <i>GUI</i> components are built during the process.
     * \param parent    Parent widget.
     * \param model     BlurParameters <i>observer</i>.
     * \see ParametersWidget::attach()
     */
    BlurParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);

    /*!
     * \brief Default destructor.
     */
    ~BlurParametersWidget();

    /*!
     * \brief Gets the <i>convolution matrix</i> width.
     * \return The <i>convolution matrix</i> width entered by the user.
     */
    int getKSizeW() const;

    /*!
     * \brief Gets the <i>convolution matrix</i> height.
     * \return The <i>convolution matrix</i> height entered by the user.
     */
    int getKSizeH() const;

    /*!
     * \brief Pulls the data from the <i>observable</i> and inserts them in the attached BlurParameters <i>observer</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see BlurParametersWidget::BlurParametersWidget()
     * \see ParametersWidget::attach()
     */
    void notify();

    /*!
     * \brief Pulls the data from the BlurParameters <i>observer</i> and inserts them in the <i>observable</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see BlurParametersWidget::BlurParametersWidget()
     * \see ParametersWidget::attach()
     */
    void update();

private slots:
    /*!
     * \brief Sets the <i>convolution matrix</i> width.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>convolution matrix</i> width.
     */
    void setKSizeW(int value);

    /*!
     * \brief Sets the <i>convolution matrix</i> height.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value The <i>convolution matrix</i> height.
     */
    void setKSizeH(int value);

    /*!
     * \brief Sets the <i>convolution matrix</i> size.
     *        This slot alters the <i>View</i> by setting and displaying the given values.
     * \param w The <i>convolution matrix</i> width.
     * \param h The <i>convolution matrix</i> height.
     */
    void setKSize(int w, int h);

private:
    QSpinBox* kWSpinBox;    /*!< <i>Convolution matrix</i> width spin box. */
    QSpinBox* kHSpinBox;    /*!< <i>Convolution matrix</i> height spin box. */
};

#endif // BLURPARAMETERSWIDGET_HPP

/*!
 * \file cannyparameterswidget.hpp
 * \brief Header containing the declaration of the CannyParametersWidget class which allows to manipulate Canny parameters.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef CANNYPARAMETERSWIDGET_HPP
#define CANNYPARAMETERSWIDGET_HPP

#include "widgets/parameterswidget.hpp"

class QDoubleSpinBox;
class QComboBox;
class QCheckBox;
class QPushButton;

/*!
 * \class CannyParametersWidget
 * \inherits ParametersWidget
 * \brief The CannyParametersWidget class allows the user to manipulate Canny related parameters in order to apply a
 *        Canny filter to an image.
 *
 *        This class is a member of the ParameterWidget family of objects. It is an <i>observable</i> object which is meant to
 *        be bound to its corresponding <i>Model</i>: the CannyParameters object.
 *
 *        Basically, this class will give the user an access to the two <i>hysteresis thresholds</i>, the <i>convolution matrix</i>
 *        size, and the <i>gradient magnitude</i> parameters. If no <i>Model</i> is specified during the instance of this object,
 *        default values are affected to the manipulated paramters. Consequently, a call to the ParametersWidget::attach() method
 *        will be required.
 * \see The \ref observermodule for more details about the relation between <i>observers</i> and <i>observables</i>.
 * \see The ParametersWidget class to get more details about the relation between the Paramaters family of objects and the
 *      ParametersWidget family of objects.
 * \see The ImageProcessor class for more details about the Canny filter.
 * \see ParametersWidget::attach()
 */
class CannyParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instanciate a CannyParametersWidget.
     *        The CannyParametersWidget is designed to manipulate Canny related parameters before applying any image transformation.
     *        This object is a member of the <i>observable</i> family of objects. It is meant to be bound to the CannyParameters object
     *        which is corresponding to its <i>observer</i>.
     *
     *        All the <i>GUI</i> components are built during the process.
     * \param parent    Parent widget.
     * \param model     CannyParameters <i>observer</i>.
     * \see ParametersWidget::attach()
     */
    CannyParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);

    /*!
     * \brief Default destructor.
     */
    ~CannyParametersWidget();

    /*!
     * \brief Gets the first <i>hysteresis threshold</i>.
     * \return The first <i>hysteresis threshold</i> entered by the user.
     */
    double getHThrA() const;

    /*!
     * \brief Gets the second <i>hysteresis threshold</i>.
     * \return The second <i>hysteresis threshold</i> entered by the user.
     */
    double getHThrB() const;

    /*!
     * \brief Gets the <i>convolution matrix</i> size.
     * \return The <i>convolution matrix</i> size entered by the user.
     */
    int getAperture() const;

    /*!
     * \brief Gets the <i>gradient magnitude</i> status.
     * \return The <i>gradient magnitude</i> status.
     */
    bool getGMagnitude() const;

    /*!
     * \brief Pulls the data from the <i>observable</i> and inserts them in the attached CannyParameters <i>observer</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see CannyParametersWidget::CannyParametersWidget()
     * \see ParametersWidget::attach()
     */
    void notify();

    /*!
     * \brief Pulls the data from the CannyParameters <i>observer</i> and inserts them in the <i>observable</i>.
     *        This method pulls the data only if a <i>Model</i> has been specified during the instance of the
     *        <i>observable</i> object, or if it has been attached before triggering this method.
     * \see CannyParametersWidget::CannyParametersWidget()
     * \see ParametersWidget::attach()
     */
    void update();

private slots:
    /*!
     * \brief Sets the first <i>hysteresis threshold</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value <i>Hysteresis threshold</i> value.
     */
    void setHThrA(double value);

    /*!
     * \brief Sets the second <i>hysteresis threshold</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value <i>Hysteresis threshold</i> value.
     */
    void setHThrB(double value);

    /*!
     * \brief Sets the <i>convolution matrix</i> size.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value <i>Convolution matrix</i> size.
     */
    void setAperture(int value);

    /*!
     * \brief Sets the <i>gradient magnitude</i>.
     *        This slot alters the <i>View</i> by setting and displaying the given value.
     * \param value <i>Gradient magnitude</i> value.
     */
    void setGMagnitude(int value);

private:
    QDoubleSpinBox* thrASpinBox;        /*!< First <i>hysteresis threshold</i> spin box. */
    QDoubleSpinBox* thrBSpinBox;        /*!< Second <i>hysteresis threshold</i> spin box. */

    QComboBox*      apComboBox;         /*!< <i>Convolution matrix</i> combo box. */

    QCheckBox*      magnCheckBox;       /*!< <i>Gradient magnitude</i> check box. */
};

#endif // CANNYPARAMETERSWIDGET_HPP

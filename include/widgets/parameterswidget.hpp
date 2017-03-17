/*!
 * \file parameterswidget.hpp
 * \brief Header containing the declaration of the ParametersWidget class which provides the minimum functionalities for building the ParametersDockWidget object.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#ifndef PARAMETERSWIDGET_HPP
#define PARAMETERSWIDGET_HPP

#include <QWidget>

class Parameters;

class QPushButton;
class QCheckBox;

/*!
 * \class ParametersWidget
 * \inherits QWidget
 * \brief The ParametersWidget is an abstract class which provides the minimum required functionalities for building the content of
 *        a ParametersDockWidget object.
 *
 *        This class is a <i>observable</i> component which inheritates from the <a href="http://doc.qt.io/qt-5/qwidget.html">QWidget<a/> class.
 *        The ParametersWidget class works hand in hand with a <i>observer</i> class which is derived from the Parameters class.
 *        An <i>observer pattern</i> has been implemented between these two families of objects. As such, this class supplies
 *        two pure virtual methods:
 *          - ParametersWidget::notify()
 *          - ParametersWidget::update()
 *        The ParametersWidget::notify() method will push the data of the <i>observable</i> into the underlying <i>observer</i>,
 *        while the ParametersWidget::update() method will pull the data from the <i>observer</i> into the <i>observable</i>.
 *
 *        The ParametersWidget holds a pointer towards the family of Parameters objects. The same goes for the family of
 *        Parameters objects.
 *
 *        Thanks to the ParametersWidget::notify() and ParametersWidget::update() methods, all ParametersWidget derived objects
 *        can act as:
 *          - An <i>observable</i> object;
 *          - An <i>observer</i> object;
 *          - Both an <i>observable</i> object and an <i>observer</i> object.
 *
 *        This ParametersWidget class also contains several <i>widget</i> which will be common to each of the derived object.
 *        The purposes of these <i>widgets</i> are indicated below:
 *          - The label is used to notifies the user which operation he/she has chosen.
 *          - The check box is used to apply the modifications made by the user in real time.
 *          - The button is used to apply the modification made by the user.
 *
 *        The family of ParametersWidget objects do not owns the <i>observers</i> and vice-versa. It is not its responsability to delete it.
 *
 * \note A connection between the check box and the button has been put in place. If the check box is checked the apply button is disabled.
 * \see The \ref observermodule for more details about the relation between <i>observers</i> and <i>observables</i> objects.
 */
class ParametersWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instantiate a ParametersWidget object.
     *        The constructor builds all the GUI components.
     * \param title     Title of the operation which is processed.
     * \param parent    Parent <i>widget</i>.
     * \param model     <i>Observer</i>.
     */
    ParametersWidget(const QString& title = QString(), QWidget* parent = nullptr);

    /*!
     * \brief Constructor which allows to instantiate a ParametersWidget object by specifying a Model.
     *        The constructor builds all the GUI components.
     * \param title     Title of the operation which is processed.
     * \param parent    Parent widget.
     * \param model     Observer.
     */
    ParametersWidget(const QString& title = QString(), QWidget* parent = nullptr, Parameters* model = nullptr);

    /*!
     * \brief Default destructor.
     */
    virtual ~ParametersWidget();

    /*!
     * \brief Allows to attach a <i>Model</i>.
     *        This method must be called if an <i>observer pattern</i> is desired and if no <i>Model</i> has been specified.
     * \param model <i>Observer</i>.
     */
    void attach(Parameters* model);

    /*!
     * \brief Gets the <i>Model</i> attached to a member of the family of ParametersWidget objects.
     * \return An object which belongs to the family of Parameters objects if a <i>Model</i> has been attached;
     *         or nullptr if no <i>Model</i> has been attached.
     */
    Parameters* model() const;

    /*!
     * \brief Determines if a member of the family of ParametersWidget objects has a <i>Model</i>.
     * \return True if the object has a <i>Model</i>; or false if no <i>Model</i> has been attached.
     */
    bool hasModel() const;

    /*!
     * \brief Determines if the real time check box is checked.
     * \return True if the real time check box is checked; or false if it is not checked.
     */
    bool hasRealTime() const;

    /*!
     * \brief Updates the <i>Model</i>.
     *        The values manipulated in the View are injected into the <i>Model</i>.
     */
    virtual void notify() = 0;

    /*!
     * \brief Updates the View.
     *        The values stored in the <i>Model</i> are injected into the View.
     */
    virtual void update() = 0;

    /*!
     * \brief Gets the button which allows to apply an operation.
     * \return The button which allows to apply an operation
     */
    QPushButton* getApplyPushButton() const;

    /*!
     * \brief Gets the check box which allows to process modifications in real time.
     * \return The check box which allows to process modifications in real time
     */
    QCheckBox* getRealTimeCheckBox() const;

signals:
    /*!
     * \brief Signal used for real time operations.
     *        This signal is triggered when the real time check box is checked.
     */
    void valuesChanged();

private slots:
    /*!
     * \brief Slot allowing to enable the button which allows to apply an operation.
     * \param value According to the <a href="http://doc.qt.io/qt-5/qt.html#CheckState-enum">CheckState enum</a>, the following values are accepted:
     *          - O if the item is unchecked.
     *          - 1 if the item is partially checked. Items in hierarchical models
     *            may be partially checked if some, but not all, of their children are checked.
     *          - 2	if the item is checked.
     */
    void setApply(int value);

private:
    QPushButton*    applyPushButton;        /*!< Button which allows to apply an operation */
    QCheckBox*      realTimeCheckBox;       /*!< Check box which allows to process operations in real time */

private:
    Parameters* m;                          /*!< <i>Observer</i>. */
};

#endif // PARAMETERSWIDGET_HPP

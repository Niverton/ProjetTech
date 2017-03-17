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
 * \brief The ParametersWidget is an abstract class which provides the minimum functionalities for building the content of a ParametersDockWidget object.
 *        This class is a View component which inheritates from the <a href="http://doc.qt.io/qt-5/qwidget.html">QWidget<a/> class.
 *        The ParametersWidget class works hand in hand with a Model class which is derived from the Parameters class. An observer pattern has
 *        been implemented between these two families of objects.
 *        As such, this class supplies two pure virtual methods:
 *          - notify()
 *          - update()
 *        The notify() method will push the data of the View into the underlying Model, while the update() method will pull the data from the Model into
 *        the View.
 *
 *        The notify() method will involve the following mechanisms:
 *
 * \image html observer-notify.png
 *
 *        The ParametersWidget holds a pointer towards a Parameters family object. The same goes for a Parameters family object.
 *        The notify() method
 *
 *        Thanks to the notify() and update() methods, all ParametersWidget derived objects can act as:
 *          - An observable object;
 *          - An observer object;
 *          - Both an observable object and an observer object.
 *
 *       The observer pattern used also allows to retrieve the parameters entered by the user for a determined operation if the ParametersDockWidget is closed.
 *
 *        The ParametersWidget abstract class also the base layout for all widgets which will be inserted in the derived classes:
 *          - A <a href="http://doc.qt.io/qt-5/QGridLayout.html">QGridLayout</a> object;
 *          - A <a href="http://doc.qt.io/qt-5/qlabel.html">QLabel</a> object;
 *          - A <a href="http://doc.qt.io/qt-5/QCheckBox.html">QCheckBox</a> object;
 *          - A <a href="http://doc.qt.io/qt-5/qpushbutton.html">QPushButton</a> object;
 *        The three last widgets are naturally layed out in the <a href="http://doc.qt.io/qt-5/QGridLayout.html">QGridLayout</a> object.
 *
 *        The purposes of these widgets are indicated below:
 *          - The label is used to notifies the user which operation he/she has chosen.
 *          - The check box is used to apply the modifications made by the user in real time.
 *          - The button is used to apply the modification made by the user.
 *
 *        The ParametersWidget family of objects do not owns the Model. It is not its responsability to delete it.
 *
 * \note A connection between the check box and the button has been put in place. If the check box is checked the apply button is disabled.
 */
class ParametersWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instantiate a ParametersWidget object without specifying a Model.
     *        A call to the attach(model) method is mandatory if an observer pattern has to be put in place.
     *        The constructor builds all the GUI components.
     * \param title     Title of the operation which is processed.
     * \param parent    Parent widget.
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
     * \brief Allows to attach a model.
     *        This method must be called if an Observer pattern is desired and if no Model has been specified.
     * \param model Observer.
     */
    void attach(Parameters* model);

    /*!
     * \brief Gets the Model attached a ParametersWidget family object.
     * \return A Parameters family object if a Model has been attached; or nullptr if no Model has been attached.
     */
    Parameters* model() const;

    /*!
     * \brief Determines if a ParametersWidget family object has a Model.
     * \return True if a ParametersWidget family object has a Model; or false if no Model has been attached.
     */
    bool hasModel() const;

    /*!
     * \brief Determines if the real time check box is checked.
     * \return True if the real time check box is checked; or false if it is not checked.
     */
    bool hasRealTime() const;

    /*!
     * \brief Updates the Model.
     *        The values manipulated in the View are injected into the Model.
     */
    virtual void notify() = 0;

    /*!
     * \brief Updates the View.
     *        The values stored in the Model are injected into the View.
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
    Parameters* m;                          /*!< Observer. */
};

#endif // PARAMETERSWIDGET_HPP

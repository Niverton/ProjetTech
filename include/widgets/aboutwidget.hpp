/*!
 * \file aboutwidget.hpp
 * \brief Header containing the declaration of the AboutWidget class which is used to display software informations.
 * \author Hadrien Decoudras
 * \date 2017-02-03
 * \version 0.1
 */

#ifndef ABOUTWIDGET_HPP
#define ABOUTWIDGET_HPP

#include <QWidget>

class QLabel;
class QPushButton;

/*!
 * \class AboutWidget
 * \brief The AboutWidget class is used to display software informations.
 *        This widget is a modal window which displays libraries used during the
 *        development of the project and the name of the programmer.
 *        The self deletion of this widget is ensured. As such, it is not needed to call
 *        delete after a dynamic allocation.
 */
class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which instanciates a ready to use AboutWidget object.
     * \param text Text of the authors.
     */
    AboutWidget(const QString& text = QString());

    /*!
     * \brief Default destructor.
     */
    ~AboutWidget();

protected:
    /*!
     * \brief Reimplemented methods in order to ensure self deletion.
     * \param event Close event.
     */
    void closeEvent(QCloseEvent* event);

private slots:
    /*!
     * \brief Allows to close the widget.
     */
    void exit();

private:
    QLabel* textLabel;              /*!< Container of the text of the authors. */
    QLabel* qtImageLabel;           /*!< Qt logo. */
    QLabel* ocvImageLabel;          /*!< OpenCV logo. */
    QLabel* cudaImageLabel;         /*!< Cuda logo. */

    QString text;                   /*!< Text of the authors. */

    QPushButton* closePushButton;   /*!< Close button. */
};

#endif // ABOUTWIDGET_H

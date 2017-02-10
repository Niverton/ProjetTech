/*!
 * \file stereotransformwidget.hpp
 * \brief Header containing the declaration of the StereoTransformWidget class which is designed to contain a transformed image.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#ifndef STEREOTRANSFORMWIDGET_H
#define STEREOTRANSFORMWIDGET_H

#include <QWidget>

#include <opencv2/core/core.hpp>

class ImageWidget;

/*!
 * \class StereoTransformWidget
 * \brief The StereoTransformWidget class is used to display a transformed image.
 *        This class is designed to hold an image transformed with the help of the
 *        OpenCV library.
 *        Basically, a StereoTransformWidget is a modal window which allows to display
 *        an image. This widget features zoom and save capabilities. The last one is
 *        available through the 'Action' menu.
 *        The StereoTransformWidget is intended to keep a stereo image displayed in a
 *        main window while the transformed image is displayed in this widget.
 *        The self deletion of this widget is ensured. As such, it is not needed to call
 *        delete after a dynamic allocation.
 */
class StereoTransformWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor which allows to instanciate a ready to use StereoTransformWidget object.
     * \param image Transformed image.
     * \param title Title of the modal window.
     */
    StereoTransformWidget(const cv::Mat& image, const QString& title = QString());

    /*!
     * \brief Default destructor.
     */
    ~StereoTransformWidget();

protected:
    /*!
     * \brief Reimplemented methods in order to ensure self deletion.
     * \param event Close event.
     */
    void closeEvent(QCloseEvent* event);

private slots:
    /*!
     * \brief Allows to save an image.
     *        Two image formats are available: PNG and JPEG.
     */
    void save();

    /*!
     * \brief Allows to close the widget.
     */
    void exit();

private:
    ImageWidget* imageWidget;   /*!< Image container. */
};

#endif // STEREOTRANSFORMWIDGET_H

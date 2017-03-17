/*!
 * \file undostack.hpp
 * \brief Header containing the declaration of the UndoStack class which is used to track
 *        the operations done by the user.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2017-01-27
 * \version 0.3
 */

#ifndef UNDOSTACK_HPP
#define UNDOSTACK_HPP

#include <stack>
#include <utility>

#include <opencv2/core/core.hpp>

class ImageWidget;

/*!
 * \class UndoStack
 * \brief The UndoStack class is used to track the operations done by the user.
 *        It simply allows to undo one or more operations done by a user.
 *        This component can be seen as a "sort of" delegation in which the owner
 *        of this object will temporarily yield part of its logic to the UndoStack
 *        object. The UndoStack object will operate on the ImageWidget and derived
 *        objects.
 */
class UndoStack
{
public:
    /*!
     * \enum UndoStackImage
     * \brief The UndoStackOp enum is used as an index in order to identify
     *        which image needs to be updated.
     */
    enum StereoUndoStackImage
    {
        UNDO_STACK_IMAGE_FIRST = 0,    /*!< First image. */
        UNDO_STACK_IMAGE_SECOND        /*!< Second image. */
    };

public:
    /*!
     * \brief Default constructor.
     */
    UndoStack();

    /*!
     * \brief Constructor which instanciates a ready to use StereoUndoStack object.
     * \param lWidget First image.
     * \param rWidget Second image
     */
    UndoStack(ImageWidget* lWidget, ImageWidget* rWidget);

    /*!
     * \brief Default destructor.
     */
    ~UndoStack();

    void push(const cv::Mat& image);

    /*!
     * \brief Saves the state of the first image.
     * \param image OpenCV representation of the first image.
     */
    void pushLeft(const cv::Mat& image);

    /*!
     * \brief Saves the state of the second image.
     * \param image OpenCV representation of the second image.
     */
    void pushRight(const cv::Mat& image);

    /*!
     * \brief Sets the first ImageWidget object.
     * \param widget The fisrt ImageWidget object.
     */
    void attach(ImageWidget* widget);

    void attachLeft(ImageWidget* widget);
    void attachRight(ImageWidget* widget);

    /*!
     * \brief Checks if the stack is empty.
     * \return True if the stack is empty; false otherwise.
     */
    bool empty() const;

    /*!
     * \brief Allows to restore the previous state of an image.
     */
    void undo();

private:
    ImageWidget*                                            lWidget;    /*!< Left widget */
    ImageWidget*                                            rWidget;    /*!< Right widget */
    std::stack<std::pair<StereoUndoStackImage, cv::Mat>>    undoStack;  /*!< Saved states of images. */
};

#endif // UNDOSTACK_HPP

/*!
 * \file undostack.hpp
 * \brief Header containing the declaration of the UndoStack class which is used to track
 *        the operations done by the user.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \version 0.2
 */

#ifndef UNDOSTACK_HPP
#define UNDOSTACK_HPP

#include <stack>
#include <tuple>

#include <opencv2/core/core.hpp>

class ImageWidget;

/*!
 * \class UndoStack
 * \brief The UndoStack class is used to track the operations done by the user.
 *        It simply allows to undo one or more operations done by a user.
 *        This component can be seen as a "sort of" delegation in which the owner
 *        of this object will temporarily yield part of its logic to the UndoStack
 *        object. The UndoStack object will operate on the two ImageWidget components
 *        of the main window.
 */
class UndoStack
{
public:
    /*!
     * \enum UndoStackImage
     * \brief The UndoStackOp enum is used as an index in order to identify
     *        which image needs to be updated.
     */
    enum UndoStackImage
    {
        UNDO_STACK_IMAGE_FIRST = 0,    /*!< First image. */
        UNDO_STACK_IMAGE_SECOND        /*!< Second image. */
    };

public:
    enum UndoStackOp
    {
        UNDO_STACK_OP_DEFAULT = 0,
        UNDO_STACK_OP_ZOOM
    };

public:
    /*!
     * \brief Default constructor.
     */
    UndoStack();

    /*!
     * \brief Constructor get an instance of a ready to use UndoStack object.
     * \param rWidget First image.
     * \param lWidget Second image
     */
    UndoStack(ImageWidget* rWidget, ImageWidget* lWidget);

    /*!
     * \brief Default destructor.
     */
    ~UndoStack();

    /*!
     * \brief Saves the state of the first image.
     * \param image OpenCV representation of the first image.
     */
    inline void pushLeft(cv::Mat& image, UndoStackOp op = UNDO_STACK_OP_DEFAULT)
    {
        undoStack.push(std::make_tuple(UNDO_STACK_IMAGE_FIRST, op, image));
    }

    /*!
     * \brief Saves the state of the second image.
     * \param image OpenCV representation of the second image.
     */
    inline void pushRight(cv::Mat& image, UndoStackOp op = UNDO_STACK_OP_DEFAULT)
    {
        undoStack.push(std::make_tuple(UNDO_STACK_IMAGE_SECOND, op, image));
    }

    inline std::tuple<UndoStackImage, UndoStackOp, cv::Mat> getTopTupleElement()
    {
        return undoStack.top();
    }

    /*!
     * \brief Sets the first ImageWidget object.
     * \param widget The fisrt ImageWidget object.
     */
    inline void setLeftWidget(ImageWidget* widget)
    {
        lWidget = widget;
    }

    /*!
     * \brief Sets the second ImageWidget object.
     * \param widget The second ImageWidget object.
     */
    inline void setRightWidget(ImageWidget* widget)
    {
        rWidget = widget;
    }

    inline bool isEmpty() const
    {
        return undoStack.empty();
    }

    /*!
     * \brief Allows to restore the previous state of an image.
     */
    void undo();

private:
    ImageWidget*                                                    lWidget;    /*!< First Widget. */
    ImageWidget*                                                    rWidget;    /*!< Second widget. */
    std::stack<std::tuple<UndoStackImage, UndoStackOp, cv::Mat>>    undoStack;  /*!< Saved states of images. */
};

#endif // UNDOSTACK_HPP

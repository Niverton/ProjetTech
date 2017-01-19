#ifndef UNDOSTACK_HPP
#define UNDOSTACK_HPP

#include <stack>
#include <utility>

#include <opencv2/core/core.hpp>

class ImageWidget;

class UndoStack
{
public:
    enum UndoStackOp
    {
        UNDO_STACK_OP_FIRST = 0,
        UNDO_STACK_OP_SECOND
    };

public:
    UndoStack();
    UndoStack(ImageWidget* rWidget, ImageWidget* lWidget);
    ~UndoStack();

    inline void pushLeft(cv::Mat& image)
    {
        undoStack.push(std::make_pair(UNDO_STACK_OP_FIRST, image));
    }

    inline void pushRight(cv::Mat& image)
    {
        undoStack.push(std::make_pair(UNDO_STACK_OP_SECOND, image));
    }

    inline void setLeftWidget(ImageWidget* widget)
    {
        lWidget = widget;
    }

    inline void setRightWidget(ImageWidget* widget)
    {
        rWidget = widget;
    }

    void undo();

private:
    ImageWidget*                                lWidget;
    ImageWidget*                                rWidget;
    std::stack<std::pair<UndoStackOp, cv::Mat>> undoStack;
};

#endif // UNDOSTACK_HPP

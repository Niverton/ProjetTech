#include "undostack.hpp"
#include "imagewidget.hpp"

#include <QDebug>

UndoStack::UndoStack() {}

UndoStack::UndoStack(ImageWidget* lWidget, ImageWidget* rWidget) : lWidget(lWidget), rWidget(rWidget) {}

UndoStack::~UndoStack() {}

void UndoStack::undo()
{
    if(undoStack.empty())
    {
        return;
    }

    std::pair<UndoStackOp, cv::Mat> p = undoStack.top();

    switch(p.first)
    {
        case UndoStack::UndoStackOp::UNDO_STACK_OP_FIRST:
        {
            lWidget->setImage(p.second);
            break;
        }

        case UndoStack::UndoStackOp::UNDO_STACK_OP_SECOND:
        {
            rWidget->setImage(p.second);
            break;
        }
    }

    undoStack.pop();
}

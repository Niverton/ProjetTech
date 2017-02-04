/*!
 * \file undostack.cpp
 * \brief Implementation of the methods of the UndoStack class declared in the undostack.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \version 0.2
 */

#include "undostack.hpp"
#include "imagewidget.hpp"

/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
UndoStack::UndoStack() {}

/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
UndoStack::UndoStack(ImageWidget* lWidget, ImageWidget* rWidget) : lWidget(lWidget), rWidget(rWidget) {}

/**************************************************************
 **************************************************************
 *
 * Destructor
 *
 **************************************************************/
UndoStack::~UndoStack() {}

/**************************************************************
 **************************************************************
 *
 * Undo
 *
 **************************************************************/
void UndoStack::undo()
{
    if(undoStack.empty())
    {
        return;
    }

    std::pair<UndoStackImage, cv::Mat> p = undoStack.top();

    switch(p.first)
    {
        case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_FIRST:
        {
            lWidget->setImage(p.second);
            break;
        }

        case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_SECOND:
        {
            rWidget->setImage(p.second);
            break;
        }
    }

    undoStack.pop();
}

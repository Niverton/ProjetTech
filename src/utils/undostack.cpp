/*!
 * \file undostack.cpp
 * \brief Implementation of the methods of the UndoStack class declared in the undostack.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2017-01-27
 * \version 0.2
 */

#include "utils/undostack.hpp"
#include "widgets/images/imagewidget.hpp"

/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
UndoStack::UndoStack() : lWidget(nullptr), rWidget(nullptr) {}

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

void UndoStack::push(const cv::Mat& image)
{
    undoStack.push(std::make_pair(UNDO_STACK_IMAGE_FIRST, image));
}

void UndoStack::pushLeft(const cv::Mat& image)
{
    undoStack.push(std::make_pair(UNDO_STACK_IMAGE_FIRST, image.clone()));
}

void UndoStack::pushRight(const cv::Mat& image)
{
     undoStack.push(std::make_pair(UNDO_STACK_IMAGE_SECOND, image.clone()));
}

void UndoStack::attach(ImageWidget* widget)
{
    lWidget = widget;
}

void UndoStack::attachLeft(ImageWidget *widget)
{
    lWidget = widget;
}

void UndoStack::attachRight(ImageWidget *widget)
{
    rWidget = widget;
}

bool UndoStack::empty() const
{
    return undoStack.empty();
}

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

    std::pair<StereoUndoStackImage, cv::Mat> pa = undoStack.top();

    switch(pa.first)
    {
        case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_FIRST:
        {
            lWidget->setImage(pa.second);
            break;
        }

        case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_SECOND:
        {
            rWidget->setImage(pa.second);
            break;
        }
    }

    undoStack.pop();
}

#include "llkview.h"

llkView::llkView()
{

}
llkView* llkView::view = new llkView();

llkView* llkView::getInstance()
{
    return view;
}

#ifndef LLKVIEW_H
#define LLKVIEW_H
#include <QGraphicsView>


class llkView : public QGraphicsView
{
public:
    static llkView* getInstance();

private:
    llkView();
    static llkView* view;
};

#endif // LLKVIEW_H

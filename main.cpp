#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <startinterface.h>
#include <QCursor>
#include <QPixmap>
#include <QtWidgets>
#include <stdlib.h>
#include <time.h>
#include "handler.h"

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene *scene) : QGraphicsView(scene)
    {
    }

protected:
    void resizeEvent(QResizeEvent *) override
    {
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startInterface scene;
    GraphicsView* view = new GraphicsView(&scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/bg/img/bg.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, QString::fromLocal8Bit("Á¬Á¬¿´")));
    view->resize(802, 802);
    view->setFixedSize(view->width(),view->height());
    view->setWindowFlags(view->windowFlags()&~Qt::WindowMaximizeButtonHint);
    view->viewport()->setCursor(QCursor(QPixmap((":/system/img/finger.png"))));
    view->show();

    srand((unsigned)time(NULL));

    handler* hand = handler::getInstance();
    QObject::connect(hand, SIGNAL(startGame()), &scene, SLOT(start()));
    QObject::connect(hand, SIGNAL(exitGame()), &scene, SLOT(exit()));
    QObject::connect(hand, SIGNAL(showHistory()), &scene, SLOT(search()));
    QObject::connect(hand, SIGNAL(showSettingsInterface()), &scene, SLOT(setSettingInterface()));
    QObject::connect(hand, SIGNAL(resetInterface()), &scene, SLOT(removeSettingButtons()));

    return a.exec();
}

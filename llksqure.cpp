#include "llksqure.h"
#include "handler.h"
#include <QCursor>
#include <QString>
#include <QDebug>
llkSqure::llkSqure(int index, int order)
{
    this->selected = false;
    this->i = 0;
    this->j = 0;
    this->setData(0, QVariant(index));
    this->setData(1, QVariant(order));
    this->init_path = ":/square/pokemon/init/img/pokemon/init/";
    this->selected_path = ":/square/pokemon/init/img/pokemon/selected/";
    setAcceptedMouseButtons(Qt::LeftButton);
    setCursor(QCursor(QPixmap(":/system/img/finger.png")));
}

QRectF llkSqure::boundingRect() const
{
    return QRectF(-5, -5, 80, 80);
}
void llkSqure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    handler* hand = handler::getInstance();
    hand->tellTheSelectOrder(this->data(1).toInt());
}
void llkSqure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void llkSqure::setSelected(bool selected)
{
    this->selected = selected;
}

bool llkSqure::isSelected()
{
    return this->selected;
}

void llkSqure::setI(int i)
{
    this->i = i;
}

void llkSqure::setJ(int j)
{
    this->j = j;
}

int llkSqure::getI()
{
    return this->i;
}

int llkSqure::getJ()
{
    return this->j;
}

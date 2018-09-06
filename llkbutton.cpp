#include "llkbutton.h"
#include "handler.h"
#include <QCursor>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QFont>
#include <QDebug>
#include <QSound>
#include <QCoreApplication>
#include <QVariant>
#include <QPen>

/***
 * 按钮
 ***/
llkButton::llkButton(QString name, QString str)
{
    this->text = str;
    this->setData(0, QVariant(name));
    this->btn_color = new QColor(0,198,255);
    this->setAcceptHoverEvents(true);
    setCursor(QCursor(QPixmap(":/system/img/finger.png")));
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF llkButton::boundingRect() const
{
    return QRectF(-15.5, -15.5, 205, 55);
}

void llkButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawRoundedRect(-12, -12, 200, 50, 20, 20);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(*this->btn_color));
    painter->drawRoundedRect(-15, -15, 200, 50, 20, 20);
    QFont font(QString::fromLocal8Bit("华文琥珀"),20,QFont::Bold,false);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(40, 17, this->text);
}

void llkButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->btn_color = new QColor(42,55,77);
    this->update();

}
void llkButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    handler* hand = handler::getInstance();
    this->btn_color = new QColor(0,198,255);
    this->update();
    int x = event->pos().x();
    int y = event->pos().y();
    if(x > -15.5 && x < this->boundingRect().width() && y > -15.5 && y < this->boundingRect().height())
    {
        if(this->data(0).toString() == "start")
            hand->tellStart();
        else if(this->data(0).toString() == "search")
            hand->tellShowHistory();
        else if(this->data(0).toString() == "exit")
            hand->tellExit();
    }
}
void llkButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    handler* hand = handler::getInstance();
    this->btn_color = new QColor(246,3,255);
    hand->tellPlaySound(QCoreApplication::applicationDirPath() + "/audio/select.wav");
    this->update();
}
void llkButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->btn_color = new QColor(0,198,255);
    this->update();
}


/***
 * 路线
 ***/
llkRoute::llkRoute()
{
    reset();
}

QRectF llkRoute::boundingRect() const
{
    return QRectF(40, 70, 720, 720);
}

void llkRoute::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(this->x1 == -1)
        return;
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    qreal new_num = num;
    new_num += overstep;
//    if(e1) qDebug() << "e1";
//    if(e2) qDebug() << "e2";
//    qDebug() << "x1:" + QString::number(x1);
//    qDebug() << "x2:" + QString::number(x2);
//    qDebug() << "y1:" + QString::number(y1);
//    qDebug() << "y2:" + QString::number(y2);
//    qDebug() << "num:" + QString::number(new_num);
    if(type == 0)
    {
        if(!e1)
            painter->drawLine(x1, y1, x1, new_num);
        painter->drawLine(x1, new_num, x2, new_num);
        if(!e2)
            painter->drawLine(x2, new_num, x2, y2);
    }else if(type == 1)
    {
        if(!e1)
            painter->drawLine(x1, y1, new_num, y1);
        painter->drawLine(new_num, y1, new_num, y2);
        if(!e2)
            painter->drawLine(new_num, y2, x2, y2);
    }
}

void llkRoute::reset()
{
    this->x1 = -1;
    this->x2 = -1;
    this->y1 = -1;
    this->y2 = -1;
    this->type = -1;
    this->num = -1;
    this->e1 = false;
    this->e2 = false;
    overstep = 0;
}

void llkRoute::setOrder(int x1, int y1, int x2, int y2, int order1, int order2, int type, int num, bool e1, bool e2, int overstep)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->order1 = order1;
    this->order2 = order2;
    this->type = type;
    this->num = num;
    this->e1 = e1;
    this->e2 = e2;
    this->overstep = overstep;
}


/***
 * 文字
 ***/
llkText::llkText(QString text)
{
    this->text = text;
    this->size = 20;
    this->color = new QColor(255, 255, 255);
}

QRectF llkText::boundingRect() const
{
    return QRectF(0, 0, 800, 800);
}

void llkText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QFont font(QString::fromLocal8Bit("华文琥珀"),size,QFont::Bold,false);
    painter->setFont(font);
    painter->setPen(*this->color);
    painter->drawText(0, 0, this->text);
}

void llkText::setText(QString text)
{
    this->text = text;
}

void llkText::setColor(QColor* color)
{
    this->color = color;
}

void llkText::setSize(int size)
{
    this->size = size;
}
/***
 * 画布
 ***/
llkcanvas::llkcanvas(QString name, qreal x, qreal y, qreal w, qreal h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = 0;
    this->setData(0, QVariant(name));
    this->setCursor(QCursor(QPixmap(":/system/img/finger.png")));
}

QRectF llkcanvas::boundingRect() const
{
    return QRectF(x, y, w, h);
}

void llkcanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    if(this->color == 0)
        painter->setBrush(Qt::darkGray);
    else
        painter->setBrush(*this->color);
    painter->drawRect(x, y, w, h);
}

void llkcanvas::setColor(QColor* color)
{
    this->color = color;
}

void llkcanvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    handler* hand = handler::getInstance();
    this->setCursor(QCursor(QPixmap(":/system/img/finger.png")));
    hand->tellPlaySound(QCoreApplication::applicationDirPath() + "/audio/click.wav");
}
void llkcanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(QPixmap(":/system/img/finger.png")));
}


/***
 * 组件
 ***/
assemble::assemble(QString name, QString path, qreal x, qreal y, qreal w, qreal h, bool hover)
{
    if(hover) this->setAcceptHoverEvents(true);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->path = path;
    this->name = name;
    this->setPixmap(QPixmap(path + name + ".png"));
    this->setData(0, QVariant(name));
    setAcceptedMouseButtons(Qt::LeftButton);
    setCursor(QCursor(QPixmap(":/system/img/finger.png")));
}

QRectF assemble::boundingRect() const
{
    return QRectF(x, y, w, h);
}

void assemble::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPixmap(QPixmap(path + name + ".png"));
    this->update();
    handler* hand = handler::getInstance();
    if(this->data(0).toString() == "settings")
        hand->tellSettings();
    else if(this->data(0).toString() == "close")
        hand->tellReset(this->data(2).toInt());
    else if(this->data(0).toString() == "volumn")
        hand->tellModifyVolumn(false);
    else if(this->data(0).toString() == "ban_volumn")
        hand->tellModifyVolumn(true);
    else if(this->data(0).toString() == "refresh")
        hand->tellRefresh();
    else if(this->data(0).toString() == "tip")
        hand->tellToFind();
    else if(this->data(0).toString() == "boom")
        hand->boom_be_clicked(!this->data(1).toBool());
    else if(this->data(0).toString() == "home")
        hand->tellToHomepage(0);
    else if(this->data(0).toString() == "game_home")
        hand->tellToHomepage(this->data(2).toInt());
    else if(this->data(0).toString() == "play_again")
        hand->tellToPlayAgain();
    else if(this->data(0).toString() == "next_checkpoint")
        hand->tellToNextCheckpoint();
    update();

}
void assemble::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->update();

}
void assemble::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->setPixmap(QPixmap(path + name + "_hover.png"));
    QString name = this->data(0).toString();
    handler* hand = handler::getInstance();
    if(name == "boom" || name == "tip" || name == "refresh")
        hand->tellPlaySound(QCoreApplication::applicationDirPath() + "/audio/prop.wav");
    this->update();
}
void assemble::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setPixmap(QPixmap(path + name + ".png"));
    this->update();
}

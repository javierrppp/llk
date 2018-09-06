#ifndef LLKBUTTON_H
#define LLKBUTTON_H
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QColor>
#include "llksqure.h"


class llkButton : public QGraphicsItem
{
public:
    llkButton(QString name, QString str);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    QString text;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    QColor* btn_color;
};

class llkRoute : public QGraphicsItem
{
public:
    llkRoute();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    //void setOrder(int x1, int y1, int x2, int y2, int type, int num, bool overstep, int size = 0);
    void setOrder(int x1, int y1, int x2, int y2, int order1, int order2, int type, int num, bool e1, bool e2, int overstep);
    void reset();
    int order1, order2;
private:
    qreal x1, x2, y1, y2;
    //type为0表示num为行号，type为1表示num为列号
    int type;
    qreal num;
    bool e1, e2;
    int overstep;
};

class llkText : public QGraphicsItem
{
public:
    llkText(QString text);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setText(QString text);
    void setColor(QColor* btn_color);
    void setSize(int size);
protected:
    QString text;
    QColor* color;
    int size;
};

class llkcanvas : public QGraphicsItem
{
public:
    llkcanvas(QString name, qreal x, qreal y, qreal w, qreal h);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setColor(QColor* btn_color);
protected:
    qreal x;
    qreal y;
    qreal w;
    qreal h;
    QColor* color;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class assemble : public QGraphicsPixmapItem
{
public:
    assemble(QString name, QString path, qreal x, qreal y, qreal w, qreal h, bool hover = true);
    QRectF boundingRect() const override;
protected:
    qreal x;
    qreal y;
    qreal w;
    qreal h;
    QString path;
    QString name;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // LLKBUTTON_H

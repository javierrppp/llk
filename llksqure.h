#ifndef LLKSQURE_H
#define LLKSQURE_H

#include <QGraphicsPixmapItem>

class llkSqure : public QGraphicsPixmapItem
{
public:
    llkSqure(int index, int order);
    QRectF boundingRect() const override;
    bool isSelected();
    void setSelected(bool selected);
    QString init_path;
    QString selected_path;
    void setI(int i);
    void setJ(int j);
    int getI();
    int getJ();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    bool selected;
    int i, j;
};

#endif // LLKSQURE_H

#ifndef DOOR_H
#define DOOR_H

#include <QLineF>
#include <QColor>
#include <QGraphicsLineItem>
#include <QPen>
#include <QPainter>

class Door: public QGraphicsLineItem
{
public:
    Door(QLineF doorline);

    QLineF door();

    /*TODO
    shape()
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QLineF _doorline;
};

#endif // DOOR_H

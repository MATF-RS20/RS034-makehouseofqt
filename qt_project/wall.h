#ifndef WALL_H
#define WALL_H

#include <QLineF>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>
class Wall: public QGraphicsPolygonItem
{
public:

    Wall(QPolygonF walls_of_rooms, double height = 2, double thickness = 0.25);

    QPolygonF walls();

    double height();

    double thickness();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*TODO
    shape()
    */
private:

    QPolygonF _walls_of_rooms;
    double _height;
    double _thickness;


};

#endif // WALL_H

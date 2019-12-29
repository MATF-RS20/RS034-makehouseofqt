#ifndef WALL_H
#define WALL_H

#include <QLineF>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>
#include "window.h"
#include "door.h"

class Wall: public QGraphicsPolygonItem
{
public:

    Wall(QPolygonF walls_of_rooms, double height = 2, double thickness = 0.25);

    QPolygonF walls();

    double height();

    double thickness();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addWindow(Window* window);

    void addDoor(Door* door);

    QVector<Window*> getWindows();

    QVector<Door*> getDoors();

    bool containsPoints(QVector<QPointF> lines);

private:

    QPolygonF _walls_of_rooms;
    QVector<Window*> _windows;
    QVector<Door*> _doors;
    double _height;
    double _thickness;

};

#endif // WALL_H

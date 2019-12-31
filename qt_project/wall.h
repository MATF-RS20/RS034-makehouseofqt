#ifndef WALL_H
#define WALL_H

#include <QLineF>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>
#include <QOpenGLWindow>
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

    QPointF middleOfTheRoom();

    void generateWallsForView(QVector<GLfloat> &vertices, QVector<GLfloat> &colors,QColor color);

    QVector<GLfloat> wall(QPointF p1, QPointF p2);

    void generateRoof(QVector<GLfloat> &vertices, QVector<GLfloat> &roof_color);

    QVector<GLfloat> roof(QPointF p1, QPointF p2);


private:

    QPolygonF _walls_of_rooms;
    QVector<Window*> _windows;
    QVector<Door*> _doors;
    float _height;
    float _thickness;

};

#endif // WALL_H

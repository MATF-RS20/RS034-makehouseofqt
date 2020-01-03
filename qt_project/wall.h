#ifndef WALL_H
#define WALL_H

#include <QLineF>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>
#include <QOpenGLWindow>
#include <QDebug>
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

    bool containsPoints(QLineF &l2);

    QPointF middleOfTheRoom();

    void generateWallsForView(QVector<GLfloat> &vertices, QVector<GLfloat> &colors,QColor color);

    QVector<GLfloat> wall(QPointF p1, QPointF p2, GLfloat c, GLfloat h);

    void generateRoof(QVector<GLfloat> &vertices, QVector<GLfloat> &roof_color);

    QVector<GLfloat> roof(QPointF p1, QPointF p2);

    bool angle_is_wrong(QLineF l1, QLineF l2);

    bool isIntersect(QLineF line1, QLineF line2);

    void generateHouseWalls(QVector<QVector<GLfloat>> &vert, QVector<QVector<GLfloat>> &uvss);

    bool canMakeDecorativeWall(QVector<QPointF> line);

    void addDecorativeWall(Wall* wall);

    void setingAngle(QLineF &l1, QLineF &l2);
private:

    QPolygonF _walls_of_rooms;
    QVector<Window*> _windows;
    QVector<Door*> _doors;
    QVector<Wall*> _decorative_wall;
    float _height;
    float _thickness;
    QVector<GLfloat> uvs=
    {
        50.0f, 50.0f,
        50.0f, -50.0f,
        -50.0f, -50.0f,
        -50.0f, 50.0f,
        50.0f, 50.0f,
        -50.0f, -50.0f,
    };

};

#endif // WALL_H

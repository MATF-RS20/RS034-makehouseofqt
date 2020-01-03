#ifndef DOOR_H
#define DOOR_H

#include <QLineF>
#include <QColor>
#include <QGraphicsLineItem>
#include <QPen>
#include <QPainter>
#include <QOpenGLWindow>
class Door: public QGraphicsLineItem
{
public:
    Door(QLineF doorline, float height=2, float thickness=0.25);

    QLineF door();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QVector<GLfloat> gdoor();

    void generateDoor(QVector<GLfloat> &vert, QVector<GLfloat> &uvss);

private:

    QLineF _doorline;
    float _height;
    float _thickness;
    QVector<GLfloat> uvs=
    {
        0.4f, 0.4f,
        0.4f, -0.4f,
        -0.4f, -0.4f,
        -0.4f, 0.4f,
        0.4f, 0.4f,
        -0.4f, -0.4f,
    };
};

#endif // DOOR_H

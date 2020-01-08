#ifndef WINDOW_H
#define WINDOW_H

#include <QLineF>
#include <QGraphicsLineItem>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QOpenGLWindow>
class Window: public QGraphicsLineItem
{
public:

    Window(QLineF windowline, float height=2, float thickness=0.25);
        QLineF window();


     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

     QVector<GLfloat> gwindow();

     void generateWindow(QVector<GLfloat> &vert, QVector<GLfloat> &uvss);


private:

    QLineF _windowline;
    float _height;
    float _thickness;
    QVector<GLfloat> uvs=
    {

        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
    };
};

#endif // WINDOW_H

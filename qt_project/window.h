#ifndef WINDOW_H
#define WINDOW_H

#include <QLineF>
#include <QGraphicsLineItem>
#include <QColor>
#include <QPen>
#include <QPainter>

class Window: public QGraphicsLineItem
{
public:

    Window(QLineF windowline, float height=2, float thickness=0.25);
        QLineF window();

    /*TODO
    shape()
    */
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QLineF _windowline;
    float _height;
    float _thickness;

};

#endif // WINDOW_H

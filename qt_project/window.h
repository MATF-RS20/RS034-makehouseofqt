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

    Window(QLineF windowline);
        QLineF window();

    /*TODO
    shape()
    */
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QLineF _windowline;
};

#endif // WINDOW_H

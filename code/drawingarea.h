#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QPainter>
class DrawingArea:public QWidget
{
   Q_OBJECT
public:
    DrawingArea(QWidget* parent=0);
    void paintEvent(QPaintEvent* e);
};

#endif // DRAWINGAREA_H

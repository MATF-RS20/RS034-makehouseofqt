#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent):QWidget(parent)
{

}
void DrawingArea::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    int w = this->width();
    int h = this->height();
    int xPart = w/50;
    int yPart = h/50;
    painter.setPen(Qt::darkYellow);
    for(int x = 0; x <= w; x+=xPart)
    {
        painter.drawLine(x, 0, x, h);
    }
    for(int y = 0; y <= h; y+=yPart)
    {
        painter.drawLine(0, y, w, y);
    }
    painter.drawLine(w, 0, w, h);
    painter.drawLine(0, h, w, h);
}

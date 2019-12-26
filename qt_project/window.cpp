#include "window.h"

Window::Window(QLineF windowline, float height, float thickness):_windowline(windowline),_height(height),_thickness(thickness)
{

}

QLineF Window::window(){
    return _windowline;
}

void Window::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setColor(QColor(189,183,107));
    pen.setWidthF(_thickness*40);

    painter->setPen(pen);
    painter->drawLine(_windowline);
}

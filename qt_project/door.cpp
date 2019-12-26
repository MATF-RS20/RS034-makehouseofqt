#include "door.h"

Door::Door(QLineF doorline, float height, float thickness):_doorline(doorline),_height(height),_thickness(thickness)
{

}

QLineF  Door::door(){
    return _doorline;
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setColor(QColor(139,69,19));
    pen.setWidthF(_thickness*40);

    painter->setPen(pen);
    painter->drawLine(_doorline);
}

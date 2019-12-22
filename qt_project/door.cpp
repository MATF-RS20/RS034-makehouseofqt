#include "door.h"

Door::Door(QLineF doorline):_doorline(doorline)
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
    pen.setWidthF(9);

    painter->setPen(pen);
    painter->drawLine(_doorline);
}

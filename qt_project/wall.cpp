#include "wall.h"

Wall::Wall(QPolygonF walls_of_rooms, double height, double thickness):
    _walls_of_rooms(walls_of_rooms),_height(height),_thickness(thickness)
{

}

QPolygonF Wall::walls(){
    return _walls_of_rooms;
}

double Wall::height(){
    return _height;
}

double Wall::thickness(){
    return _thickness;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::darkGray,_thickness*40);

    painter->setPen(pen);
    painter->drawPolygon(_walls_of_rooms);
}

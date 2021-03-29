#include "floor.h"

Floor::Floor(QVector<Wall*> walls, QList<QPolygonF> allPolys):
    _walls(std::move(walls)),_allPolys(std::move(allPolys))
{

}

QVector<Wall*> Floor::getwalls(){
   return _walls;
}


void Floor::setwalls(QVector<Wall *> walls){
   _walls = walls;
}

QList<QPolygonF> Floor::getAllPolys(){
    return _allPolys;
}
void Floor::setAllPolys(QList<QPolygonF> allPolys){
    _allPolys = allPolys;
}

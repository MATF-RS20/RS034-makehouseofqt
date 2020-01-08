#include "floor.h"

Floor::Floor(QVector<Wall*> walls, QList<QPolygonF> allPolys):
    _walls(walls),_allPolys(allPolys)
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

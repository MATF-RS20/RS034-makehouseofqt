#include "floor.h"

Floor::Floor(QVector<Wall*> walls):
    _walls(walls)
{

}

QVector<Wall*> Floor::getwalls(){
   return _walls;
}


void Floor::setwalls(QVector<Wall *> walls){
   _walls= walls;
}


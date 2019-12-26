#include "floor.h"

Floor::Floor(QVector<Wall*> walls, QVector<Window*> windows, QVector<Door*> doors):
    _walls(walls), _windows(windows), _doors(doors)
{

}

QVector<Wall*> Floor::getwalls(){
   return _walls;
}

QVector<Window*> Floor::getwindows(){
    return _windows;
}

QVector<Door*> Floor::getdoors(){
    return _doors;
}

void Floor::setwalls(QVector<Wall *> walls){
   _walls= walls;
}
void Floor::setwindows(QVector<Window *> windows){
   _windows= windows;
}
void Floor::setdoors(QVector<Door *> doors){
   _doors= doors;
}

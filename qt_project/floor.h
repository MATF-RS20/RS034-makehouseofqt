#ifndef FLOOR_H
#define FLOOR_H

#include <QGraphicsItem>
#include <QObject>
#include "QWidget"
#include "wall.h"
#include "window.h"
#include "door.h"
#include <QVector>
class Floor
{
    //Q_OBJECT
public:
    Floor(QVector<Wall*> walls, QVector<Window*> windows, QVector<Door*> doors);
    QVector<Wall*> getwalls();
    QVector<Window*> getwindows();
    QVector<Door*> getdoors();
    void setwalls(QVector<Wall*> walls);
    void setwindows(QVector<Window*> windows);
    void setdoors(QVector<Door*> doors);
private:
    QVector<Wall*> _walls;
    QVector<Window*> _windows;
    QVector<Door*> _doors;
};

#endif // FLOOR_H

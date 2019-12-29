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
    Floor(QVector<Wall*> walls);
    QVector<Wall*> getwalls();
    void setwalls(QVector<Wall*> walls);
private:
    QVector<Wall*> _walls;
};

#endif // FLOOR_H

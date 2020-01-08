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
    Floor(QVector<Wall*> walls, QList<QPolygonF> allPolys);
    QVector<Wall*> getwalls();
    void setwalls(QVector<Wall*> walls);

    QList<QPolygonF> getAllPolys();
    void setAllPolys(QList<QPolygonF> allPolys);
private:
    QVector<Wall*> _walls;
    QList<QPolygonF> _allPolys;
};

#endif // FLOOR_H

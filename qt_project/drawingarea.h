#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QtGui>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QGraphicsView>
#include <QBrush>
#include <QPen>
#include <QHoverEvent>
#include <QString>
#include <math.h>
#include <QVector>
#include <QPainterPath>
#include <QKeyEvent>
#include "wall.h"
#include "window.h"
#include "door.h"

class DrawingArea : public QWidget
{
    Q_OBJECT

public:

    DrawingArea(QWidget *parent = 0);

    QSize sizeHint() const;

    void paintEvent( QPaintEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void enterEvent(QMouseEvent *e);

    void keyPressEvent(QKeyEvent *e);

    int my_x, my_y;

    QPainter painter;

    bool on_mouse;

    bool aviable_complete_polygon;

signals:

    void releaseMouse();
    void have_points(int);
    void send_polygon_size(QString);
    void leaveEvent(QMouseEvent*);
    void HoverLeave( QPointF & pos, const QPointF & oldPos);
    void enableCompleteDrawing(bool);
    void fail_to_add_peak(QString);
    void have_been_reseting(QString);
    void update_status(QString);
    void update_status_finish(QString);

public slots:

    void complete_drawing();
    void reset_drawing();

private slots:

    void changeOnMouse();


private:

    bool start_exist;
    bool aviable_here_place_newPoint;
    bool first_line_exist;
    bool isIntersect(QLineF line1, QLineF line2);
    bool polygon_is_complited;
    bool chosen_window;
    bool chosen_door;
    QVector<QLineF>::Iterator ii;
    QVector<QPointF> polygonPoints;
    QVector<QLineF> lines;
    QPointF startPoint;
    QPointF point1, point2;
    QPen pen_green;
    QPen pen_red;
    QPen last_line_style;
    QPen first_line_style;
    QPen last_line_style_fail;
    QVector<Wall*> walls_for_rooms;
    QVector<Door*> doors_for_rooms;
    QVector<Window*> windows_for_rooms;
    void reinitialize();
};

#endif // DRAWINGAREA_H

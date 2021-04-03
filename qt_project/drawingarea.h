#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include "door.h"
#include "floor.h"
#include "inputdialog.h"
#include "wall.h"
#include "window.h"
#include <QBrush>
#include <QGraphicsView>
#include <QPainterPath>
#include <QPen>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QtGui>
#include <QtWidgets/QApplication>
#include <math.h>

class DrawingArea : public QWidget {
  Q_OBJECT

public:
  DrawingArea(QWidget *parent = 0);

  QSize sizeHint() const;

  void paintEvent(QPaintEvent *e);

  void mouseMoveEvent(QMouseEvent *e);

  void mousePressEvent(QMouseEvent *e);

  void enterEvent(QMouseEvent *e);

  void keyPressEvent(QKeyEvent *e);

  int my_x, my_y;

  QPainter painter;

  bool on_mouse;

  bool aviable_complete_polygon;

  QVector<Wall *> getWall();
  QVector<Floor *> getFloor();
signals:

  void releaseMouse();
  void have_points(int);
  void send_polygon_size(QString);
  void leaveEvent(QMouseEvent *);
  void HoverLeave(QPointF &pos, const QPointF &oldPos);
  void enableCompleteDrawing(bool);
  void fail_to_add_peak(QString);
  void have_been_reseting(QString);
  void update_status(QString);
  void update_status_finish(QString);

public slots:

  void complete_drawing();
  void reset_drawing();
  void changedParams();

private slots:

  void changeOnMouse();

private:
  bool start_exist;
  bool aviable_here_place_newPoint;
  bool first_line_exist;
  bool polygon_is_complited;
  bool chosen_window;
  bool chosen_door;
  bool intersect_happened;
  bool good_room;
  QVector<QLineF>::Iterator ii;
  QVector<QPointF> polygonPoints;
  QVector<QLineF> lines;
  QList<QPolygonF> allPolys;
  QPointF startPoint;
  QPointF point1, point2;
  QPen pen_green;
  QPen pen_red;
  QPen last_line_style;
  QPen first_line_style;
  QPen last_line_style_fail;
  QVector<Wall *> walls_for_rooms;
  QVector<Floor *> floors;
  InputDialog *input_dialog;
  float wall_height;
  float wall_thickness;
  int last_floor;
  void reinitialize();
  void reinit_floors();
  static float polygonArea(QPolygonF p, int n);
  bool canMakeRoom();
  static bool isIntersect(QLineF line1, QLineF line2);
};

#endif // DRAWINGAREA_H

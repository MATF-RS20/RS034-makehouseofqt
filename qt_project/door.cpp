#include "door.h"

Door::Door(QLineF doorline, float height, float thickness)
    : _doorline(doorline), _height(height), _thickness(thickness) {}

QLineF Door::door() { return _doorline; }

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  QPen pen;
  pen.setColor(QColor(95, 158, 160));
  pen.setWidthF(5);
  painter->setPen(pen);
  float d = (_doorline.x2() - _doorline.x1());

  float x1 = (_doorline.x1());
  float x2 = (_doorline.x2());

  float y1 = (_doorline.y1());
  float y2 = (_doorline.y2());

  if (abs(x1 - x2) > abs(y1 - y2) and y1 >= 300) {
    if (x2 > x1) {
      QRectF rectangle(QPointF(x1 - d, y1 - 90), QPointF(x2, y1 + 90));

      painter->drawPie(rectangle, _doorline.angle() * 16, 90 * 16);
    } else {
      float d = (_doorline.x1() - _doorline.x2());
      QRectF rectangle(QPointF(x2 - d, y2 - 90), QPointF(x1, y2 + 90));
      QLineF line(QPointF(x2, y2), QPointF(x1, y1));
      float startangle = (line.angle());
      painter->drawPie(rectangle, startangle * 16, 90 * 16);
    }

  } else if (abs(x1 - x2) > abs(y1 - y2) and y1 < 300) {
    if (x2 < x1) {
      QRectF rectangle(QPointF(x1 - d, y1 - 90), QPointF(x2, y1 + 90));

      painter->drawPie(rectangle, _doorline.angle() * 16, 90 * 16);
    } else {
      float d = (_doorline.x1() - _doorline.x2());
      QRectF rectangle(QPointF(x2 - d, y2 - 90), QPointF(x1, y2 + 90));
      QLineF line(QPointF(x2, y2), QPointF(x1, y1));
      float startangle = (line.angle());
      painter->drawPie(rectangle, startangle * 16, 90 * 16);
    }
  } else if (abs(y1 - y2) > abs(x1 - x2) and x1 < 400) {
    if (y2 > y1) {
      float d = (_doorline.y2() - _doorline.y1());
      QRectF rectangle(QPointF(x1 - 60, y1 - d), QPointF(x1 + 60, y2));

      painter->drawPie(rectangle, _doorline.angle() * 16, 90 * 16);
    } else {
      float d = (_doorline.y1() - _doorline.y2());
      QRectF rectangle(QPointF(x2 - 60, y2 - d), QPointF(x2 + 60, y1));
      QLineF line(QPointF(x2, y2), QPointF(x1, y1));
      float startangle = (line.angle());
      painter->drawPie(rectangle, startangle * 16, 90 * 16);
    }
  } else if (abs(y1 - y2) > abs(x1 - x2) and x1 >= 400) {
    if (y2 < y1) {
      float d = (_doorline.y2() - _doorline.y1());
      QRectF rectangle(QPointF(x1 - 60, y1 - d), QPointF(x1 + 60, y2));

      painter->drawPie(rectangle, _doorline.angle() * 16, 90 * 16);
    } else {
      float d = (_doorline.y1() - _doorline.y2());
      QRectF rectangle(QPointF(x2 - 60, y2 - d), QPointF(x2 + 60, y1));
      QLineF line(QPointF(x2, y2), QPointF(x1, y1));
      float startangle = (line.angle());
      painter->drawPie(rectangle, startangle * 16, 90 * 16);
    }
  }
}
QVector<GLfloat> Door::gdoor() {
  qreal c = 20.0;
  GLfloat p1x = (GLfloat)_doorline.p1().x() / c;
  GLfloat p1y = (GLfloat)_doorline.p1().y() / c;
  GLfloat p2x = (GLfloat)_doorline.p2().x() / c;
  GLfloat p2y = (GLfloat)_doorline.p2().y() / c;
  return {
      p1x,
      0,
      p1y,
      p2x,
      0,
      p2y,
      p1x,
      (GLfloat)2 * _height,
      p1y,
      p1x,
      (GLfloat)2 * _height,
      p1y,
      p2x,
      0,
      p2y,
      p2x,
      (GLfloat)2 * _height,
      p2y,
  };
}
void Door::generateDoor(QVector<GLfloat> &vert, QVector<GLfloat> &uvss) {
  QVector<GLfloat> array = gdoor();
  for (auto t : array)
    vert.push_back(t);
  for (auto p : uvs)
    uvss.push_back(p);
}

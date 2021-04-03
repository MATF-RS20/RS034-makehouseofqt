#ifndef DOOR_H
#define DOOR_H

#include <QColor>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QOpenGLWindow>
#include <QPainter>
#include <QPen>
class Door : public QGraphicsLineItem {
public:
  Door(QLineF doorline, float height = 2, float thickness = 0.25);

  QLineF door();

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  QVector<GLfloat> gdoor();

  void generateDoor(QVector<GLfloat> &vert, QVector<GLfloat> &uvss);

private:
  QLineF _doorline;
  float _height;
  float _thickness;
  QVector<GLfloat> uvs = {

      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
  };
};

#endif // DOOR_H

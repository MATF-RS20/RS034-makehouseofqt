#ifndef WINDOW_H
#define WINDOW_H

#include <QColor>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QOpenGLWindow>
#include <QPainter>
#include <QPen>
class Window : public QGraphicsLineItem {
public:
  Window(QLineF windowline, float height = 2, float thickness = 0.25);
  QLineF window();

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  QVector<GLfloat> gwindow();

  void generateWindow(QVector<GLfloat> &vert, QVector<GLfloat> &uvss);

private:
  QLineF _windowline;
  float _height;
  float _thickness;
  QVector<GLfloat> uvs = {
      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
  };
};

#endif // WINDOW_H

#include "window.h"

Window::Window(QLineF windowline, float height, float thickness)
    : _windowline(windowline), _height(height), _thickness(thickness) {}

QLineF Window::window() { return _windowline; }

void Window::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  QPen pen;
  pen.setColor(QColor(189, 183, 107));
  pen.setWidthF(_thickness * 40);

  painter->setPen(pen);
  painter->drawLine(_windowline);
}
QVector<GLfloat> Window::gwindow() {
  qreal c = 20.0;
  GLfloat p1x = (GLfloat)_windowline.p1().x() / c;
  GLfloat p1y = (GLfloat)_windowline.p1().y() / c;
  GLfloat p2x = (GLfloat)_windowline.p2().x() / c;
  GLfloat p2y = (GLfloat)_windowline.p2().y() / c;
  return {
      p1x,
      _height,
      p1y,
      p2x,
      _height,
      p2y,
      p1x,
      (GLfloat)2 * _height,
      p1y,
      p1x,
      (GLfloat)2 * _height,
      p1y,
      p2x,
      _height,
      p2y,
      p2x,
      (GLfloat)2 * _height,
      p2y,
  };
}
void Window::generateWindow(QVector<GLfloat> &vert, QVector<GLfloat> &uvss) {
  QVector<GLfloat> array = gwindow();
  for (auto t : array)
    vert.push_back(t);
  for (auto p : uvs)
    uvss.push_back(p);
}

#ifndef WALLSMODELVIEW_H
#define WALLSMODELVIEW_H


#include <GL/glu.h>
#include <QtOpenGL>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QColorDialog>
#include <QColor>
#include "wall.h"

class WallsModelView : public QOpenGLWindow
{
public:
    WallsModelView(QVector<Wall*> walls);

protected:

    void initializeGL();

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void initialize_vbos();


private:
    QOpenGLContext* openGLContext;
    QOpenGLFunctions* openGLFunctions;
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLVertexArrayObject* vao;
    QOpenGLBuffer* vbo_vertices;
    QOpenGLBuffer* vbo_colors;
    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;
//    QOpenGLBuffer* vbo_roof_vertices;
//    QOpenGLBuffer* vbo_roof_colors;
//    QVector<GLfloat> roof_vertices;
//    QVector<GLfloat> roof_colors;
    QTime* time;
    QColor _color;
    QPointF lastPos;
    QVector<Wall*> _walls;
    int currentTime = 0;
    int oldTime = 0;
    float deltaTime = 0;
    float rotation = 0;
    GLfloat rotationX=0, rotationY=0, rotationZ=0;
};

#endif // WALLSMODELVIEW_H

#ifndef HOUSE_H
#define HOUSE_H
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGL/QGL>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLContext>
#include <QtOpenGL/QGLColormap>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QtOpenGLVersion>
#include <QtOpenGL/QtOpenGLDepends>
#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLShader>
#include <QtOpenGL/QGLBuffer>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QColorDialog>
#include <QColor>
#include <QSurface>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QImage>
#include "floor.h"
#include "selectingform.h"

class House :public QOpenGLWindow
{
    Q_OBJECT
public:
    House(QVector<Floor*> floors);
    void keyPressEvent(QKeyEvent *event);
    ~House(){}
public slots:
    void changingTextures(int i);
protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QOpenGLContext* openGLContext;
    QOpenGLFunctions* openGLFunctions;
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLVertexArrayObject* vao;
    QOpenGLBuffer* vbo_vertices;
    QOpenGLBuffer* vbo_uvs;
    QVector<GLfloat> vertices;
    QVector<GLfloat> uvs;

    QVector<QOpenGLBuffer*> _vbo_vertices;
    QVector<QOpenGLBuffer*> _vbo_uvs;

    QOpenGLTexture* texture[4];
    QVector<QVector<GLfloat>> _vertices;
    QVector<QVector<GLfloat>> _uvs;

    QVector<Floor*> _floors;
    QString str= "./k.bmp";
    QVector<QString> tex={"./k.bmp", "./beige.jpg", "./window.bmp", "./d2.png"};
    float angle=0.0;
    float lx=0.0f,lz=-1.0f;
    float x=0.0f,z=0.0f, y=2.0f;
    int i=0, j=0;

    SelectingForm *sf;
    void initializeAgain();
    void deletingDataForDrawing();
};


#endif // HOUSE_H

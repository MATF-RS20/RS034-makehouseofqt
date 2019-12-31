#include "wallsmodelview.h"
WallsModelView::WallsModelView(QVector<Wall*> walls):_walls(walls)
{
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 2);
    setFormat(format);

    openGLContext = new QOpenGLContext();
    openGLContext->setFormat(format);
    openGLContext->create();
    openGLContext->makeCurrent(this);

    time = new QTime();
    time->start();
}

void WallsModelView::initializeGL()
{
    openGLFunctions = openGLContext->functions();
    glEnable(GL_DEPTH_TEST);

    _color= QColor(Qt::white);
    static const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 posAttr;\n"
    "layout(location = 1) in vec3 colAttr;\n"
    "uniform mat4 matrix;\n"
    "out vec3 fragCol;\n"
    "void main() {\n"
    "fragCol = colAttr;\n"
    "gl_Position = matrix * vec4(posAttr, 1.0); }";

    static const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 fragCol;\n"
    "out vec4 col;\n"
    "void main() {\n"
    "col = vec4(fragCol, 1.0); }";

    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shaderProgram->link();


    for(Wall *w: _walls){
        w->generateWallsForView(vertices, colors, _color);
    }

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();

    initialize_vbos();

    vao->release();
}

void WallsModelView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    currentTime = time->elapsed();
    deltaTime = (float)(currentTime - oldTime) / 1000.0f;
    oldTime = currentTime;

    glViewport(0, 0, this->width(), this->height());

    glClearColor(0.39f, 0.58f, 0.93f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao->bind();
    shaderProgram->bind();

    rotation += deltaTime ;


    QMatrix4x4 matrixMVP;
    QMatrix4x4 model, view, projection;
    model.translate(0, 0.5, 0);

    model.rotate(rotationX, 1, 0, 0);
    model.rotate(rotationY, 0, 1, 0);
    model.rotate(rotationZ,0, 0, 1);
    view.lookAt(QVector3D(5+sin(rotation), 5, 5+(-cos(rotation))), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    projection.perspective(60.0f, ((float)this->width()/(float)this->height()), 0.1f, 100.0f);
    matrixMVP = projection * view * model;
    shaderProgram->setUniformValue("matrix", matrixMVP);

    vbo_vertices->bind();
    shaderProgram->bindAttributeLocation("posAttr", 0);
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    vbo_colors->bind();
    shaderProgram->bindAttributeLocation("colAttr", 1);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    shaderProgram->release();
    vao->release();

    this->update();
}

void WallsModelView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    glViewport(0, 0, this->width(), this->height());
    this->update();
}

void WallsModelView::mouseDoubleClickEvent(QMouseEvent *event){
    Q_UNUSED(event);
    QColor color= QColorDialog::getColor();

    if(color.isValid())
        _color=color;

    vertices.clear();
    colors.clear();

    for(Wall* w: _walls)
        w->generateWallsForView(vertices, colors, _color);

    initialize_vbos();

    this->update();
}

void WallsModelView::mousePressEvent(QMouseEvent *event){
    lastPos=event->pos();
}

void WallsModelView::mouseMoveEvent(QMouseEvent *event){
    GLfloat dx= (GLfloat) (event->x() - lastPos.x()) / width();
    GLfloat dy= (GLfloat) (event->y() - lastPos.y()) / height();

    if(event->buttons()==Qt::LeftButton){
        rotationX +=180*dy;
        rotationY += 180*dx;
        this->update();
    }else if(event->buttons()==Qt::RightButton){
        rotationX +=180*dy;
        rotationZ += 180*dx;
        this->update();
    }
    lastPos= event->pos();
}

void WallsModelView::initialize_vbos(){
    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo_vertices->create();
    vbo_vertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_vertices->bind();
    vbo_vertices->allocate(vertices.begin(), vertices.size() * sizeof(GLfloat));

    vbo_colors = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo_colors->create();
    vbo_colors->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_colors->bind();
    vbo_colors->allocate(colors.begin(), colors.size() * sizeof(GLfloat));


}


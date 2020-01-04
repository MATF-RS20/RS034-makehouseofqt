#include "house.h"
#include <QFileDialog>
House::House(QVector<Floor*> floors):_floors(floors)
{

    this->setTitle("Setnja po kuci");
    sf=new SelectingForm();
    connect(this->sf, SIGNAL(sendingChoice(int)), this, SLOT(changingTextures(int)), Qt::DirectConnection);

    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 2);
    setFormat(format);

    openGLContext = new QOpenGLContext();
    openGLContext->setFormat(format);
    openGLContext->create();
    openGLContext->makeCurrent(this);

}

void House::initializeGL()
{
    openGLFunctions = openGLContext->functions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glCullFace( GL_FRONT);


    for(int i=0; i<4; i++){

        qDebug()<<QApplication::applicationDirPath();
        texture[i] = new QOpenGLTexture(QImage(QApplication::applicationDirPath()+tex[i]).mirrored());
        texture[i]->setMinificationFilter(QOpenGLTexture::Nearest);
        texture[i]->setMagnificationFilter(QOpenGLTexture::Linear);

    }

    static const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 posAttr;\n"
    "layout(location = 1) in vec2 uvAttr\n;"
    "uniform mat4 matrix;\n"
    "out vec3 fragPos;\n"
    "out vec2 fragUV;\n"
    "void main() {\n"
    "fragPos = posAttr;\n"
    "fragUV = uvAttr;\n"
    "gl_Position = matrix * vec4(posAttr, 1.0); }";

    static const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 fragPos;\n"
    "in vec2 fragUV;\n"
    "uniform sampler2D tex;\n"
    "out vec4 col;\n"
    "void main() {\n"
    "vec4 texCol = texture(tex, fragUV);\n"
    "col = texCol; }";


    shaderProgram = new QOpenGLShaderProgram(this);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    shaderProgram->link();
    QVector<GLfloat> vertices=
    {

        -100.0f,0.0f,-100.0f,
        100.0f,0.0f,-100.0f,
        -100.0f,0.0f, 100.0f,
        100.0f,0.0f,-100.0f,
        100.0f,0.0f, 100.0f,
        -100.0f,0.0f, 100.0f


    };
    QVector<GLfloat> uvs=
    {
        -50.0f, -50.0f,
        50.0f, -50.0f,
        -50.0f, 50.0f,
        50.0f, -50.0f,
        50.0f, 50.0f,
        -50.0f, 50.0f

    };

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();

    _floors.at(0)->getwalls().at(0)->generateHouseWalls(_vertices, _uvs);

    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo_vertices->create();
    vbo_vertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_vertices->bind();
    vbo_vertices->allocate(vertices.begin(), vertices.size() * sizeof(GLfloat));

    vbo_uvs = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo_uvs->create();
    vbo_uvs->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_uvs->bind();
    vbo_uvs->allocate(uvs.begin(), uvs.size() * sizeof(GLfloat));

    initializeAgain();

    vao->release();
}

void House::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


    glViewport(0, 0, this->width(), this->height());

    glClearColor(0.39f, 0.58f, 0.93f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vao->bind();
    shaderProgram->bind();


    QMatrix4x4 matrixMVP;
    QMatrix4x4 model, view, projection;
    QPointF mid=_floors.at(j)->getwalls().at(i)->middleOfTheRoom()/20.0;
    view.lookAt(QVector3D(mid.x()+x, y, mid.y()+z), QVector3D(mid.x()+x+lx, y, mid.y()+z+lz), QVector3D(0, 1, 0));
    projection.perspective(60.0f, ((float)this->width()/(float)this->height()), 0.1f, 100.0f);
    matrixMVP = projection * view * model;
    shaderProgram->setUniformValue("matrix", matrixMVP);


    vbo_vertices->bind();
    shaderProgram->bindAttributeLocation("posAttr", 0);
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    vbo_uvs->bind();
    shaderProgram->bindAttributeLocation("uvAttr", 1);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, 0, 2);
    texture[0]->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    texture[0]->release();


    for(int i=0;i<_vertices.size();i++){
        _vbo_vertices.at(i)->bind();
        shaderProgram->bindAttributeLocation("posAttr", 0);
        shaderProgram->enableAttributeArray(0);
        shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3);

        _vbo_uvs.at(i)->bind();
        shaderProgram->bindAttributeLocation("uvAttr", 1);
        shaderProgram->enableAttributeArray(1);
        shaderProgram->setAttributeBuffer(1, GL_FLOAT, 0, 2);
        texture[i+1]->bind();
        glDrawArrays(GL_TRIANGLES,0,_vertices.at(i).size());
        texture[i+1]->release();
    }



    shaderProgram->release();
    vao->release();

    this->update();


}

void House::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    glViewport(0, 0, this->width(), this->height());
    this->update();
}
void House::keyPressEvent(QKeyEvent *event){
    float fraction = 0.5f; //bilo je 0.1f

    if(event->key()==Qt::Key_Up){
        x += lx * fraction;
        z += lz * fraction;
    }else if(event->key()==Qt::Key_Down){
        x -= lx * fraction;
        z -= lz * fraction;
    }else if(event->key()==Qt::Key_Left){
        angle -= 0.05f;
        lx = sin(angle);
        lz = -cos(angle);
    }else if(event->key()==Qt::Key_Right){
        angle += 0.05f;
        lx = sin(angle);
        lz = -cos(angle);
    }else if(event->key()==Qt::Key_Space){
            y=15;
    }else if(event->key()==Qt::Key_D){
        if(i+1>=_floors.at(j)->getwalls().size())
            return;
        i++;

        deletingDataForDrawing();

        _floors.at(j)->getwalls().at(i)->generateHouseWalls(_vertices, _uvs);

        initializeAgain();

    }else if(event->key()==Qt::Key_A){
        if(i-1<0)
            return;
        i--;

        deletingDataForDrawing();

       _floors.at(j)->getwalls().at(i)->generateHouseWalls(_vertices, _uvs);

        initializeAgain();

    }else if(event->key()==Qt::Key_W){
        if(j+1>=_floors.size())
            return;


        j++;

        deletingDataForDrawing();
        i=0;
        _floors.at(j)->getwalls().at(i)->generateHouseWalls(_vertices, _uvs);

        initializeAgain();

    }else if(event->key()==Qt::Key_S){
        if(j-1<0)
            return;
        j--;
        i=0;
        deletingDataForDrawing();

       _floors.at(j)->getwalls().at(i)->generateHouseWalls(_vertices, _uvs);

        initializeAgain();

    }else if(event->key()==Qt::Key_C){

        sf->show();
    }
    this->update();
}

void House::initializeAgain(){
    for(int i=0;i<_vertices.size();i++){
        _vbo_vertices.push_back(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        _vbo_vertices.last()->create();
        _vbo_vertices.last()->setUsagePattern(QOpenGLBuffer::StaticDraw);
        _vbo_vertices.last()->bind();
        _vbo_vertices.last()->allocate(_vertices.at(i).begin(), _vertices.at(i).size()* sizeof(GLfloat));

        _vbo_uvs.push_back( new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        _vbo_uvs.last()->create();
        _vbo_uvs.last()->setUsagePattern(QOpenGLBuffer::StaticDraw);
        _vbo_uvs.last()->bind();
        _vbo_uvs.last()->allocate(_uvs.at(i).begin(), _uvs.at(i).size() * sizeof(GLfloat));
    }
    angle=0.0;
    lx=0.0f,lz=-1.0f;
    x=0.0f,z=0.0f, y=2.0f;
}

void House::changingTextures(int i){

    tex[i] = QFileDialog::getOpenFileName();
    texture[i] = new QOpenGLTexture(QImage(tex[i]).mirrored());
    texture[i]->setMinificationFilter(QOpenGLTexture::Nearest);
    texture[i]->setMagnificationFilter(QOpenGLTexture::Linear);
    this->update();

}

void House::deletingDataForDrawing(){
    for(auto p: _vertices)
        p.clear();
   for(auto p: _uvs)
       p.clear();
   for(auto p: _vbo_vertices)
       delete p;
  for(auto p: _vbo_uvs)
      delete p;
   _vertices.clear();
   _uvs.clear();
   _vbo_vertices.clear();
   _vbo_uvs.clear();

}

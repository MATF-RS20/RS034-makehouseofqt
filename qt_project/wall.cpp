#include "wall.h"
#include <QString>
Wall::Wall(QPolygonF walls_of_rooms, double height, double thickness):
    _walls_of_rooms(walls_of_rooms),_height(height),_thickness(thickness)
{

}

QPolygonF Wall::walls(){
    return _walls_of_rooms;
}

double Wall::height(){
    return _height;
}

double Wall::thickness(){
    return _thickness;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::darkGray,_thickness*40);

    painter->setPen(pen);
    painter->drawPolygon(_walls_of_rooms);

    for(auto w: _decorative_wall)
        w->paint(painter, Q_NULLPTR, Q_NULLPTR);

    for(auto w: _windows)
        w->paint(painter, Q_NULLPTR, Q_NULLPTR);

    for(auto d: _doors)
        d->paint(painter, Q_NULLPTR, Q_NULLPTR);
}

void Wall::addWindow(Window *window){
    _windows.push_back(window);
}

void Wall::addDoor(Door *door){
    _doors.push_back(door);
}

QVector<Window*> Wall::getWindows(){
    return _windows;
}

QVector<Door*> Wall::getDoors(){
    return _doors;
}

bool Wall::containsPoints(QLineF &l2){


    auto start= _walls_of_rooms.begin();
    auto end= _walls_of_rooms.end();



    QPolygonF p1;
    p1<<l2.p1()<<l2.p2()<<l2.p1();

    QPolygonF p2;
    p1<<*start<<*(start+1)<<*start;
    while (start!=end-1) {

        auto l1=QLineF(*start, *(start+1));
        if(angle_is_wrong(l1, l2) || p1.containsPoint(l1.p1(), Qt::FillRule()) ||  p1.containsPoint(l1.p2(), Qt::FillRule())){
            start++;
            continue;
        }
        QPointF p;
        if((p2.containsPoint(l2.p1(), Qt::FillRule()) || p2.containsPoint(l2.p2(), Qt::FillRule()))){
            return true;
        }

         if(l1.intersect(l2,&p)==QLineF::BoundedIntersection){
             return true;
         }

         if(isIntersect(l1, l2)){

             return true;
         }

        start++;
    }

    auto decstart= _decorative_wall.begin();
    auto decend= _decorative_wall.end();
    while(decstart!=decend){
        if((*decstart)->containsPoints(l2))
            return true;
        decstart++;
    }
    return false;
}

QPointF Wall::middleOfTheRoom(){
    float x=0, y=0;
    for (QPointF p: _walls_of_rooms){
        x+=p.x();
        y+=p.y();
    }
    return QPointF(x,y)/_walls_of_rooms.size();
}

QVector<GLfloat> Wall::wall(QPointF p1, QPointF p2, GLfloat c, float h){

    GLfloat p1x = (GLfloat) p1.x()/c;
    GLfloat p2x = (GLfloat) p2.x()/c;
    GLfloat p1y = (GLfloat) p1.y()/c;
    GLfloat p2y = (GLfloat) p2.y()/c;
    QVector<GLfloat> array{
        p2x, h, p2y,
        p2x, 0, p2y,
        p1x, 0, p1y,
        p1x, h, p1y,
        p2x, h, p2y,
        p1x, 0, p1y,
    };

    return array;
}
void Wall::generateWallsForView(QVector<GLfloat> &vertices, QVector<GLfloat> &colors, QColor color){

    auto start= _walls_of_rooms.begin();
    auto end= _walls_of_rooms.end()-1;
    while( start != end){
        QVector<GLfloat> array= wall(*start, *(start+1), 200.0, _height/2);

        for(auto a: array)
            vertices.push_back(a);

        for(int i=0; i<6; i++){
            colors.push_back(color.redF());
            colors.push_back(color.greenF());
            colors.push_back(color.blueF());
        }

        start++;
    }

    auto decstart=_decorative_wall.begin();
    auto decend= _decorative_wall.end();
    while(decstart != decend){
        (*decstart)->generateWallsForView(vertices, colors, color);
        decstart++;
    }
}
QVector<GLfloat> Wall::roof(QPointF p1, QPointF p2){
    QPointF middle = middleOfTheRoom();
    GLfloat c=200.0;
    GLfloat p1x = (GLfloat) p1.x()/c;
    GLfloat p2x = (GLfloat) p2.x()/c;
    GLfloat p1y = (GLfloat) p1.y()/c;
    GLfloat p2y = (GLfloat) p2.y()/c;

    GLfloat mx = (GLfloat) middle.x()/c;
    GLfloat my = (GLfloat) middle.y()/c;
    return {
         mx, (GLfloat) (_height+1.5)/2, my,
         p2x, (GLfloat) _height/2,  p2y,
         p1x, (GLfloat) _height/2,  p1y
    };
}
void Wall::generateRoof(QVector<GLfloat> &vertices, QVector<GLfloat> &roof_color){
     auto start = _walls_of_rooms.begin();
     auto end = _walls_of_rooms.end()-1;

     while(start!=end){
         QVector<GLfloat> array = roof(*start, *(start+1));

         for(auto a: array)
             vertices.push_back(a);

         for(int i=0;i<3;i++){
             roof_color.push_back(1);
             roof_color.push_back(0);
             roof_color.push_back(0);
         }
         start++;
     }
}

bool Wall::angle_is_wrong(QLineF l1, QLineF l2){
    qreal angle= abs(l1.angleTo(l2));
    return (angle<175 && angle>5) || (angle>185 && angle<355);
}

bool Wall::isIntersect(QLineF line1, QLineF line2)
{
    double a1,a2,a3,a4; double x11,y11,x12,y12, x21, y21,x22,y22;
    x11 = line1.p1().x(); y11 = line1.p1().y();
    x12 = line1.p2().x(); y12 = line1.p2().y();
    x21 = line2.p1().x(); y21 = line2.p1().y();
    x22 = line2.p2().x(); y22 = line2.p2().y();


    a4=(x22-x21)*(y11-y21)-(y22-y21)*(x11-x21);
    a3=(x22-x21)*(y12-y21)-(y22-y21)*(x12-x21);
    a2=(x12-x11)*(y21-y11)-(y12-y11)*(x21-x11);
    a1=(x12-x11)*(y22-y11)-(y12-y11)*(x22-x11);

    return ((a1*a2 < 0.0) && (a3*a4 < 0.0));
}

void Wall::generateHouseWalls(QVector<QVector<GLfloat> > &vert, QVector<QVector<GLfloat> > &uvss){
    auto startw= _walls_of_rooms.begin();
    auto endw = _walls_of_rooms.end()-1;
    QVector<GLfloat> v,  u;
    while(startw!= endw){
        QVector<GLfloat> wallie=wall(*startw, *(startw+1), 20.0, 3*_height);
        for(auto nzu: wallie)
            v.push_back(nzu);

        for(auto a:uvs)
            u.push_back(a);
        startw++;
    }

    auto decstart=_decorative_wall.begin();
    auto decend= _decorative_wall.end();
    while(decstart != decend){
        QVector<GLfloat> wallie= wall((*decstart)->walls()[0],(*decstart)->walls()[1], 20.0, 3*_height);
        for(auto nzu: wallie)
            v.push_back(nzu);

        for(auto a:uvs)
            u.push_back(a);

        decstart++;
    }

    vert.push_back(v);
    uvss.push_back(u);

    v.clear();
    u.clear();

    auto startwd= _windows.begin();
    auto endwd= _windows.end();

    if(startwd!=endwd){
        while(startwd!=endwd){
            QVector<GLfloat> v1;
            QVector<GLfloat> u1;
            (*startwd)->generateWindow(v1,u1);
            for(auto a: v1)
                v.push_back(a);
            for(auto a: u1)
                u.push_back(a);
            startwd++;
        }

    }else{
        v.push_back(0);
        u.push_back(0);
        v.push_back(0);
        u.push_back(0);
        v.push_back(0);
    }
    vert.push_back(v);
    uvss.push_back(u);

    v.clear();
    u.clear();

    auto startd= _doors.begin();
    auto endd= _doors.end();

    if(startd!=endd){
        while(startd!=endd){
            QVector<GLfloat> v1;
            QVector<GLfloat> u1;
            (*startd)->generateDoor(v1,u1);
            for(auto a: v1)
                v.push_back(a);
            for(auto a: u1)
                u.push_back(a);
            startd++;
        }

    }else{
        v.push_back(0);
        u.push_back(0);
        v.push_back(0);
        u.push_back(0);
        v.push_back(0);
    }
    vert.push_back(v);
    uvss.push_back(u);

}

bool Wall::canMakeDecorativeWall(QVector<QPointF> line){


    auto start= _walls_of_rooms.begin();
    auto end= _walls_of_rooms.end();


    auto l2=QLineF(line[0], line[1]);

    QPolygonF p1;
    p1<<line[0]<<line[1]<<line[2];

    QPolygonF p2;
    p1<<*start<<*(start+1)<<*start;
    while (start!=end-1) {

        auto l1=QLineF(*start, *(start+1));

        QPointF p;
       if(angle_is_wrong(l1, l2) && ( l1.intersect(l2,&p)==QLineF::BoundedIntersection || p2.containsPoint(l2.p1(), Qt::FillRule()) || p2.containsPoint(l2.p2(), Qt::FillRule())))
           return true;


        start++;
    }
    return false;
}

void Wall::addDecorativeWall(Wall *wall){
    _decorative_wall.push_back(wall);
}

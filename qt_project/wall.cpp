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

bool Wall::containsPoints(QVector<QPointF> lines){
    auto start= _walls_of_rooms.begin();
    auto end= _walls_of_rooms.end();

    QVector<QRectF> r;
    while (start!=end-1) {

        if(start->x()==(start+1)->x()){

            if(start->y()<(start+1)->y()){

                r.push_back(QRectF(QPointF(start->x()-0.5,start->y()), QPointF((start+1)->x()+0.5,(start+1)->y())));

            }else{

                r.push_back(QRectF(QPointF((start+1)->x()-0.5,(start+1)->y()), QPointF((start)->x()+0.5,(start)->y())));

            }
        }else if(start->y()==(start+1)->y()){

            if(start->x()<(start+1)->x()){

                r.push_back(QRectF(QPointF(start->x(),start->y()-0.5), QPointF((start+1)->x(),(start+1)->y()+0.5)));

            }else{

                r.push_back(QRectF(QPointF((start+1)->x(),(start+1)->y()-0.5), QPointF((start)->x(),(start)->y()+0.5)));
            }
        }else{
            if(start->x()>(start+1)->x()){

                if(start->y()>(start+1)->y()){

                    r.push_back(QRectF(QPointF((start+1)->x()-0.5,(start+1)->y()), QPointF((start)->x()+0.5,(start)->y())));

                }else {

                    r.push_back(QRectF(QPointF(start->x()-0.5,start->y()), QPointF((start+1)->x()+0.5,(start+1)->y())));

                }
            }else{
                if(start->y()>(start+1)->y()){

                    r.push_back(QRectF(QPointF(start->x()-0.5,start->y()), QPointF((start+1)->x()+0.5,(start+1)->y())));

                }else{

                    r.push_back(QRectF(QPointF((start+1)->x()-0.5,(start+1)->y()), QPointF((start)->x()+0.5,(start)->y())));
                }
            }
        }
        start++;
    }
    QRectF rr;
    if(lines[0].x()==lines[1].x()){

        if(lines[0].y()<lines[1].y()){

            rr=(QRectF(QPointF(lines[0].x()-1.5,lines[0].y()), QPointF(lines[1].x()+1.5,lines[1].y())));

        }else{

            rr=(QRectF(QPointF(lines[1].x()-1.5,lines[1].y()), QPointF(lines[0].x()+1.5,lines[0].y())));

        }
    }else if(lines[0].y()==lines[1].y()){

        if(lines[0].x()<lines[1].x()){

            rr=(QRectF(QPointF(lines[0].x(),lines[0].y()-1.5), QPointF(lines[1].x(),lines[1].y()+1.5)));
        }else{

            rr=(QRectF(QPointF(lines[1].x(),lines[1].y()-1.5), QPointF(lines[0].x(),lines[0].y()+1.5)));
        }
    }else{
        if(lines[0].x()>lines[1].x()){

            rr=(QRectF(QPointF(lines[0].x()-1.5,lines[0].y()), QPointF(lines[1].x()+1.5,lines[1].y())));

        }else{

            rr=(QRectF(QPointF(lines[1].x()-1.5,lines[1].y()), QPointF(lines[0].x()+1.5,lines[0].y())));

        }
    }
    for(QRectF p:r){
        if(p.intersects(rr))
            return true;
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

QVector<GLfloat> Wall::wall(QPointF p1, QPointF p2){
    GLfloat c=200.0;
    GLfloat p1x = (GLfloat) p1.x()/c;
    GLfloat p2x = (GLfloat) p2.x()/c;
    GLfloat p1y = (GLfloat) p1.y()/c;
    GLfloat p2y = (GLfloat) p2.y()/c;
    QVector<GLfloat> array{
        p2x, _height/2, p2y,
        p2x, 0, p2y,
        p1x, 0, p1y,
        p1x, _height/2, p1y,
        p2x, _height/2, p2y,
        p1x, 0, p1y,
    };

    return array;
}
void Wall::generateWallsForView(QVector<GLfloat> &vertices, QVector<GLfloat> &colors, QColor color){

    auto start= _walls_of_rooms.begin();
    auto end= _walls_of_rooms.end()-1;
    while( start != end){
        QVector<GLfloat> array= wall(*start, *(start+1));

        for(auto a: array)
            vertices.push_back(a);

        for(int i=0; i<6; i++){
            colors.push_back(color.redF());
            colors.push_back(color.greenF());
            colors.push_back(color.blueF());
        }

        start++;

    }
}
QVector<GLfloat> Wall::roof(QPointF p1, QPointF p2){
    QPointF middle = middleOfTheRoom();

    return {
        (GLfloat) middle.x(), (GLfloat) (_height+1)/2, (GLfloat) middle.y(),
        (GLfloat) p2.x(), (GLfloat) _height/2, (GLfloat) p2.y(),
        (GLfloat) p1.x(), (GLfloat) _height/2, (GLfloat) p1.y()
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

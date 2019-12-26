#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent)
   : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);//stavljeno je iz razloga sto nece tastere da registruje dovoljno brzo
    start_exist =false;
    on_mouse = false;
    aviable_here_place_newPoint = true;
    aviable_complete_polygon = false;
    first_line_exist =false;
    polygon_is_complited = false;
    chosen_door=false;
    chosen_window=false;
    input_dialog=new InputDialog(this);
    wall_height=2.0;
    wall_thickness=0.25;
    last_floor=0;

    setCursor(Qt::CrossCursor);
    pen_green.setWidth(3);
    pen_green.setStyle(Qt::DashLine);
    pen_green.setColor(Qt::green);
    pen_red.setWidth(3);
    pen_red.setStyle(Qt::DashLine);
    pen_red.setColor(Qt::red);
    last_line_style.setWidth(3);
    last_line_style.setStyle(Qt::DashDotDotLine);
    last_line_style.setColor(Qt::green);
    last_line_style_fail.setWidth(3);
    last_line_style_fail.setStyle(Qt::DashDotDotLine);
    last_line_style_fail.setColor(Qt::red);
    first_line_style.setWidth(3);
    first_line_style.setStyle(Qt::DashDotDotLine);
    first_line_style.setColor(Qt::black);

    connect(this, SIGNAL(leaveEvent()),this,SLOT(changeOnMouse()), Qt::DirectConnection);
    connect(this,SIGNAL(HoverLeave(QPointF,const QPointF)), this, SLOT(changeOnMouse()),Qt::DirectConnection);

}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //mreza
    QPainter painter(this);
    int w = this->width();
    int h = this->height();
    int xPart = w/50;
    int yPart = h/50;
    painter.setPen(Qt::darkYellow);
    for(int x = 0; x <= w; x+=xPart)
    {
        painter.drawLine(x, 0, x, h);
    }
    for(int y = 0; y <= h; y+=yPart)
    {
        painter.drawLine(0, y, w, y);
    }
    painter.drawLine(w, 0, w, h);
    painter.drawLine(0, h, w, h);

    //ako je pritisnuto dugme za zavrsetak nacrta iscta nam se konacan poligon
    if(polygon_is_complited)
    {
        if(polygonPoints.size()==3 && chosen_door){

            doors_for_rooms.push_back(new Door(QLineF(polygonPoints.at(0),polygonPoints.at(1)), wall_height, wall_thickness));
            chosen_door=false;

        }else if(polygonPoints.size()==3 && chosen_window){

            windows_for_rooms.push_back(new Window(QLineF(polygonPoints.at(0),polygonPoints.at(1)), wall_height, wall_thickness));
            chosen_window=false;

        }
        else
            walls_for_rooms.push_back(new Wall(QPolygonF(polygonPoints), wall_height, wall_thickness));
    }
    //losa implementacija ali za sad ce da koristi
    for(auto i=walls_for_rooms.begin(); i!=walls_for_rooms.end(); i++)
        (*i)->paint(&painter,Q_NULLPTR,Q_NULLPTR);

    for(auto i=windows_for_rooms.begin(); i!=windows_for_rooms.end(); i++)
        (*i)->paint(&painter,Q_NULLPTR,Q_NULLPTR);

    for(auto i=doors_for_rooms.begin(); i!=doors_for_rooms.end(); i++)
        (*i)->paint(&painter,Q_NULLPTR,Q_NULLPTR);

    //laksa navigacija kroz mrezu
    QRectF textRect( 4,  5, 200, 20);

    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(11);
    painter.setFont(font);
    painter.setPen(Qt::black);
    QString message =  "X "+ QString::number(this->my_x) + " | Y " + QString::number(this->my_y);
    painter.drawText(textRect,  message);

    if(!start_exist)
        return;


    if (!first_line_exist)
    {
         QLineF line1;
         line1.setLine(startPoint.x(),startPoint.y(),my_x,my_y);

         painter.setPen(first_line_style);
         painter.drawLine(startPoint.x(),startPoint.y(),my_x,my_y);

         return;
     }

     painter.setPen(Qt::black);
     for(ii=lines.begin(); ii!=lines.end(); ii++)
         painter.drawLine((*ii));

     (aviable_here_place_newPoint) ? painter.setPen(pen_green) : painter.setPen(pen_red);

         if(on_mouse)

     painter.drawLine(point2.x(),point2.y(),my_x,my_y);


         if(polygonPoints.size()>2)
    {
         QLineF last_line(point2,startPoint);
         ii=lines.begin(); aviable_complete_polygon = true;
         while(aviable_complete_polygon && ii!=lines.end())
         {
             aviable_complete_polygon = (!isIntersect((*ii), last_line));
             ii++;
         }




         if(!on_mouse)
         {

              aviable_complete_polygon ? painter.setPen(last_line_style) : painter.setPen(last_line_style_fail);
              painter.drawLine(last_line);

              QPolygonF finalPolygon(polygonPoints);
              QBrush brush(Qt::green,Qt::CrossPattern);
              painter.setBrush(brush);
              if(aviable_complete_polygon)
              {
                  painter.drawPolygon(finalPolygon);
                  emit update_status_finish(QString(tr("moze da se zavrsi")));
               }else
                  emit update_status_finish(QString(tr("ne moze da se zavrsi")));
        }

         emit have_points(polygonPoints.size());
         emit enableCompleteDrawing(aviable_complete_polygon);
    }

     QApplication::processEvents();

}


void DrawingArea::mousePressEvent(QMouseEvent * e)
{
    if(polygon_is_complited)
        return;

    on_mouse = true;

   if( !start_exist){
         startPoint = e->pos();
         start_exist = true;
         polygonPoints.push_back(startPoint);
         point2 = startPoint;
         this ->repaint();
         return;
    }

    if(!first_line_exist)
    {
        point2 = e ->pos();
        QLineF line1(startPoint, point2);
        lines.push_back(line1);
        polygonPoints.push_back(point2);
        first_line_exist = true;
        this ->repaint();
        return;
    }

    if( aviable_here_place_newPoint)
    {

         QLineF line1(point2, e->pos());
         lines.push_back(line1);
         point2 = e ->pos();
         polygonPoints.push_back(point2);
    }
    else
        emit fail_to_add_peak(QString(tr("ne moze ovde da se crta")));

    this ->repaint();


}


void DrawingArea::mouseMoveEvent(QMouseEvent * e)
{
    if(polygon_is_complited)
        return;

     on_mouse=true;

     my_x = e->localPos().x();
     my_y = e->localPos().y();


     if((abs(point2.x()-my_x)>0) && (abs(point2.x()-my_x)>0))
           aviable_here_place_newPoint =true;

      if( first_line_exist )
      {
           QLineF dash_line(point2.x(),point2.y(),my_x,my_y);


           ii = lines.begin();
           while(aviable_here_place_newPoint && (ii != lines.end() ) )
           {
               aviable_here_place_newPoint = (!isIntersect((*ii),dash_line));
               ++ii;
           }
      }
      if(aviable_here_place_newPoint)
          update_status(QString(tr("moze da se stavi tacka")));
      else
          update_status(QString(tr("ne moze da se stavi tacka")));


      this ->repaint();

      QApplication::processEvents();

}


void DrawingArea::enterEvent(QMouseEvent * e)
{
    Q_UNUSED(e);
    this -> on_mouse = true;
}


QSize DrawingArea::sizeHint() const
{
    return QSize(620, 460);
}



bool DrawingArea::isIntersect(QLineF line1, QLineF line2)
{
    double a1,a2,a3,a4; int x11,y11,x12,y12, x21, y21,x22,y22;
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

void DrawingArea::reinitialize(){
    lines.resize(0);
    lines.clear();//nepotrebno
    polygonPoints.resize(0);
    polygonPoints.clear();//nepotrebno
    first_line_exist = false;
    start_exist = false;
    aviable_here_place_newPoint = true;
    first_line_exist =false;
    polygon_is_complited = false;
    on_mouse = false;
    aviable_complete_polygon = false;
    emit have_been_reseting(QString(tr("Drawing new polygon...")));
    this -> repaint();
}
void DrawingArea::complete_drawing(){
    polygon_is_complited = true;
    polygonPoints.push_back(startPoint);

    this -> repaint();
    reinitialize();
}

void DrawingArea::reset_drawing()
{
    reinitialize();
}

void DrawingArea::changeOnMouse()
{
    on_mouse = false;
    repaint();
}
void DrawingArea::reinit_floors(){
    walls_for_rooms.clear();
    windows_for_rooms.clear();
    doors_for_rooms.clear();
}
void DrawingArea::keyPressEvent(QKeyEvent *e){

    if(e->key()==Qt::Key_W){

        chosen_window = true;
        this->repaint();
    }else if(e->key()==Qt::Key_D){

        chosen_door = true;
        this->repaint();
    }else if(e->key()==Qt::Key_C){

        input_dialog->show();
        this->repaint();

    }else if(e->key()==Qt::Key_N){
        floors.push_back(new Floor(walls_for_rooms, windows_for_rooms, doors_for_rooms));
        walls_for_rooms.clear();
        windows_for_rooms.clear();
        doors_for_rooms.clear();
        last_floor++;
        reinitialize();
    }else if(e->key()==Qt::Key_B){
        if(last_floor-1<0)
            return;
        last_floor--;
        reinitialize();
        reinit_floors();
        walls_for_rooms=floors.at(last_floor)->getwalls();
        windows_for_rooms=floors.at(last_floor)->getwindows();
        doors_for_rooms=floors.at(last_floor)->getdoors();
        this->repaint();
    }else if(e->key()==Qt::Key_F){
        if(last_floor+1>floors.size())
            return;
        if(last_floor+1==floors.size()){
            last_floor++;
            reinitialize();
            reinit_floors();
            this->repaint();
            return;
        }
        last_floor++;
        reinitialize();
        reinit_floors();
        walls_for_rooms=floors.at(last_floor)->getwalls();
        windows_for_rooms=floors.at(last_floor)->getwindows();
        doors_for_rooms=floors.at(last_floor)->getdoors();
        this->repaint();
    }else if(e->key()==Qt::Key_S){

        floors.at(last_floor)->setwalls(walls_for_rooms);
        floors.at(last_floor)->setwindows(windows_for_rooms);
        floors.at(last_floor)->setdoors(doors_for_rooms);
        this->repaint();
    }

}

void DrawingArea::changedParams(){
    wall_height=input_dialog->height();
    wall_thickness=input_dialog->thickness();
}

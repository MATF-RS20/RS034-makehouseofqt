#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent)
   : QWidget(parent)
{
    start_exist =false;
    on_mouse = false;
    aviable_here_place_newPoint = true;
    aviable_complete_polygon = false;
    first_line_exist =false;
    polygon_is_complited = false;
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
          QPen pen;
          pen.setColor(QColor(192,192,192));
          pen.setWidthF(5.5);
          QPolygonF finalPolygon(polygonPoints);
          painter.setPen(pen);
          painter.drawPolygon(finalPolygon);
          return;
    }
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
                  emit update_status_finish(QString(tr("polygon can be finished")));
               }else
                  emit update_status_finish(QString(tr("this polygon can't be finished !")));
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
        emit fail_to_add_peak(QString(tr("ololo! not here!")));

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
          update_status(QString(tr("you can tag new peak here")));
      else
          update_status(QString(tr("you can not tag new peak here")));


      this ->repaint();

      QApplication::processEvents();

}


void DrawingArea::enterEvent(QMouseEvent * e)
{
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


void DrawingArea::complete_drawing(){
    polygon_is_complited = true;
    this -> repaint();
}

void DrawingArea::reset_drawing()
{
     lines.resize(0);
     lines.clear();//nepotrebno
     polygonPoints.resize(0);
     polygonPoints.clear();//nepotrebno
     first_line_exist = false;
     start_exist = false;
     start_exist =false;
     aviable_here_place_newPoint = true;
     first_line_exist =false;
     polygon_is_complited = false;
     on_mouse = false;
     aviable_complete_polygon = false;
     emit have_been_reseting(QString(tr("Drawing new polygon...")));
     this -> repaint();
}

void DrawingArea::changeOnMouse()
{
    on_mouse = false;
    repaint();
}


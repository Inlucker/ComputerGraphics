#include "canvas.h"

#include <QMessageBox>
#include <QPainterPath>
#include <QPolygon>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    linePen = QPen(Qt::red);
    cutterPen = QPen(Qt::black);
    rezPen = QPen(Qt::blue);
    setStyleSheet("background-color:white;");
    isDelay = true;

    color_line = QColor(Qt::red);
    color_cutter = QColor(Qt::black);
    color_rez = QColor(Qt::blue);

    edgeFlag = true;

    clean();
}

Canvas::~Canvas()
{
    delete painter;
    delete my_pixmap;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && rect().contains(event->pos()))
    {
        /*double x = prev_x_line;
        double y = prev_y_line;*/

        if (edgeFlag)
        {
            double x = prev_x_line;
            double y = prev_y_line;
            if (event->modifiers() == Qt::ALT && !firstPointLineCheck())
            {
                x = event->x();
                if ((event->x() > prev_x_line && event->y() < prev_y_line) || (event->x() < prev_x_line && event->y() > prev_y_line))
                    y = y - (x - prev_x_line);
                else
                    y = y + (x - prev_x_line);
            }
            else if (event->modifiers() == Qt::CTRL && !firstPointLineCheck())
            {
                x = event->x();
            }
            else if (event->modifiers() == Qt::SHIFT && !firstPointLineCheck())
            {
                y = event->y();
            }
            else
            {
                x = event->x();
                y = event->y();
            }

            addPoint(x, y);
        }
        else
        {
            double x = prev_x_cutter;
            double y = prev_y_cutter;
            if (event->modifiers() == Qt::ALT && !firstPointCutterCheck())
            {
                x = event->x();
                if ((event->x() > prev_x_cutter && event->y() < prev_y_cutter) || (event->x() < prev_x_cutter && event->y() > prev_y_cutter))
                    y = y - (x - prev_x_cutter);
                else
                    y = y + (x - prev_x_cutter);
            }
            else if (event->modifiers() == Qt::CTRL && !firstPointCutterCheck())
            {
                x = event->x();
            }
            else if (event->modifiers() == Qt::SHIFT && !firstPointCutterCheck())
            {
                y = event->y();
            }
            else
            {
                x = event->x();
                y = event->y();
            }
            setCutter(x, y);
        }
    }
    else
    {
        if (event->button() == Qt::RightButton && rect().contains(event->pos()))
        {
            if (edgeFlag)
                setCutter(event->x(), event->y());
            else
                addPoint(event->x(), event->y());
        }
    }
}

void Canvas::setCutterPenColor(QColor color)
{
    color_cutter = color;
    cutterPen.setColor(color);
}

void Canvas::setLinePenColor(QColor color)
{
    color_line = color;
    linePen.setColor(color);
}

void Canvas::setRezColor(QColor color)
{
    color_rez = color;
    rezPen.setColor(color);
}

/*void Canvas::setDelay(bool val)
{
    isDelay = val;
}*/

void Canvas::addPoint(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    //painter->setPen(linePen);
    plot(int_x, int_y);
    if (isFirstPointLine)
    {
        prev_x_line = int_x;
        prev_y_line = int_y;
        isFirstPointLine = false;
    }
    else
    {
        //DrawLineBrezenheimFloat(prev_x_line, prev_y_line, int_x, int_y);
        //lines.push_back(Line(Point(prev_x_line, prev_y_line), Point(int_x, int_y)));
        lines.push_back(Line(prev_x_line, int_x, prev_y_line, int_y));

        isFirstPointLine = true;
    }
    prev_x_line = int_x;
    prev_y_line = int_y;
    setupUpdate();
    //update();
}

void Canvas::lock()
{
    if (!isLocked)
    {
        setCutter(x0, y0);
        //painter->drawLine(prev_x_cutter, prev_y_cutter, round(x0), round(y0));
        isLocked = true;
        isFirstPointCutter = true;
    }
}

void Canvas::setCutter(double x, double y)
{
    if (!cutterSize() || !isLocked)
    {
        int int_x = round(x);
        int int_y = round(y);
        //QPainter painter(my_pixmap);
        //painter->setPen(cutterPen);
        plot(int_x, int_y);
        if (isFirstPointCutter)
        {
            x0 = int_x;
            y0 = int_y;
            isFirstPointCutter = false;
            isLocked = false;
            //cutter.insert(cutter.end(), Point(int_x, int_y));
        }
        else
        {
            //cutter.insert(cutter.end(), Point(int_x, int_y));
            //egles.push_back(Line(prev_x_cutter, prev_y_cutter, int_x, int_y));
            cutter.push_back(Line(prev_x_cutter, int_x, prev_y_cutter, int_y));
            //painter->drawLine(prev_x_cutter, prev_y_cutter, int_x, int_y);
        }
        prev_x_cutter = int_x;
        prev_y_cutter = int_y;
        setupUpdate();
        //update();
    }
}

void Canvas::cutterUpdate()
{
    painter->setPen(cutterPen);
    for (auto cutter_line : cutter)
        DrawLineBrezenheimFloat(cutter_line);
}

void Canvas::setupUpdate()
{
    painter->setPen(linePen);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    for (auto line : lines)
        DrawLineBrezenheimFloat(line);

    cutterUpdate();
    update();
}

int sign(double val)
{
  if (val > 0)
      return 1;
  if (val < 0)
      return -1;
  else
      return 0;
}

bool Canvas::firstPointCheck()
{
    return isFirstPointLine && isFirstPointCutter;
}

bool Canvas::firstPointLineCheck()
{
    return isFirstPointLine;
}

bool Canvas::firstPointCutterCheck()
{
    return isFirstPointCutter;
}

int Canvas::linesSize()
{
    return lines.size();
}

int Canvas::cutterSize()
{
    return cutter.size();
}

bool Canvas::locked()
{
    return isLocked;
}

//not mine
/*long Canvas::is_convex()
{
    Point p1, p2, p3;
    long x1, y1, x2, y2, r, prev = 0, curr;
    for (size_t i = 0; i < cutter.size() - 2; i++)
    {
        p1 = cutter[i];
        p2 = cutter[i + 1];
        p3 = cutter[i + 2];

        x1 = p2.x - p1.x;
        y1 = p2.y - p1.y;

        x2 = p3.x - p2.x;
        y2 = p3.y - p2.y;

        r = x1 * y2 - x2 * y1;
        curr = sign(r);

        if (!prev)
            prev = curr;
        if (curr && curr != prev)
            return 0;
    }

    p1 = cutter[cutter.size() - 2];
    p2 = cutter[cutter.size() - 1];
    p3 = cutter[0];

    x1 = p2.x - p1.x;
    y1 = p2.y - p1.y;

    x2 = p3.x - p2.x;
    y2 = p3.y - p2.y;

    r = x1 * y2 - x2 * y1;
    curr = sign(r);
    if (curr && curr != prev)
        return 0;

    p1 = cutter[cutter.size() - 1];
    p2 = cutter[0];
    p3 = cutter[1];

    x1 = p2.x - p1.x;
    y1 = p2.y - p1.y;

    x2 = p3.x - p2.x;
    y2 = p3.y - p2.y;

    r = x1 * y2 - x2 * y1;
    curr = sign(r);
    if (curr && curr != prev)
        return 0;

    return prev;
}

long scalar_prod(Point v1, Point v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}*/

//Mine
bool CheckSigns(QVector<int> signs, int &obhod)
{
    int count_plus = 0;
    int count_minus = 0;
    for (int i = 0; i < signs.size(); i++)
    {
        if (signs[i] > 0)
        {
            count_plus++;
        }
        if (signs[i] < 0)
        {
            count_minus++;
        }
    }
    if ((count_minus == 0 && count_plus == 0) || (count_minus&&count_plus))
        return false;
    if (count_minus == 0)
        obhod = 1;
    else
        obhod = -1;
    return true;

}

int sign(int n)
{
    if (n > 0)
        return 1;
    else if (n == 0)
        return 0;
    return -1;
}

int VectorMult(Line l1, Line l2)
{
    int Vx1 = l1.x2-l1.x1;
    int Vy1 = l1.y2-l1.y1;
    int Vx2 = l2.x2-l2.x1;
    int Vy2 = l2.y2-l2.y1;
    return Vx1*Vy2-Vx2*Vy1;
}

double scalMult(Point p1, Point p2)
{
    return p1.x()*p2.x() + p2.y()*p1.y();
}

bool Canvas::isConvex(int &obhod)
{
    if (cutter.size() < 2)
        return false;
    QVector<int> signs;
    for (size_t i =0; i < cutter.size() - 1; i++)
    {
        int Mult = VectorMult(cutter[i],cutter[i+1]);
        int msign = sign(Mult);
        signs.append(msign);
    }
    int Mult = VectorMult(cutter[cutter.size() - 1],cutter[0]);
    int msign = sign(Mult);
    signs.append(msign);
    return CheckSigns(signs, obhod);
}

void Canvas::alg(Point p1, Point p2, int obhod)
{
   double tn = 0; //нижняя
   double tv = 1; //верхняя
   double t = 0; //параметр
   Point D; // вектор ориентации
   D.setX(p2.x() - p1.x());
   D.setY(p2.y() - p1.y());
   int size = cutter.size();
   for (int i = 0; i < size; i++)
   {
       Point nVector; //вектор нормали
       if (i  == size - 1)
       {
           if (obhod == -1)
           {
               nVector.setX((cutter[0].y1 - cutter[i].y1));
               nVector.setY(-(cutter[0].x1 - cutter[i].x1));
           }
           else
           {
               nVector.setX(-(cutter[0].y1 - cutter[i].y1));
               nVector.setY((cutter[0].x1 - cutter[i].x1));
           }

       }
       else
       {
           if (obhod == -1)
           {
               nVector.setX((cutter[i + 1].y1 - cutter[i].y1));
               nVector.setY(-(cutter[i + 1].x1 - cutter[i].x1));
           }
           else
           {
               nVector.setX(-(cutter[i + 1].y1 - cutter[i].y1));
               nVector.setY((cutter[i + 1].x1 - cutter[i].x1));
           }
       }
       Point W; // нек коэфицент(для определения знака)
       W.setX(p1.x() - cutter[i].x1);
       W.setY(p1.y() - cutter[i].y1);

       int Wsk = scalMult(W,nVector);
       int Dsk = scalMult(D,nVector);
       if (Dsk == 0) // отрезок вырождается в точку или параллелен
       {
           if (Wsk < 0)
               return;
           else
               continue;

       }
       t = -(double)Wsk/Dsk;
       if (Dsk > 0)
       {
           if (t>1)
               return;
           else
           {
               tn = t>tn?t:tn;
           }
       }
       if (Dsk < 0)
       {
           if (t<0)
               return;
           else
           {
               tv = t<tv?t:tv;
           }
       }
   }
   if (tn <= tv)
   {
       DrawLineBrezenheimFloat(round(p1.x() + (p2.x()-p1.x())*tv),
                               round(p1.y() + (p2.y()-p1.y())*tv),
                               round(p1.x() + (p2.x()-p1.x())*tn),
                               round(p1.y() + (p2.y()-p1.y())*tn));
   }
   return;
}

void Canvas::cut()
{
    int obhod;
    if(!isConvex(obhod))
    {
        QMessageBox::information(this, "Error", "Невыпуклый многоугольник.");
        return;
    }
    QPainterPath path /*= QPainterPath(QPointF(cutter[0].x1, cutter[0].y1))*/;
    QPolygon polygon;
    for (auto &line : cutter)
    {
        polygon.append(QPoint(line.x1, line.y1));
    }
    path.addPolygon(polygon);
    painter->fillPath(path, QBrush(Qt::white));
    cutterUpdate();

    painter->setPen(rezPen);
    for (int i = 0 ; i < lines.size(); i++)
    {
        Point p1(lines[i].x1,lines[i].y1);
        Point p2(lines[i].x2,lines[i].y2);
        alg(p2, p1, obhod);
        update();
    }

    //not Mine
    /*long conv = is_convex();
    if (conv)
    {
        for (auto &line : lines)
        {
            long m = cutter.size()-1; //fig.edges_count();
            Point D = Point(line.p2.x - line.p1.x, line.p2.y - line.p1.y);
            double t_low = 0, t_high = 1;
            for (long i = 0; i < m; i++)
            {
                Point f = cutter.at(i); //fig.get_edge(i).get_p1();
                Point p2 = cutter.at(i+1); //fig.get_edge(i).get_p2();
                Point n_in = Point(conv * (p2.y - f.y), -conv * (p2.x - f.x));
                Point W = Point(line.p1.x - f.x, line.p1.y - f.y); //src.get_p1() - f;
                double Wsc = scalar_prod(W, n_in);
                double Dsc = scalar_prod(D, n_in);

                if (Dsc)
                {
                    double t = - Wsc / Dsc;
                    if (Dsc > 0)
                    {
                        if (t > 1)
                            continue;
                            //return false;
                        else if (t > t_low)
                        {
                            t_low = t;
                        }
                    }
                    else
                    {
                        if (t < 0)
                            continue;
                            //return false;
                        else if (t < t_high)
                        {
                            t_high = t;
                        }
                    }
                }
                else if (Wsc < 0)
                    continue;
                    //return false;
            }
            if (t_low > t_high)
                continue;
                //return false;
            cout << "ok";
            Point res1 = Point(line.p1.x + (line.p2.x - line.p1.x) * t_low, line.p1.y + (line.p2.y - line.p1.y) * t_low); //(line.p1 + (line.p2 - line.p1) * t_low);
            Point res2 = Point(line.p1.x + (line.p2.x - line.p1.x) * t_high, line.p1.y + (line.p2.y - line.p1.y) * t_high); //(line.p1 + (line.p2 - line.p1) * t_high);
            painter->setPen(rezPen);
            DrawLineBrezenheimFloat(Line(res1, res2));
            //return true;
        }
        update();
    }
    else
    {
        cout << "not convex" << endl;
    }*/
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter pixmap_painter(this);

    pixmap_painter.drawPixmap(0, 0, *my_pixmap);
}

void Canvas::plot(int x, int y)
{
    //p->setPen(semiPen);
    painter->drawPoint(x, y);
}

void Canvas::clean()
{
    x0 = 0, y0 = 0;
    xz = 0, yz = 0;
    isFirstPointLine = true;
    isFirstPointCutter = true;
    isLocked = false;
    isZatravka = false;

    if (painter)
        delete painter;

    if (my_pixmap)
        delete my_pixmap;
    my_pixmap = new QPixmap(2000, 2000);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    //my_pixmap->fill(color_rez);

    painter = new QPainter(my_pixmap);
    painter->setPen(linePen);

    lines.clear();
    cutter.clear();

    update();
}


void Canvas::DrawLineBrezenheimFloat(Line l)
{
    //DrawLineBrezenheimFloat(l.p1.x, l.p1.y, l.p2.x, l.p2.y);
    DrawLineBrezenheimFloat(l.x1, l.y1, l.x2, l.y2);
}

void Canvas::DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end)
{
    int X = X_start, Y = Y_start;
    int dX = X_end - X_start, dY = Y_end - Y_start;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        //dX, dY = dY, dX;
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1; // шагаем по y
    }
    else
        steep = 0;

    double tg = double(dY) / double(dX) ; // tангенс угла наклона
    double er = tg - 0.5; // начальное значение ошибки

    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);

    painter->drawPoint(X, Y);
    while (X != X_end || Y != Y_end)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 1; // отличие от целого
            //stairs.append(st)
            //st = 0
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            //st += 1
            er += tg; // отличие от целого
        }
        painter->drawPoint(X, Y);
    }
}

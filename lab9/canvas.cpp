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

double getAngle(Line l1, Line l2)
{
    //Point v1 = Point(l1.x2 - l1.x1, l1.y2 - l1.y1);
    //Point v2 = Point(l2.x2 - l2.x1, l2.y2 - l2.y1);
    double x1 = l1.x2 - l1.x1;
    double y1 = l1.y2 - l1.y1;
    double x2 = l2.x2 - l2.x1;
    double y2 = l2.y2 - l2.y1;


    double t = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));

    if (t<-1)
        t = -1;
    else if(t> 1)
        t = 1;

    return acos(t)*180/M_PI;
}

void Canvas::addPoint(double x, double y)
{
    if (!linesSize() || !isLinesLocked)
    {
        int int_x = round(x);
        int int_y = round(y);
        plot(int_x, int_y);
        if (isFirstPointLine)
        {
            x0_l = int_x;
            y0_l = int_y;
            isFirstPointLine = false;
            isLinesLocked = false;
        }
        else
        {
            Line newLine(prev_x_line, prev_y_line, int_x, int_y);
            if (lines.size() >= 1)
            {
                linesAngleSum += getAngle(lines[lines.size()-1], newLine);
            }
            lines.push_back(newLine);
        }
        prev_x_line = int_x;
        prev_y_line = int_y;
        setupUpdate();
    }
}

void Canvas::lockLines()
{
    if (!isLinesLocked)
    {
        addPoint(x0_l, y0_l);
        if (lines.size() >= 1)
        {
            linesAngleSum += getAngle(lines[lines.size()-1], lines[0]);
        }
        cout << "linesAngleSum: " << linesAngleSum << endl;
        isLinesLocked = true;
        isFirstPointLine = true;
    }
}

void Canvas::lockCutter()
{
    if (!isCutterLocked)
    {
        setCutter(x0, y0);
        if (cutter.size() >= 1)
        {
            cutterAngleSum += getAngle(cutter[cutter.size()-1], cutter[0]);
        }
        cout << "cutterAngleSum: " << cutterAngleSum << endl;
        isCutterLocked = true;
        isFirstPointCutter = true;
    }
}

void Canvas::setCutter(double x, double y)
{
    if (!cutterSize() || !isCutterLocked)
    {
        int int_x = round(x);
        int int_y = round(y);
        plot(int_x, int_y);
        if (isFirstPointCutter)
        {
            x0 = int_x;
            y0 = int_y;
            isFirstPointCutter = false;
            isCutterLocked = false;
        }
        else
        {
            Line newLine(prev_x_cutter, prev_y_cutter, int_x, int_y);
            if (cutter.size() >= 1)
            {
                cutterAngleSum += getAngle(cutter[cutter.size()-1], newLine);
            }
            cutter.push_back(newLine);
        }
        prev_x_cutter = int_x;
        prev_y_cutter = int_y;
        setupUpdate();
        //update();
    }
}

void Canvas::linesUpdate()
{
    painter->setPen(linePen);
    for (auto cutter_line : lines)
        DrawLineBrezenheimFloat(cutter_line);
}

void Canvas::cutterUpdate()
{
    painter->setPen(cutterPen);
    for (auto cutter_line : cutter)
        DrawLineBrezenheimFloat(cutter_line);
}

void Canvas::setupUpdate()
{
    my_pixmap->fill(QColor(0, 0, 0, 0));
    linesUpdate();

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

bool Canvas::lockedLines()
{
    return isLinesLocked;
}

bool Canvas::lockedCutter()
{
    return isCutterLocked;
}

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
    return p1.X*p2.X + p2.Y*p1.Y;
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

int myIsVisible(Point p, Point c1, Point c2)
{
    int w1 = (p.X - c1.X) * (c2.Y - c1.Y);
    int w2 = (p.Y - c1.Y) * (c2.X - c1.X);
    int w3 = w1-w2;
    return sign(w3);
}

bool isCrossing(Point p1, Point p2, Point c1, Point c2)
{
    int vis1 = myIsVisible(p1, c1, c2);
    int vis2 = myIsVisible(p2, c1, c2);
    if ((vis1 > 0 && vis2 < 0) ||(vis1 < 0 && vis2 > 0))
        return true;
    return false;
}

Point find_cross_point(Point p1, Point p2, Point c1, Point c2)
{
    double a = p2.X - p1.X;
    double b = c1.X - c2.X;
    double c = c1.X - p1.X;

    double d = p2.Y - p1.Y;
    double e = c1.Y - c2.Y;
    double f = c1.Y - p1.Y;

    double det = a*e - b*d;
    double t = (c*e - b * f) / det;
    Point I;
    I.X = (p1.X + (p2.X - p1.X) * t);
    I.Y = (p1.Y + (p2.Y - p1.Y) * t);
    return I;
}

void Canvas::cut()
{
    int obhod1;
    if (!isConvex(obhod1))
    {
        QMessageBox::information(this, "Error", "Невыпуклый отсекатель.");
        return;
    }

    vector<Point> c;
    for(int i = 0; i < cutter.size(); i++)
    {
        Point p1(cutter[i].x1,cutter[i].y1);
        c.push_back(p1);
    }
    Point p1(cutter[0].x1,cutter[0].y1);
    c.push_back(p1);
    size_t Nc = c.size()-1;

    vector<Point> p;
    for(int i = 0; i < lines.size(); i++)
    {
        Point p1(lines[i].x1,lines[i].y1);
        p.push_back(p1);
    }
   // point p1(lines[0].x1, lines[0].y1);
    //p.push_back(p1);
    size_t Np = p.size(), Nq;
    Point F,S,I;
    vector<Point> Q;

    for (int i = 0; i < Nc; i++)
    {
        Nq = 0;
        for (int j = 0; j < Np; j++)
        {
            if (j == 0)
            {
                F = p[j];
            }
            else
            {
                if (isCrossing(S,p[j],c[i],c[i+1]))
                {
                    Nq++;
                    I = find_cross_point(S,p[j],c[i],c[i+1]);
                    Q.push_back(I);
                }
            }
            S = p[j];
            int vis = myIsVisible(S, c[i], c[i+1]);
            if ((vis  >= 0 && obhod1 == -1) || (vis <= 0 && obhod1 == 1))
            {
                Q.push_back(S);
                Nq++;
            }
        }
        if (Nq != 0)
        {
            if (isCrossing(S, F, c[i], c[i+1]))
            {
                Nq++;
                I = find_cross_point(S,F,c[i],c[i+1]);
                Q.push_back(I);
            }
        }
        Np = Nq;
        p = Q;
        Q.clear();
    }


    if (Np == 0)
    {
        QMessageBox::information(this, "Error", "Полностью невидимый многоугольник.");
        return;
    }
    painter->setPen(rezPen);
    painter->setPen(QPen(color_rez,3));
    for (size_t i = 0; i < p.size()-1; i++)
    {
         DrawLineBrezenheimFloat(p[i].X, p[i].Y, p[i+1].X, p[i+1].Y);
    }
    DrawLineBrezenheimFloat(p[p.size()-1].X, p[p.size()-1].Y, p[0].X, p[0].Y);
    update();

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
    linesAngleSum = 0;
    cutterAngleSum = 0;
    x0_l = 0, y0_l = 0;
    x0 = 0, y0 = 0;
    isFirstPointLine = true;
    isFirstPointCutter = true;
    isLinesLocked = false;
    isCutterLocked = false;

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

void Canvas::resetLines()
{
    linesAngleSum = 0;
    x0_l = 0, y0_l = 0;
    isFirstPointLine = true;
    isLinesLocked = false;
    lines.clear();
    setupUpdate();
}

void Canvas::resetCutter()
{
    cutterAngleSum = 0;
    x0 = 0, y0 = 0;
    isFirstPointCutter = true;
    isCutterLocked = false;
    cutter.clear();
    setupUpdate();
}

#define EPS 1e-5

bool Canvas::isLinesPolygon()
{
    return ((linesAngleSum - 360) < EPS);
}

bool Canvas::isCutterPolygon()
{
    return ((cutterAngleSum - 360) < EPS);
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

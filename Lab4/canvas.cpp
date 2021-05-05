#include "canvas.h"
#include <math.h>
#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    //isClean = false;
    method = CANON;
    pen = QPen(Qt::black);
    setStyleSheet("background-color:white;");
    clean();
}

Canvas::~Canvas()
{

}

void Canvas::setPenColor(QColor color)
{
    pen.setColor(color);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, my_pixmap);
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

double max(double val1, double val2)
{
  if (val1 >= val2)
      return val1;
  if (val1 < val2)
      return -val2;
}

/*void Canvas::plot(QPainter *p, int x, int y, int c)
{
    if (pen.color() == Qt::white)
        c = 255;
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue(), int(double(c))));
    p->setPen(pen);
    p->drawPoint(x, y);
}*/

void Canvas::plot(QPainter *p, int x, int y)
{
    p->setPen(pen);
    p->drawPoint(x, y);
}

/*void Canvas::DrawPoint(QPainter *p, bool steep, int x, int y)
{
    if (!steep)
        plot(p, x, y);
    else
        plot(p, y, x);
}*/

void Canvas::DrawCircleCanon(int X_c, int Y_c, int R)
{
    //(x - X_c)^2 + (y - Y_c)^2 = r^2;
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    QPolygon circle;

    for (int y = Y_c - R; y <= Y_c + R; y++)
    {
        circle.append(QPoint(sqrt(pow(R, 2) - pow(y-Y_c, 2)) + X_c, y));
        //plot(&painter, sqrt(pow(R, 2) - pow(y-Y_c, 2)) + X_c, y);
        //plot(&painter, -sqrt(pow(R, 2) - pow(y-Y_c, 2)) + X_c, y);
    }


    for (int y = Y_c + R; y >= Y_c - R; y--)
        circle.append(QPoint(-sqrt(pow(R, 2) - pow(y-Y_c, 2)) + X_c, y));

    for (int x = X_c - R; x <= X_c + R; x++)
    {
        //plot(&painter, x, sqrt(pow(R, 2) - pow(x-X_c, 2)) + Y_c);
        //plot(&painter, x, -sqrt(pow(R, 2) - pow(x-X_c, 2)) + Y_c);
    }

    painter.drawPolygon(circle);
}

void Canvas::DrawEllipseCanon(int X_c, int Y_c, int A, int B)
{
    //(x - X_c)^2/a^2 + (y - Y_c)^2/b^2 = 1;
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    QPolygon ellipse;

    for (int y = Y_c - B; y <= Y_c + B; y++)
        ellipse.append(QPoint(sqrt((1 - pow(y-Y_c, 2)/pow(B, 2)) * pow(A, 2)) + X_c, y));

    for (int y = Y_c + B; y >= Y_c - B; y--)
        ellipse.append(QPoint(-sqrt((1 - pow(y-Y_c, 2)/pow(B, 2)) * pow(A, 2)) + X_c, y));

    painter.drawPolygon(ellipse);
}

void Canvas::DrawCircleParam(int X_c, int Y_c, int R)
{
    //x = X_c + R*cos(t)
    //y = Y_c + R*sin(t)
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    QPolygon circle;

    double t = 0;
    double step = (M_PI * 2) / (R * M_PI * 2);
    //step = 1 / (R * 1);
    while (t <= M_PI * 2)
    {
        //plot(&painter, X_c + R*cos(t), Y_c + R*sin(t));
        circle.append(QPoint(X_c + R*cos(t), Y_c + R*sin(t)));
        t += step;
    }

    painter.drawPolygon(circle);
}

void Canvas::DrawEllipseParam(int X_c, int Y_c, int A, int B)
{
    //x = X_c + A*cos(t)
    //y = Y_c + B*sin(t)
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    QPolygon circle;

    double t = 0;
    double step = (M_PI * 2) / ((A*B/2) * M_PI);
    //step = 1 / (R * 1);
    while (t <= M_PI * 2)
    {
        //plot(&painter, X_c + R*cos(t), Y_c + R*sin(t));
        circle.append(QPoint(X_c + A*cos(t), Y_c + B*sin(t)));
        t += step;
    }

    painter.drawPolygon(circle);
}

void Canvas::DrawCircleBrezenham(int X_c, int Y_c, int R)
{

}

void Canvas::DrawEllipseBrezenham(int X_c, int Y_c, int A, int B)
{

}

void Canvas::DrawCircleMidpoint(int X_c, int Y_c, int R)
{

}

void Canvas::DrawEllipseMidpoint(int X_c, int Y_c, int A, int B)
{

}

void Canvas::DrawCircleQt(int X_c, int Y_c, int R)
{
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    painter.drawEllipse(QPointF(X_c, Y_c), R, R);
}

void Canvas::DrawEllipseQt(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    painter.drawEllipse(QPointF(X_c, Y_c), A, B);
}

void Canvas::drawCircle()
{
    switch (method)
    {
        case CANON:
        {
            DrawCircleCanon(X_center, Y_center, Radius);
            break;
        }
        case PARAM:
        {
            DrawCircleParam(X_center, Y_center, Radius);
            break;
        }
        case BREZENHAM:
        {
            DrawCircleBrezenham(X_center, Y_center, Radius);
            break;
        }
        case MIDPOINT:
        {
            DrawCircleMidpoint(X_center, Y_center, Radius);
            break;
        }
        case STANDART:
        {
            DrawCircleQt(X_center, Y_center, Radius);
            break;
        }
        default:
        //???
        break;
    }
}

void Canvas::drawEllipse()
{
    switch (method)
    {
        case CANON:
        {
            DrawEllipseCanon(X_center, Y_center, a, b);
            break;
        }
        case PARAM:
        {
            DrawEllipseParam(X_center, Y_center, a, b);
            break;
        }
        case BREZENHAM:
        {
            DrawEllipseBrezenham(X_center, Y_center, a, b);
            break;
        }
        case MIDPOINT:
        {
            DrawEllipseMidpoint(X_center, Y_center, a, b);
            break;
        }
        case STANDART:
        {
            DrawEllipseQt(X_center, Y_center, a, b);
            break;
        }
        default:
        //???
        break;
    }
}

void Canvas::drawCircleSpectre()
{
    int R = RadiusStart;
    int i = 0;
    do
    {
        switch (method)
        {
            case CANON:
            {
                DrawCircleCanon(X_center, Y_center, R);
                break;
            }
            case PARAM:
            {
                DrawCircleParam(X_center, Y_center, R);
                break;
            }
            case BREZENHAM:
            {
                DrawCircleBrezenham(X_center, Y_center, R);
                break;
            }
            case MIDPOINT:
            {
                DrawCircleMidpoint(X_center, Y_center, R);
                break;
            }
            case STANDART:
            {
                DrawCircleQt(X_center, Y_center, R);
                break;
            }
            default:
            //???
            break;
        }
        R += (RadiusEnd - RadiusStart) / (FiguresNumber-1);
        i++;
    } while(i < FiguresNumber);
}

void Canvas::drawEllipseSpectre()
{
    int A = a_start;
    int B = b_start;
    int i = 0;
    do
    {
        switch (method)
        {
            case CANON:
            {
                DrawEllipseCanon(X_center, Y_center, A, B);
                break;
            }
            case PARAM:
            {
                DrawEllipseParam(X_center, Y_center, A, B);
                break;
            }
            case BREZENHAM:
            {
                DrawEllipseBrezenham(X_center, Y_center, A, B);
                break;
            }
            case MIDPOINT:
            {
                DrawEllipseMidpoint(X_center, Y_center, A, B);
                break;
            }
            case STANDART:
            {
                DrawEllipseQt(X_center, Y_center, A, B);
                break;
            }
            default:
            //???
            break;
        }
        A += stepA;
        B += stepB;
        i++;
    } while(i < FiguresNumber);
}

void Canvas::clean()
{
    my_pixmap = QPixmap(2000, 2000);
    my_pixmap.fill(QColor(0,0,0,0));
    update();
}


/*
#include <chrono>

using namespace std;

#define ITERATIONS 1000

double Canvas::getTime(float length, Algoritm alg)
{
    //srand(time(0));
    int X_start = 10000, X_end = 10000 + length, Y_start = 10000, Y_end = 10000;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    //std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    switch (alg)
    {
        case DIG_DIF_ANALIZ:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineDGA(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case BREZENHAM_FLOAT:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineBrezenheimFloat(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case BREZENHAM_INT:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineBrezenheimInt(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case BREZENHAM_STEP_REM:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineBrezenheimSmooth(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case VU:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineVu(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case STANDART:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawLineQt(X_start, X_end, Y_start, Y_end);
            end = chrono::high_resolution_clock::now();
            break;
        }
        default:
        //???
        break;
    }
    chrono::duration<double> dur = end - start;
    //cout << "here1" << endl;
    //cout << end << " " << start << " " << dur.count() << endl;
    //cout << "here2" << endl;
    //clean();
    return dur.count()/ITERATIONS;
}*/

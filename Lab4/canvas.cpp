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

    /*for (int x = X_c - R; x <= X_c + R; x++)
    {
        //plot(&painter, x, sqrt(pow(R, 2) - pow(x-X_c, 2)) + Y_c);
        //plot(&painter, x, -sqrt(pow(R, 2) - pow(x-X_c, 2)) + Y_c);
    }*/

    painter.drawPolygon(circle);
}

void Canvas::DrawEllipseCanon(int X_c, int Y_c, int A, int B)
{
    //(x - X_c)^2 + (y - Y_c)^2 = r^2;
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
    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);
    switch (method)
    {
        case CANON:
        {
            DrawCircleCanon(X_center, Y_center, Radius);
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
    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);
    switch (method)
    {
        case CANON:
        {
            DrawEllipseCanon(X_center, Y_center, a, b);
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

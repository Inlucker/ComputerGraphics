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
  else
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

void Canvas::plot4(QPainter *p, int X_c, int Y_c, int x, int y)
{
    p->setPen(pen);
    p->drawPoint(X_c + x, Y_c + y);
    p->drawPoint(X_c + x, Y_c - y);
    p->drawPoint(X_c - x, Y_c + y);
    p->drawPoint(X_c - x, Y_c - y);
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
    /*
    1. Ввод R, Xc, Yc.
    2. X = 0, Y = R, Δ = 2(1-R).
    3. Высвечивание текущего пиксела (X,Y).
    4. Анализ D:
       4.1 Если Δ < 0, go to 5.
       4.2 если Δ = 0, go to 8.
       4.3 если Δ > 0, go to 6.
    5. δ1 = 2Δ + 2Y - 1 и анализ полученного значения:
       5.1 если δ1 =< 0, go to 7.
       5.2 иначе, go to 8.
    6. Вычисление параметра δ2 = 2Δ - 2X - 1 и анализ полученного значения:
       6.1 если δ2 =< 0, go to 8
       6.2 иначе, go to 9.
    7. Горизонтальный шаг: X = X + 1; Δ = Δ + 2X + 1. go to 3.
    8. Диагональный шаг: X = X + 1; Y = Y - 1; Δ = Δ + 2(X - Y + 1). go to 3.
    9. Вертикальный шаг: Y = Y - 1; Δ = Δ - 2Y + 1. go to 3.
    10. Конец.
    */
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int x = 0;
    int y = R;
    int er = 2*(1-R);
    int y_end = 0;
    //plotEllipse(&painter, X_c, Y_c, x, y);
    while(y >= y_end)
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (er < 0)
        {
            int d1 = 2*er + 2*y - 1;
            if (d1 < 0)
            {
                // horizontal
                x++;
                er += 2*x + 1;
            }
            else
            {
                // diagonal
                x++;
                y--;
                er += 2*(x - y + 1);
            }
        }
        else if (er == 0)
        {
            // diagonal
            x++;
            y--;
            er += 2*(x - y + 1);
        }
        else
        {
            int d2 = 2*er - 2*x - 1;
            if (d2 < 0)
            {
                // diagonal
                x++;
                y--;
                er += 2*(x - y + 1);
            }
            else
            {
                // vertical
                y--;
                er += 1 - 2*y;
            }
        }
    }

}

void Canvas::DrawEllipseBrezenham(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int x = 0; // Компонента x
    int y = B; // Компонента y
    int a_sqr = A * A; // a^2, a - большая полуось
    int b_sqr = B * B; // b^2, b - малая полуось
    int delta = 4 * b_sqr * ((x + 1) * (x + 1)) + a_sqr * ((2 * y - 1) * (2 * y - 1)) - 4 * a_sqr * b_sqr; // Функция координат точки (x+1, y-1/2)
    while (a_sqr * (2 * y - 1) > 2 * b_sqr * (x + 1)) // Первая часть дуги
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (delta < 0) // Переход по горизонтали
        {
            x++;
            delta += 4 * b_sqr * (2 * x + 3);
        }
        else // Переход по диагонали
        {
            x++;
            delta = delta - 8 * a_sqr * (y - 1) + 4 * b_sqr * (2 * x + 3);
            y--;
        }
    }
    delta = b_sqr * ((2 * x + 1) * (2 * x + 1)) + 4 * a_sqr * ((y + 1) * (y + 1)) - 4 * a_sqr * b_sqr; // Функция координат точки (x+1/2, y-1)
    while (y + 1 != 0) // Вторая часть дуги, если не выполняется условие первого цикла, значит выполняется a^2(2y - 1) <= 2b^2(x + 1)
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (delta < 0) // Переход по вертикали
        {
            y--;
            delta += 4 * a_sqr * (2 * y + 3);
        }
        else // Переход по диагонали
        {
            y--;
            delta = delta - 8 * b_sqr * (x + 1) + 4 * a_sqr * (2 * y + 3);
            x++;
        }
    }
}

void Canvas::DrawCircleMidpoint(int X_c, int Y_c, int R)
{
    DrawEllipseMidpoint(X_c, Y_c, R, R);
}

void Canvas::DrawEllipseMidpoint(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    /*
    Вход: a, b, xc, yc

    b2 = b * b
    bd = 2 * b2
    a2 = a * a
    ad = 2 * a2

    x = 0, y = b, f = b2 - a2 * b + 0,25 * a2

    while b2 * x > a2 * y do
        if f > 0 then
            x = x + 1
            y = y - 1
            f = f + bd * x + b2 - ad * y
        else
            x = x + 1
            f = f + bd * x + b2

    f = f + 3 / 4 * (a2 + b2) - (a2 * y + b2 * x)

    while y >= 0 do
        if f > 0 then
            y = y - 1
            x = x + 1
            f = f + ad * y + a2 - bd * x
        else
            y = y - 1
            f = f + ad * y + a2
    */

    /*int b2 = B*B;
    int bd = 2 * b2;
    int a2 = A * A;
    int ad = 2 * a2;

    double x = 0, y = b, f = b2 - a2 * b + 0.25 * a2;

    while (b2 * x > a2 * y)
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (f > 0)
        {
            x++;
            y--;
            f += bd * x + b2 - ad * y;
        }
        else
        {
            x++;
            f += bd * x + b2;
        }
        plot4(&painter, X_c, Y_c, x, y);
    }

    f = f + 3 / 4 * (a2 + b2) - (a2 * y + b2 * x);

    while (b2 * x > a2 * y)
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (f > 0)
        {
            y--;
            x++;
            f += ad * y + a2 - bd * x;
        }
        else
        {
            y--;
            f += ad * y + a2;
        }
    }*/

    int dx, dy, d1, d2, x, y;
    int a_sqr = A * A; // a^2, a - большая полуось
    int b_sqr = B * B; // b^2, b - малая полуось
    x = 0;
    y = B;
    // Начальный параметр решения области 1
    d1 = (b_sqr) - (a_sqr * B) + (0.25 * a_sqr);
    dx = 2 * b_sqr * x;
    dy = 2 * a_sqr * y;

    // Для региона 1
    while (dx < dy)
    {
        // Печать точек на основе 4-сторонней симметрии
        plot4(&painter, X_c, Y_c, x, y);
        // Проверка и обновление значения
        // параметр решения на основе алгоритма
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * b_sqr);
            d1 = d1 + dx + (b_sqr);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * b_sqr);
            dy = dy - (2 * a_sqr);
            d1 = d1 + dx - dy + (b_sqr);
        }
    }

    // Параметр решения области 2
    d2 = ((b_sqr) * ((x + 0.5) * (x + 0.5))) +
         ((a_sqr) * ((y - 1) * (y - 1))) -
          (a_sqr * b_sqr);

    // Построение точек области 2
    while (y >= 0)
    {
        // Печать точек на основе 4-сторонней симметрии
        plot4(&painter, X_c, Y_c, x, y);

        // Проверка и обновление параметра
        // значение на основе алгоритма
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * a_sqr);
            d2 = d2 + (a_sqr) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * b_sqr);
            dy = dy - (2 * a_sqr);
            d2 = d2 + dx - dy + (a_sqr);
        }
    }
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
            //DrawCircleBrezenham(X_center, Y_center, Radius);
            DrawEllipseBrezenham(X_center, Y_center, Radius, Radius);
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

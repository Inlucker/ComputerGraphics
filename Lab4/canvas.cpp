#include "canvas.h"
#include <math.h>
#include <iostream>

using namespace std;

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

/*double max(double val1, double val2)
{
  if (val1 >= val2)
      return val1;
  else
      return -val2;
}*/

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
    //x^2 + y^2 = r^2;
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int x = 0;
    int y = 0;

    while (x <= R/sqrt(2))
    {
        y = round(sqrt(R*R-x*x));
        plot4(&painter, X_c, Y_c, x, y);
        plot4(&painter, X_c, Y_c, y, x);
        x++;
    }

    /*y = 0;
    while (y <= R)
    {
        y++;
        x = round(sqrt(R*R-y*y));
        plot4(&painter, X_c, Y_c, x, y);
    }*/
}

void Canvas::DrawEllipseCanon(int X_c, int Y_c, int A, int B)
{
    //(x - X_c)^2/a^2 + (y - Y_c)^2/b^2 = 1;
    //x^2/a^2 + y^2/b^2 = 1;
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    double x = 0;
    double y = 0;

    while (x <= A)
    {
        y = round(B*sqrt(1-x*x/A/A));
        plot4(&painter, X_c, Y_c, round(x), y);
        x++;
    }

    y = 0;
    while (y <= B)
    {
        x = round(A*sqrt(1-y*y/B/B));
        plot4(&painter, X_c, Y_c, x, y);
        y++;
    }
}

void Canvas::DrawCircleParam(int X_c, int Y_c, int R)
{
    //x = X_c + R*cos(t)
    //y = Y_c + R*sin(t)
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int x = 0;
    int y = R;
    plot4(&painter, X_c, Y_c, x, y);
    double step = 1.0 / R;
    for (double t = 0; t <= M_PI/2; t += step)
    {
        x = round(R*cos(t));
        y = round(R*sin(t));
        plot4(&painter, X_c, Y_c, x, y);
        //plot4(&painter, X_c, Y_c, y, x);
    }
}

void Canvas::DrawEllipseParam(int X_c, int Y_c, int A, int B)
{
    //x = X_c + A*cos(t)
    //y = Y_c + B*sin(t)
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    double x = 0;
    double y = B;
    plot4(&painter, X_c, Y_c, x, y);
    double step = 1.0 / (A>B? A:B);
    //double step = 1.0 / ((A+B)/2);
    for (double t = 0; t <= M_PI/2; t += step)
    {
        x = round(A*cos(t));
        y = round(B*sin(t));
        plot4(&painter, X_c, Y_c, x, y);
    }
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
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    /*int x = 0;
    int y = R;
    int er = 2*(1-R);
    int y_end = R/sqrt(2);//= 0;
    //plotEllipse(&painter, X_c, Y_c, x, y);
    while(y >= y_end)
    {
        plot4(&painter, X_c, Y_c, x, y);
        plot4(&painter, X_c, Y_c, y, x);
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
    }*/

    int x = 0;
    int y = int(R);
    int di = int(2*(1-R));
    //int y_end = R/sqrt(2);

    while (x <= R && y >= 0)
    //while(y >= y_end)
    {
        plot4(&painter, X_c, Y_c, x, y);
        //plot4(&painter, X_c, Y_c, y, x);
        if (di < 0)
        {
            //vnutri
            //диагональный или горизонтальный
            int d1 = 2*di + 2*y -1;
            if (d1 < 0)
            {
                // горизонт
                x++;
                di = di+2*x +1;
            }
            else
            {
                //диагональ
                x++;
                y--;
                di += 2*(x-y+1);
            }
        }
        else if (di == 0)
        {
            //na
            //выбираем диагональный
            x++;
            y--;
            di += 2*(x-y+1);
        }
        else
        {
            //snaruzi
            //диагональный или вертикальный
            int d2 = 2*di-2*x-1;
            if (d2 < 0)
            {
                // диагональный
                x++;
                y--;
                di += 2*(x-y+1);

            }
            else
            {
                // вертикальный
                y--;
                di = di - 2*y+1;
            }
        }
    }
}

void Canvas::DrawEllipseBrezenham(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    /*int x = 0; // Компонента x
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
    }*/

    int x = 0;
    int y = int(B);
    int end_y = 0;
    int a_sqr = A*A;
    int b_sqr = B*B;
    int di = a_sqr + b_sqr - 2 * a_sqr * y;

    while (y >= end_y)
    {
        plot4(&painter, X_c, Y_c, x, y);
        if (di < 0)
        {
            //vnutri
            //диагональный или горизонтальный
            int d1 = 2 * di + 2 * a_sqr * y - 1;
            if (d1 < 0)
            {
                // горизонт
                x++;
                di = di + 2 * b_sqr * x + b_sqr;
            }
            else
            {
                //диагональ
                x++;
                y--;
                di +=  2 * b_sqr * x + b_sqr + a_sqr - 2 * a_sqr * y;
            }
        }
        else if (di == 0)
        {
            //na
            //выбираем диагональный
            x++;
            y--;
            di +=  2 * b_sqr * x + b_sqr + a_sqr - 2 * a_sqr * y;
        }
        else
        {
            //snaruzi
            //диагональный или вертикальный
            int d2 = 2*di-2*b_sqr*x-1;
            if (d2 <= 0)
            {
                // диагональный
                x++;
                y--;
                di +=  2 * b_sqr * x + b_sqr + a_sqr - 2 * a_sqr * y;

            }
            else
            {
                // вертикальный
                y--;
                di = di - 2 * a_sqr * y + a_sqr;
            }
        }
    }
}

void Canvas::DrawCircleMidpoint(int X_c, int Y_c, int R)
{
    //DrawEllipseMidpoint(X_c, Y_c, R, R);

    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int x = 0;
    int y = R;

    int d = 1 - R;
    plot4(&painter, X_c, Y_c, x, y);
    plot4(&painter, X_c, Y_c, y, x);

    while (x < y)
    {
        x++;
        if (d < 0)
            d += 2*x + 1;
        else
        {
            y--;
            d += 2*(x - y) + 1;
        }
        plot4(&painter, X_c, Y_c, x, y);
        plot4(&painter, X_c, Y_c, y, x);
    }

    /*int r_sqr = R*R;
    int x = 0;
    int y = R;
    int rd2 = round(R/sqrt(2));

    int f = (r_sqr-r_sqr*y + 0.25*r_sqr + 0.5);
    int df = 0;
    int delta = -2*r_sqr * y;

    // идем по окружности до центра чатверти
    while(x <= rd2)
    {
        plot4(&painter, X_c, Y_c, x, y);
        x++;
        if (f >= 0)
        {
            y--;
            delta += 2*r_sqr;
            f += delta;
        }
        df +=2*r_sqr;
        f += df +r_sqr;
    }
    delta = 2*r_sqr*x;
    f+= -r_sqr *(x+y);
    df = -2*r_sqr*y;
    while(y>= 0)
    {
        plot4(&painter, X_c, Y_c, x, y);
        y--;
        if (f < 0)
        {
            x++;
            delta += 2*r_sqr;
            f += delta;
        }
        df += 2*r_sqr;
        f += df +r_sqr;
    }*/
}

void Canvas::DrawEllipseMidpoint(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);

    int a_sqr = A*A;
    int b_sqr = B*B;
    int x = 0;
    int y = B;
    int rd2 = a_sqr/sqrt(a_sqr+b_sqr);
    //fpr = b*b(x+1)^2 + a*a(y*y -0.5) - a*a*b*b

    int f = (b_sqr - a_sqr * y + 0.25 * a_sqr + 0.5);
    int df = 0;
    int delta = -2*a_sqr * y;

    while(x <= rd2)
    {
        plot4(&painter, X_c, Y_c, x, y);

        x++;
        if (f >= 0)
        {
            y--;
            delta += 2*a_sqr;
            f += delta;
        }
        df +=2*b_sqr;
        f += df +b_sqr;
    }
    delta = 2*b_sqr*x;
    f+= -b_sqr * (x + 0.75) - a_sqr * (y - 0.75);
    df = -2*a_sqr*y;

    while(y >= 0)
    {
        plot4(&painter, X_c, Y_c, x, y);
        y--;
        if (f < 0)
        {
            x++;
            delta += 2*b_sqr;
            f += delta;
        }
        df += 2*a_sqr;
        f += df +a_sqr;
    }
}

void Canvas::DrawCircleQt(int X_c, int Y_c, int R)
{
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
    painter.setPen(pen);
    painter.drawEllipse(QPointF(X_c, Y_c), R, R);
}

void Canvas::DrawEllipseQt(int X_c, int Y_c, int A, int B)
{
    QPainter painter(&my_pixmap);
    //setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue()));
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
            //DrawEllipseBrezenham(X_center, Y_center, Radius, Radius);
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

#include <chrono>

using namespace std;

#define ITERATIONS 100

double Canvas::getCircleTime(int R, Algoritm alg)
{
    //srand(time(0));
    int X_c = 10000, Y_c = 10000;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    //std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    switch (alg)
    {
        case CANON:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawCircleCanon(X_c, Y_c, R);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case PARAM:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawCircleParam(X_c, Y_c, R);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case BREZENHAM:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawCircleBrezenham(X_c, Y_c, R);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case MIDPOINT:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawCircleMidpoint(X_c, Y_c, R);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case STANDART:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawCircleQt(X_c, Y_c, R);
            end = chrono::high_resolution_clock::now();
            break;
        }
        default:
        //???
        break;
    }
    chrono::duration<double> dur = end - start;
    return dur.count()/ITERATIONS;
}

double Canvas::getEllipseTime(int A, int B, Algoritm alg)
{
    //srand(time(0));
    int X_c = 10000, Y_c = 10000;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    //std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    switch (alg)
    {
        case CANON:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawEllipseCanon(X_c, Y_c, A, B);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case PARAM:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawEllipseParam(X_c, Y_c, A, B);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case BREZENHAM:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawEllipseBrezenham(X_c, Y_c, A, B);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case MIDPOINT:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawEllipseMidpoint(X_c, Y_c, A, B);
            end = chrono::high_resolution_clock::now();
            break;
        }
        case STANDART:
        {
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < ITERATIONS; i++)
                DrawEllipseQt(X_c, Y_c, A, B);
            end = chrono::high_resolution_clock::now();
            break;
        }
        default:
        //???
        break;
    }
    chrono::duration<double> dur = end - start;
    return dur.count()/ITERATIONS;
}


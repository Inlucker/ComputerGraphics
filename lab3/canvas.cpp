#include "canvas.h"
#include <math.h>
#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    //isClean = false;
    method = DIG_DIF_ANALIZ;
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
    //Создание рисовальщика
    //painter.begin(this); //Захват контекста

    //DRAW in pixmap

    //if (!isClean)
        switch (method)
        {
            case DIG_DIF_ANALIZ:
            {
            /*
                1. Ввод (xн, ун), (хк, ук)
                2. dx = xк - хн, dy = ук - ун
                3. Δx = |dx|, Δy = |dy|
                4. Если Δx > Δy, то l = Δx, иначе l = Δy
                5. dx = dx / l, dy = dy / l
                6. x = хн, у = ун (х, у вещественные)
                7. Цикл построения отрезка (по i от 1 до i + 1)
                   7.1. Высветить точку (округление(x), округлуние(у))
                   7.2. x = x + dx, y = y + dy
                   7.3 Конец цикла
                8. Конец.
            */

                /*double dX = fabs(X_start - X_end), dY = abs(Y_start - Y_end);
                double l = fmax(dX, dY);
                dX = (X_end - X_start) / l;
                dY = (Y_end - Y_start) / l;
                //dX /= l;
                //dY /= l;
                double X = X_start, Y = Y_start;

                QPainter painter(&my_pixmap);
                painter.setPen(pen);

                while (fabs(X - X_end) > 1 || fabs(Y - Y_end) > 1)
                {
                    painter.drawPoint(int(X), int(Y));
                    //QPoint p = QPoint(int(X), int(Y));
                    //draw_point(p);
                    X = X + dX, Y += dY;
                }*/

                //painter.end();

                break;
            }
            default:
            //???
            break;
        }

    /*QPainter painter(this);
    painter.translate(width() / 2, height() / 2);
    painter.drawPixmap(0, 0, my_pixmap);*/

    QPainter painter2(this);

    //float x_center = width() / 2;
    //float y_center = height() / 2;
    //painter2.translate(x_center, y_center);

    //painter2.scale(1, -1);

    //painter.drawPixmap(width() / 2, height() / 2, my_pixmap);
    painter2.drawPixmap(0, 0, my_pixmap);

    //isClean = false;

    //painter.end(); //Освобождение контекста
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

void Canvas::draw()
{
    switch (method)
    {
        case DIG_DIF_ANALIZ:
        {
        /*
            1. Ввод (xн, ун), (хк, ук)
            2. dx = xк - хн, dy = ук - ун
            3. Δx = |dx|, Δy = |dy|
            4. Если Δx > Δy, то l = Δx, иначе l = Δy
            5. dx = dx / l, dy = dy / l
            6. x = хн, у = ун (х, у вещественные)
            7. Цикл построения отрезка (по i от 1 до i + 1)
               7.1. Высветить точку (округление(x), округлуние(у))
               7.2. x = x + dx, y = y + dy
               7.3 Конец цикла
            8. Конец.
        */

            double dX = fabs(X_start - X_end), dY = abs(Y_start - Y_end);
            double step = fmax(dX, dY);
            dX = (X_end - X_start) / step;
            dY = (Y_end - Y_start) / step;
            double X = X_start, Y = Y_start;

            QPainter painter(&my_pixmap);
            painter.setPen(pen);

            painter.drawPoint(int(X), int(Y));
            while (fabs(X - X_end) > 1 || fabs(Y - Y_end) > 1)
            {
                //QPoint p = QPoint(int(X), int(Y));
                //draw_point(p);
                X = X + dX, Y += dY;
                painter.drawPoint(int(X), int(Y));
            }
            break;
        }
        case BREZENHAM_FLOAT:
        {
            /*
            1. Ввод исходных данных (Xн, Yн), (Xк, Yк)
            2. X = Xн ; Y = Yн
            3. dx = Xк - Xн; dx = Xк - Xн
            4. Sх = sign(dx); Sy = sign(dy)
            5. dx = |dx|; dy = |dy|
            6. Если dx > dy, то обмен = 0, иначе обмен = 1; t = dx; dx = dy; dy = t
            7. m = dy / dx; e = m - 0.5
            8. Цикл определения отрезка (по i от 1 до dx + 1)
               8.1. Высвечивание T(x, y)
               8.2. Если e >= 0, то
                1) если обмен = 0, то y = y + sy, иначе x = x + sx
                2) e = e - 1
               8.3. Если обмен = 0, то x = x + sx, иначе y = y + sy
               8.4. e = e + m
               8.5. Конец цикла
            9. Конец
            */

            int X = X_start, Y = Y_start;
            int dX = X_end - X_start, dY = Y_end - Y_start;
            int SX = sign(dX), SY = sign(dY);
            dX = abs(dX), dY = abs(dY);

            int step;
            if (dY >= dX)
            {
                //dX, dY = dY, dX;
                int tmp = dX;
                dX = dY;
                dY = tmp;
                step = 1; // шагаем по y
            }
            else
                step = 0;

            double tg = double(dY) / double(dX) ; // tангенс угла наклона
            double er = tg - 0.5; // начальное значение ошибки

            QPainter painter(&my_pixmap);
            painter.setPen(pen);

            painter.drawPoint(X, Y);
            while (X != X_end || Y != Y_end)
            {
                if (er >= 0)
                {
                    if (step == 1) // dy >= dx
                        X += SX;
                    else // dy < dx
                        Y += SY;
                    er -= 1; // отличие от целого
                    //stairs.append(st)
                    //st = 0
                }
                if (er <= 0)
                {
                    if (step == 0) // dy < dx
                        X += SX;
                    else // dy >= dx
                        Y += SY;
                    //st += 1
                    er += tg; // отличие от целого
                }
                painter.drawPoint(X, Y);
            }
            break;
        }
        case BREZENHAM_INT:
        {
            /*
            1. Ввод исходных данных (Xн, Yн), (Xк, Yк)
            2. X = Xн ; Y = Yн
            3. dx = Xк - Xн; dx = Xк - Xн
            4. Sх = sign(dx); Sy = sign(dy)
            5. dx = |dx|; dy = |dy|
            6. Если dx > dy, то обмен = 0, иначе обмен = 1; t = dx; dx = dy; dy = t
            7. (для челочисленного e = 2dy - dx)
            8. Цикл определения отрезка (по i от 1 до dx + 1)
               8.1. Высвечивание T(x, y)
               8.2. Если e >= 0, то
                1) если обмен = 0, то y = y + sy, иначе x = x + sx
                2) (для целочисленного e = e - 2dx)
               8.3. Если обмен = 0, то x = x + sx, иначе y = y + sy
               8.4. (для целочисленного e = e + 2dy)
               8.5. Конец цикла
            9. Конец
            */

            int X = X_start, Y = Y_start;
            int dX = X_end - X_start, dY = Y_end - Y_start;
            int SX = sign(dX), SY = sign(dY);
            dX = abs(dX), dY = abs(dY);

            int step;
            if (dY >= dX)
            {
                //dX, dY = dY, dX;
                int tmp = dX;
                dX = dY;
                dY = tmp;
                step = 1; // шагаем по y
            }
            else
                step = 0;

            int er = 2 * dY - dX; // отличие от вещественного (e = tg - 1 / 2) tg = dy / dx

            QPainter painter(&my_pixmap);
            painter.setPen(pen);

            painter.drawPoint(X, Y);
            while (X != X_end || Y != Y_end)
            {
                if (er >= 0)
                {
                    if (step == 1) // dy >= dx
                        X += SX;
                    else // dy < dx
                        Y += SY;
                    er -= 2 * dX; // отличие от вещественного (e -= 1)
                    //stairs.append(st)
                    //st = 0
                }
                if (er <= 0)
                {
                    if (step == 0) // dy < dx
                        X += SX;
                    else // dy >= dx
                        Y += SY;
                    //st += 1
                    er += 2 * dY; // отличие от вещественного (e += tg)
                }
                painter.drawPoint(X, Y);
            }
            break;
        }
        case BREZENHAM_STEP_REM:
        {
            int X = X_start, Y = Y_start;
            int I = 100;
            //fill = get_rgb_intensity(canvas, fill, I)
            int dX = X_end - X_start, dY = Y_end - Y_start;
            int SX = sign(dX), SY = sign(dY);
            dX = abs(dX), dY = abs(dY);

            int step;
            if (dY >= dX)
            {
                int tmp = dX;
                dX = dY;
                dY = tmp;
                step = 1;
            }
            else
                step = 0;

            double tg = double(dY) / double(dX) * double(I); // тангенс угла наклона (умножаем на инт., чтобы не приходилось умножать внутри цикла
            //double er = double(I) / 2; // интенсивность для высвечивания начального пикселя
            double er = 0.5;
            double w = double(I) - tg; // пороговое значение

            QPainter painter(&my_pixmap);
            painter.setPen(pen);

            painter.drawPoint(X, Y);
            while (X != X_end || Y != Y_end)
            {
                if (er < w)
                {
                    if (step == 0) // dy < dx
                        X += SX; // -1 if dx < 0, 0 if dx = 0, 1 if dx > 0
                    else // dy >= dx
                        Y += SY; // -1 if dy < 0, 0 if dy = 0, 1 if dy > 0
                    //st += 1 // stepping
                    er += tg;
                }
                else if (er >= w)
                {
                    X += SX;
                    Y += SY;
                    er -= w;
                    //stairs.append(st)
                    //st = 0
                }
                painter.drawPoint(X, Y);
            }

            break;
        }
        default:
        //???
        break;
    }
}

/*void Canvas::draw_point(QPoint point)
{
    //std::cout << "here\n";
    QPainter painter(&my_pixmap);
    painter.setPen(pen);
    painter.drawPoint(point);
    //update() ;
}*/

void Canvas::clean()
{
    my_pixmap = QPixmap(2000, 2000);
    my_pixmap.fill(QColor(0,0,0,0));
    update();
}

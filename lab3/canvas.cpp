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

void Canvas::plot(QPainter *p, int x, int y, int c)
{
    setPenColor(QColor(pen.color().red(), pen.color().green(), pen.color().blue(), int(double(c))));
    p->setPen(pen);
    p->drawPoint(x, y);
}

void Canvas::DrawPoint(QPainter *p, bool steep, int x, int y, int c)
{
    if (!steep)
        plot(p, x, y, c);
    else
        plot(p, y, x, c);
}

void Canvas::draw()
{
    QPainter painter(&my_pixmap);
    painter.setPen(pen);
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
            double steep = fmax(dX, dY);
            dX = (X_end - X_start) / steep;
            dY = (Y_end - Y_start) / steep;
            double X = X_start, Y = Y_start;

            //QPainter painter(&my_pixmap);
            //painter.setPen(pen);

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

            painter.drawPoint(X, Y);
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

            int er = 2 * dY - dX; // отличие от вещественного (e = tg - 1 / 2) tg = dy / dx

            //QPainter painter(&my_pixmap);
            //painter.setPen(pen);

            painter.drawPoint(X, Y);
            while (X != X_end || Y != Y_end)
            {
                if (er >= 0)
                {
                    if (steep == 1) // dy >= dx
                        X += SX;
                    else // dy < dx
                        Y += SY;
                    er -= 2 * dX; // отличие от вещественного (e -= 1)
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
                    er += 2 * dY; // отличие от вещественного (e += tg)
                }
                painter.drawPoint(X, Y);
            }
            break;
        }
        case BREZENHAM_STEP_REM:
        {
            /*
            1. Ввод Xн, Yн, Xк, Yк, I - количество уровней интенсивности.
            2. Вычисление приращений dX = Xк-Xн и dY = Yк-Yн.
            3. Вычисление шага изменения каждой координаты: SX = sign(dX), SY = sign(dY).
            4. dX = |dX|, dY = |dY|.
            5. m = dY / dX
            6. Если m > 1
                6.1.t = dX;
                6.2 dX = dY;
                6.3 dY = t;
                6.4 m = 1/m;
                6.5 obmen = 0, если m < 1, иначе obmen = 1
            7. e = I / 2
            8. X = Xн, Y = Yн.
            9. m = mI, W = I-m.
            10. Высвечивание пиксела с координатами (X,Y) интенсивностью E(e).
            11. Цикл от i = 1 до i = dX с шагом 1:
                11.1. Если e < W, то
                      11.1.1 если obmen = 0, то X = X + SX, иначе Y = Y + SY
                      11.1.2 e = e + m.
                11.2 иначе
                      11.2.1 X = X + SX, Y = Y + SY, e = e - W.
                11. 3 Высвечивание пикселя с координатами (X,Y) интенсивностью E(e).
            12. Конец цикла.
            */
            int X = X_start, Y = Y_start;
            int I = 255;
            //fill = get_rgb_intensity(canvas, fill, I)
            int dX = X_end - X_start, dY = Y_end - Y_start;
            int SX = sign(dX), SY = sign(dY);
            dX = abs(dX), dY = abs(dY);

            int steep;
            if (dY >= dX)
            {
                int tmp = dX;
                dX = dY;
                dY = tmp;
                steep = 1;
            }
            else
                steep = 0;

            double tg = double(dY) / double(dX) * double(I); // тангенс угла наклона (умножаем на инт., чтобы не приходилось умножать внутри цикла
            double er = double(I) / 2; // интенсивность для высвечивания начального пикселя
            double w = double(I) - tg; // пороговое значение
            //std::cout << w << std::endl;
            //std::cout << tg << std::endl;

            /*setPenColor(QColor(0, 0, 0, int(double(er))));
            painter.setPen(pen);
            painter.drawPoint(X, Y);*/
            plot(&painter, X, Y, int(er));
            while (X != X_end || Y != Y_end)
            {
                if (er < w)
                {
                    if (steep == 0) // dy < dx
                        X += SX; // -1 if dx < 0, 0 if dx = 0, 1 if dx > 0
                    else // dy >= dx
                        Y += SY; // -1 if dy < 0, 0 if dy = 0, 1 if dy > 0
                    //st += 1 // steepping
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
                //std::cout << er << std::endl;
                //std::cout << int(255.0 / 50.0 * double(er)) << std::endl;
                plot(&painter, X, Y, int(er));
                /*setPenColor(QColor(0, 0, 0, int(double(er))));
                painter.setPen(pen);
                painter.drawPoint(X, Y);*/
            }
            break;
        }
        case VU:
        {
            /*
            private void WuLine(int x0, int y0, int x1, int y1)
            {
                var steep = Math.Abs(y1 - y0) > Math.Abs(x1 - x0);
                if (steep)
                {
                    Swap(ref x0, ref y0);
                    Swap(ref x1, ref y1);
                }
                if (x0 > x1)
                {
                    Swap(ref x0, ref x1);
                    Swap(ref y0, ref y1);
                }

                DrawPoint(steep, x0, y0, 1); // Эта функция автоматом меняет координаты местами в зависимости от переменной steep
                DrawPoint(steep, x1, y1, 1); // Последний аргумент — интенсивность в долях единицы
                float dx = x1 - x0;
                float dy = y1 - y0;
                float gradient = dy / dx;
                float y = y0 + gradient;
                for (var x = x0 + 1; x <= x1 - 1; x++)
                {
                    DrawPoint(steep, x, (int)y, 1 - (y - (int)y));
                    DrawPoint(steep, x, (int)y + 1, y - (int)y);
                    y += gradient;
                }
            }
            */

            int I = 255;
            bool steep = abs(Y_end - Y_start) > abs(X_end - X_start);

            if (steep)
            {
                int tmp = X_start;
                X_start = Y_start;
                Y_start = tmp;

                tmp = X_end;
                X_end = Y_end;
                Y_end = tmp;
            }
            if (X_start > X_end)
            {
                int tmp = X_start;
                X_start = X_end;
                X_end = tmp;

                tmp = Y_start;
                Y_start = Y_end;
                Y_end = tmp;
            }

            DrawPoint(&painter, steep, X_start, Y_start, I);
            DrawPoint(&painter, steep, X_end, Y_end, I);

            double dX = X_end - X_start, dY = Y_end - Y_start;

            double tg;
            if (dX == 0)
                tg = 1;
            else
                tg = dY / dX;

            //int xend = round(X_start);
            //int yend = Y_start + tg * (xend - X_start);
            //int  xpx1 = xend;
            //double y = double(yend) + tg;
            double y = Y_start + tg;

            //xend = int(double(X_end) + 0.5);
            //int xpx2 = xend;
            for (int x = X_start + 1; x < X_end; x++)
            {
                DrawPoint(&painter, steep, x, int(y), I*(abs(1.0 - y + int(y))));
                DrawPoint(&painter, steep, x, int(y)+1, I*(abs(y - int(y))));
                y += tg;
            }


        }
        case STANDART:
        {
            //QPainter painter(&my_pixmap);
            //painter.setPen(pen);
            painter.drawLine(X_start, Y_start, X_end, Y_end);
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

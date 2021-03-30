#include "canvas.h"
#include "math.h"
#include "iostream"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:white;");
    //background_color = Qt::white;
    clean();
    pen = QPen(Qt::black);
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
            }

            //painter.end();

            break;
        }
        case CLEAN:
        {
            clean();
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

    std::cout << "test\n";

    //painter.end(); //Освобождение контекста
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
}

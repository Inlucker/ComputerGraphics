#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView()
{
    points_mn = NULL;
    clearPoints();
}

MyGraphicsView::~MyGraphicsView()
{
    if (points_mn)
    {
        delete [] points_mn;
        points_mn = NULL;
    }
}

void MyGraphicsView::clearPoints()
{
    /*rez_x1 = -8;
    rez_y1 = -8;
    rez_x2 = -8;
    rez_y2 = -8;
    rez_x3 = -8;
    rez_y3 = -8;*/

    if (points_mn)
    {
        delete [] points_mn;
        points_mn = NULL;
    }

    points_number = 0;

    /*for (int i = 0; i < MAX_POINT_NUMBER; i++)
    {
        x[i] = -1;
        y[i] = -1;
    }*/
    /*for (int i = 0; i < TRIANGLE_POINTS_NUMBER; i++)
    {
        x_rez[i] = -1;
        y_rez[i] = -1;
    }*/
}

void MyGraphicsView::paintEvent(QPaintEvent *)
{
    //создание рисовальщика
    painter.begin(this); //захват контекста
    double x_center = width() / 2;
    double y_center = height() / 2;
    //cout << x_center << " " << y_center << endl;

    painter.translate(x_center, y_center);

    //Scale
    double x_max = 0;
    double y_max = 0;

    for (int i = 0; i < points_number; i++)
    {
        if (qAbs(points_mn[i].first) > x_max)
            x_max = qAbs(points_mn[i].first);

        if (qAbs(points_mn[i].second) > y_max)
            y_max = qAbs(points_mn[i].second);
    }

    double k = 1;

    if (x_max != 0 && y_max != 0)
    {
        //k = min((x_center - 50) / (x_max + (x_center / 10)), (y_center - 25) / (y_max + (y_center / 10)));
        k = min((x_center - 50) / (x_max), (y_center - 25) / (y_max));
    }
    //cout << "k = " << k << endl;

    //Old Scale
    /*int x_max = 0;
    int y_max = 0;

    for (int i = 0; i < points_number; i++)
    {
        if (qAbs(points_mn[i].first) > x_max)
            x_max = qAbs(points_mn[i].first);

        if (qAbs(points_mn[i].second) > y_max)
            y_max = qAbs(points_mn[i].second);
    }

    int k_x = 1;
    int k_y = 1;

    if (x_max != 0 && y_max != 0)
    {
        //int k = max(x_max, y_max);
        //painter.scale(x_center / k, y_center/ k);
        k_x = x_center / x_max;
        k_y = y_center / y_max;
        painter.scale(x_center / x_max, y_center / y_max);
    }*/

    //All dots
    /*painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    for (int i = 0; i < MAX_POINT_NUMBER; i++)
    {
        QRect rect(x[i] - 2, HEIGHT - y[i] - 2, 4, 4);
        if (x[i] >= 0 && y[i] >= 0)
        {
            painter.drawEllipse(rect);
            //painter.drawEllipse(x[i] - 2, height() - y[i] - 2, 4, 4);
        }
    }*/
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    for (int i = 0; i < points_number; i++)
    {
        painter.drawEllipse(QPointF(points_mn[i].first * k, HEIGHT - points_mn[i].second * k), 2, 2);
        //cout << points_mn[i].first * k << " " << HEIGHT - points_mn[i].second * k << endl;
    }

    if (rez)
    {
        //Triangle
        painter.drawLine(rez_x1 * k, (HEIGHT - rez_y1) * k, rez_x2 * k, (HEIGHT - rez_y2) * k);
        painter.drawLine(rez_x2 * k, (HEIGHT - rez_y2) * k, rez_x3 * k, (HEIGHT - rez_y3) * k);
        painter.drawLine(rez_x3 * k, (HEIGHT - rez_y3) * k, rez_x1 * k, (HEIGHT - rez_y1) * k);

        //Triangle medians
        painter.drawLine(rez_x1 * k, (HEIGHT - rez_y1) * k, (rez_x2 * k + rez_x3 * k) / 2, (HEIGHT - rez_y2 * k + HEIGHT - rez_y3 * k) / 2);
        painter.drawLine(rez_x2 * k, (HEIGHT - rez_y2) * k, (rez_x3 * k + rez_x1 * k) / 2, (HEIGHT - rez_y3 * k + HEIGHT - rez_y1 * k) / 2);
        painter.drawLine(rez_x3 * k, (HEIGHT - rez_y3) * k, (rez_x1 * k + rez_x2 * k) / 2, (HEIGHT - rez_y1 * k + HEIGHT - rez_y2 * k) / 2);


        //Traingle dots
        painter.setBrush(QBrush(Qt::green,Qt::SolidPattern)); //transparent
        painter.drawEllipse(QPointF(rez_x1 * k, HEIGHT - rez_y1 * k), 4, 4);
        painter.drawEllipse(QPointF(rez_x2 * k, HEIGHT - rez_y2 * k), 4, 4);
        painter.drawEllipse(QPointF(rez_x3 * k, HEIGHT - rez_y3 * k), 4, 4);

        QRect rect(rez_x1 * k - 40, (HEIGHT - rez_y1) * k - 10 - 12 , 80, 20);
        painter.drawText(rect, Qt::AlignCenter, tr("#%1 (%2; %3)").arg(id1).arg(rez_x1).arg(rez_y1));
        rect = QRect(rez_x2 * k - 40, (HEIGHT - rez_y2) * k - 10 - 12, 80, 20);
        painter.drawText(rect, Qt::AlignCenter, tr("#%1 (%2; %3)").arg(id2).arg(rez_x2).arg(rez_y2));
        rect = QRect(rez_x3 * k - 40, (HEIGHT - rez_y3) * k - 10 - 12, 80, 20);
        painter.drawText(rect, Qt::AlignCenter, tr("#%1 (%2; %3)").arg(id3).arg(rez_x3).arg(rez_y3));
    }

    //painter.fillRect(0, 0, width(), height(), Qt::CrossPattern); //отрисовка

    painter.end();//освобождение контекста
}

/*void MyGraphicsView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); //новый объект "рисовальщика"
    painter.setPen (QPen(Qt::red,Qt::SolidLine));
    //создать и установить перо - красная сплошная линия
    painter.drawLine(0,0,width(),height());
    //нарисовать линию через рабочую область формы
    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
    //создать и установить кисть - зелёная слошная заливка
    QPoint center(width()/2,height()/2);
    int rad = qMin(width()/4,height()/4);
    painter.drawEllipse(center,rad,rad);
    //нарисовать окружность по центру
    painter.setFont(QFont("sans-serif",-1,10));
    //установить шрифт заданного начертания и размера 10 пт
    QRect rect(center.x()-rad,center.y()-rad,rad*2,rad*2);
    painter.drawText(rect, Qt::AlignCenter, tr("Hello,\nworld!"));
    //вывели строку текста, выравненную по центру
}*/

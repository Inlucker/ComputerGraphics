#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView()
{
    clearPoints();
}

MyGraphicsView::~MyGraphicsView()
{

}

void MyGraphicsView::clearPoints()
{
    rez_x1 = -8;
    rez_y1 = -8;
    rez_x2 = -8;
    rez_y2 = -8;
    rez_x3 = -8;
    rez_y3 = -8;

    for (int i = 0; i < MAX_POINT_NUMBER; i++)
    {
        x[i] = -1;
        y[i] = -1;
    }
    for (int i = 0; i < TRIANGLE_POINTS_NUMBER; i++)
    {
        x_rez[i] = -1;
        y_rez[i] = -1;
    }
}

void MyGraphicsView::paintEvent(QPaintEvent *)
{
    QPainter painter; //создание рисовальщика
    painter.begin(this); //захват контекста


    //QPoint center(width()/2,height()/2);
    //int rad = qMin(width()/4,height()/4);
    //rad = 5;
    //QRect rect(center.x()-rad,center.y()-rad,rad*2,rad*2);
    //painter.drawText(rect, Qt::AlignCenter, tr("Hello,\nworld!"));

    //All dots
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    for (int i = 0; i < MAX_POINT_NUMBER; i++)
    {
        QRect rect(x[i] - 2, height() - y[i] - 2, 4, 4);
        if (x[i] && y[i] >= 0)
        {
            painter.drawEllipse(rect);
            //painter.drawEllipse(x[i] - 2, height() - y[i] - 2, 4, 4);
        }
    }

    if (rez_x1 > 0 && rez_y1 > 0 && rez_x2 > 0 && rez_y2 > 0 && rez_x3 > 0 && rez_y3 > 0)
    {
        //Triangle
        painter.drawLine(rez_x1, height() - rez_y1, rez_x2, height() - rez_y2);
        painter.drawLine(rez_x2, height() - rez_y2, rez_x3, height() - rez_y3);
        painter.drawLine(rez_x3, height() - rez_y3, rez_x1, height() - rez_y1);

        //Triangle medians
        painter.drawLine(rez_x1, height() - rez_y1, (rez_x2 + rez_x3) / 2, (height() - rez_y2 + height() - rez_y3) / 2);
        painter.drawLine(rez_x2, height() - rez_y2, (rez_x3 + rez_x1) / 2, (height() - rez_y3 + height() - rez_y1) / 2);
        painter.drawLine(rez_x3, height() - rez_y3, (rez_x1 + rez_x2) / 2, (height() - rez_y1 + height() - rez_y2) / 2);


        //Traingle dots
        painter.setBrush(QBrush(Qt::green,Qt::SolidPattern)); //transparent
        painter.drawEllipse(rez_x1 - 4, height() - rez_y1 - 4, 8, 8);
        painter.drawEllipse(rez_x2 - 4, height() - rez_y2 - 4, 8, 8);
        painter.drawEllipse(rez_x3 - 4, height() - rez_y3 - 4, 8, 8);

        QRect rect(rez_x1 - 40, height() - rez_y1 - 10 - 12, 80, 20);
        painter.drawText(rect, Qt::AlignCenter, tr("#%1 (%2; %3)").arg(id1).arg(rez_x1).arg(rez_y1));
        rect = QRect(rez_x2 - 40, height() - rez_y2 - 10 - 12, 80, 20);
        painter.drawText(rect, Qt::AlignCenter, tr("#%1 (%2; %3)").arg(id2).arg(rez_x2).arg(rez_y2));
        rect = QRect(rez_x3 - 40, height() - rez_y3 - 10 - 12, 80, 20);
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

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

    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    for (int i = 0; i < MAX_POINT_NUMBER; i++)
    {
        if (x[i] && y[i] >= 0)
            painter.drawEllipse(x[i] - 2, height() - y[i] - 2, 4, 4);
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

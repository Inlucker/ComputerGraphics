#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    semiPen = QPen(Qt::black);
    mainPen = QPen(Qt::red);
    setStyleSheet("background-color:white;");
    delay = true;
    clean();
}

Canvas::~Canvas()
{

}

void Canvas::setMainPenColor(QColor color)
{
    mainPen.setColor(color);
}

void Canvas::setSemiPenColor(QColor color)
{
    semiPen.setColor(color);
}

void Canvas::setDelay(bool val)
{
    delay = val;
}

void Canvas::addPoint(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    QPainter painter(&my_pixmap);
    painter.setPen(semiPen);
    plot(&painter, int_x, int_y);
    if (isFirstPoint)
    {
        x0 = int_x;
        y0 = int_y;
        isFirstPoint = false;
    }
    else
    {
        painter.drawLine(prev_x, prev_y, int_x, int_y);
    }
    prev_x = int_x;
    prev_y = int_y;
    update();
}

void Canvas::lock()
{
    addPoint(x0, y0);
    isLocked = true;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter pixmap_painter(this);
    pixmap_painter.drawPixmap(0, 0, my_pixmap);
}

void Canvas::plot(QPainter *p, int x, int y)
{
    //p->setPen(semiPen);
    p->drawPoint(x, y);
}

void Canvas::clean()
{
    x0 = 0, y0 = 0;
    isFirstPoint = true;
    isLocked = false;
    my_pixmap = QPixmap(2000, 2000);
    my_pixmap.fill(QColor(0,0,0,0));
    update();
}

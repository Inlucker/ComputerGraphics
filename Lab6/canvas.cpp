#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    semiPen = QPen(Qt::black);
    mainPen = QPen(Qt::red);
    bgPen = QPen(Qt::white);
    setStyleSheet("background-color:white;");
    isDelay = true;

    color_border = QColor(Qt::black);
    color_shading = QColor(Qt::red);
    color_background = QColor(Qt::white);

    clean();
}

Canvas::~Canvas()
{
    delete painter;
    delete my_pixmap;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && rect().contains(event->pos()))
    {
        double x = prev_x;
        double y = prev_y;
        if (event->modifiers() == Qt::ALT && !firstPointCheck())
        {
            x = event->position().x();
            if ((event->position().x() > prev_x && event->position().y() < prev_y) || (event->position().x() < prev_x && event->position().y() > prev_y))
                y = y - (x - prev_x);
            else
                y = y + (x - prev_x);
        }
        else if (event->modifiers() == Qt::CTRL && !firstPointCheck())
        {
            x = event->position().x();
        }
        else if (event->modifiers() == Qt::SHIFT && !firstPointCheck())
        {
            y = event->position().y();
        }
        else
        {
            x = event->position().x();
            y = event->position().y();
        }

        addPoint(x, y);
    }
    else if (event->button() == Qt::RightButton && rect().contains(event->pos()))
    {

    }
}

void Canvas::setMainPenColor(QColor color)
{
    color_shading = color;
    mainPen.setColor(color);
}

void Canvas::setSemiPenColor(QColor color)
{
    color_border = color;
    semiPen.setColor(color);
}

void Canvas::setBackgroundColor(QColor color)
{
    color_background = color;
    bgPen.setColor(color);
}

void Canvas::setDelay(bool val)
{
    isDelay = val;
}

void Canvas::addPoint(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    //QPainter painter(my_pixmap);
    painter->setPen(semiPen);
    plot(int_x, int_y);
    if (isFirstPoint)
    {
        x0 = int_x;
        y0 = int_y;
        isFirstPoint = false;
        isLocked = false;
    }
    else
    {
        edges.insert(edges.end(), Edge(prev_x, prev_y, int_x, int_y));
        painter->drawLine(prev_x, prev_y, int_x, int_y);
    }
    prev_x = int_x;
    prev_y = int_y;
    update();
}

void Canvas::lock()
{
    addPoint(x0, y0);
    isLocked = true;
    isFirstPoint = true;
}

QColor Canvas::getPixelAt(int x, int y)
{
    return grab(QRect(x, y, 1, 1)).toImage().pixelColor(0,0);
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

void Canvas::fill(int del)
{

}

bool Canvas::firstPointCheck()
{
    return isFirstPoint;
}

bool Canvas::locked()
{
    return isLocked;
}

int Canvas::getEdgesNumber()
{
    return edges.size();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter pixmap_painter(this);
    pixmap_painter.drawPixmap(0, 0, *my_pixmap);
}

void Canvas::plot(int x, int y)
{
    //p->setPen(semiPen);
    painter->drawPoint(x, y);
}

void Canvas::clean()
{
    x0 = 0, y0 = 0;
    isFirstPoint = true;
    isLocked = false;

    if (painter)
        delete painter;

    if (my_pixmap)
        delete my_pixmap;
    my_pixmap = new QPixmap(2000, 2000);
    my_pixmap->fill(QColor(0,0,0,0));

    painter = new QPainter(my_pixmap);
    painter->setPen(semiPen);

    edges.clear();

    update();
}

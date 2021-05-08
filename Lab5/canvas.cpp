#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    semiPen = QPen(Qt::black);
    mainPen = QPen(Qt::red);
    setStyleSheet("background-color:white;");
    delay = true;

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
}

void Canvas::setDelay(bool val)
{
    delay = val;
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

void Canvas::fill()
{
    int x_max = edges[0].x1;

    for (size_t i = 0; i < edges.size(); i++)
    {
        if (edges[i].x1 > x_max)
            x_max = edges[i].x1;
    }

    for (size_t i = 0; i < edges.size(); i++)
    {
        QImage image = my_pixmap->toImage();

        int x1 = edges[i].x1;
        int x2 = edges[i].x2;
        int y1 = edges[i].y1;
        int y2 = edges[i].y2;

        if (y1 > y2)
        {
            int tmp = y2;
            y2 = y1;
            y1 = tmp;
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        else if (y1 == y2)
            continue;

        double dx = (x2 - x1)/(double)(y2-y1);
        double xstart = x1;
        painter->setPen(color_shading);
        for (int y = y1; y < y2; y++)
        {
            for (int x = round(xstart); x <= x_max; x++)
            {

                //QColor color = image.pixelColor(x, y);
                QColor color = getPixelAt(x, y);
                if (color == color_background)
                {
                    painter->setPen(color_shading);
                }
                else if (color == color_shading)
                {
                    painter->setPen(color_background);
                }
                else
                {
                    painter->setPen(color_border);
                }
                painter->drawPoint(x,y);
            }
            xstart += dx;

            if (delay)
                repaint();

            this->update();
            //ui->draw_label->setPixmap(*scene);
        }
    }
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

    update();
}

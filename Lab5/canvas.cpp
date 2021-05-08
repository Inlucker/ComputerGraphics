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

//old fill
/*void Canvas::fill(int del)
{
    if (isDelay)
        delay = del;

    int x_max = edges[0].x1;

    for (size_t i = 0; i < edges.size(); i++)
    {
        if (edges[i].x1 > x_max)
            x_max = edges[i].x1;
    }

    for (size_t i = 0; i < edges.size(); i++)
    {
        //QImage image = my_pixmap->toImage();

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
        //else if (y1 == y2)
            //continue;

        double dx = (x2 - x1)/(double)(y2-y1);
        double xstart = x1;
        //painter->setPen(color_shading);
        for (int y = y1; y < y2; y++)
        {
            for (int x = round(xstart); x <= x_max; x++)
            {

                //QColor color = image.pixelColor(x, y);
                QColor color = getPixelAt(x, y);
                if (color == color_background)
                {
                    painter->setPen(color_shading);
                    //painter->setPen(mainPen);
                }
                else if (color == color_shading)
                {
                    painter->setPen(color_background);
                    //painter->setPen(bgPen);
                }
                else
                {
                    painter->setPen(color_border);
                    //painter->setPen(semiPen);
                }
                painter->drawPoint(x,y);
            }
            xstart += dx;

            if (isDelay)
            {
                Sleep(delay);
                repaint();
            }

            //ui->draw_label->setPixmap(*scene);
        }
    }
    this->update();
}*/

//new fill
void Canvas::fill(int del)
{
    if (isDelay)
        delay = del;

    int x_max = edges[0].x1;
    int x_min = edges[0].x1;

    int y_max = edges[0].y1;
    int y_min = edges[0].y1;

    for (size_t i = 0; i < edges.size(); i++)
    {
        if (edges[i].x1 > x_max)
            x_max = edges[i].x1;
        if (edges[i].x1 < x_min)
            x_min = edges[i].x1;

        if (edges[i].y1 > y_max)
            y_max = edges[i].y1;
        if (edges[i].y1 < y_min)
            y_min = edges[i].y1;
    }

    //Обрисовка
    painter->setPen(color_background);
    for (int y = y_min; y <= y_max; y++)
    {
        int count = 0;
        bool isPrevBorder = false;
        int last_x = -1;
        for (int x = x_min; x <= x_max; x++)
        {
            QColor color = getPixelAt(x, y);

            if (color == color_border && isPrevBorder)
                painter->drawPoint(x,y);

            if (color == color_border)
                isPrevBorder = true;
            else
                isPrevBorder = false;

            if (getPixelAt(x, y) == color_border)
            {
                last_x = x;
                count++;
            }

            //Kostil'
            if (x == x_max && count % 2 == 1)
            {
                painter->setPen(color_border);
                painter->drawPoint(last_x-1,y);
                painter->drawPoint(last_x,y);
                painter->setPen(color_background);
            }
        }

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }
    }

    //Зарисовка
    //painter->setPen(color_shading);
    for (int y = y_min; y <= y_max; y++)
    {
        bool flag = false;
        for (int x = x_min; x <= x_max; x++)
        {
            //QColor color = image.pixelColor(x, y);
            QColor color = getPixelAt(x, y);

            if (color == color_border)
                flag = !flag;

            if (flag)
            {
                painter->setPen(color_shading);
            }
            else
            {
                painter->setPen(color_background);
            }
            painter->drawPoint(x,y);
        }

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }

    }
    this->update();
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

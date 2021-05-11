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

int sign(double val)
{
  if (val > 0)
      return 1;
  if (val < 0)
      return -1;
  else
      return 0;
}

//new fill
/*void Canvas::fill(int del)
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

    //Обрисовка по лекциям (с проверкой на локальный экстремум)
    my_pixmap->fill(QColor(0,0,0,0));
    painter->setPen(color_border);
    for (size_t i = 0; i < edges.size(); i++)
    {
        int x1 = edges[i].x1;
        int x2 = edges[i].x2;
        int y1 = edges[i].y1;
        int y2 = edges[i].y2;

        int prevId = i - 1;
        if (prevId < 0)
        {
            prevId = edges.size() - 1;
        }
        Edge prevEdge = edges[prevId];

        int nextId = i + 1;
        if (nextId > edges.size() - 1)
        {
            nextId = 0;
        }
        Edge nextEdge = edges[nextId];

        bool swapFlag = false;
        if (y1 > y2)
        {
            int tmp = y2;
            y2 = y1;
            y1 = tmp;
            tmp = x2;
            x2 = x1;
            x1 = tmp;
            Edge tmp_edge = nextEdge;
            nextEdge = prevEdge;
            prevEdge = tmp_edge;
            swapFlag = true;
        }

        //если ребро не горизонтальное - обрисовка
        if (double(y2-y1) != 0)
        {
            double dx = (x2 - x1)/double(y2-y1);
            double x = x1 + (dx/2);

            //cout << "next edge\n";
            int y = y1;
            //(с проверкой на локальный экстремум)
            if (edges[i].isExtremum(prevEdge))
            {
                double tmp_x = x;
                while (getPixelAt(int(tmp_x + 0.5), y) == color_border)
                //if (getPixelAt(int(tmp_x + 0.5), y1) == color_border)
                {
                    if (!swapFlag)
                    {
                        if (prevEdge.x1 < int(tmp_x + 0.5))
                            tmp_x--;
                        else if (prevEdge.x1 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += sign(dx);
                    }
                    else
                    {
                        if (prevEdge.x2 < int(tmp_x + 0.5))
                            tmp_x--;
                        else if (prevEdge.x2 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += sign(dx);
                    }
                }
                painter->drawPoint(int(tmp_x + 0.5), y);
                //cout << "start(" << int(tmp_x + 0.5) << "; " << y << ")" << endl;
                x += dx; y++;
                if (isDelay)
                {
                    Sleep(delay);
                    repaint();
                }
                //Попробовать упростить без этого
            }

            //for (double y = y1 + 1; y < y2 - 1; y++)
            for (y; y < y2 - 1; y++)
            {
                double tmp_x = x;
                while (getPixelAt(int(tmp_x + 0.5), y) == color_border)
                {
                    //tmp_x++;
                    if (!swapFlag)
                    {
                        if (prevEdge.x1 < int(tmp_x + 0.5))
                            tmp_x--;
                        else if (prevEdge.x1 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += sign(dx);
                    }
                    else
                    {
                        if (prevEdge.x2 < int(tmp_x + 0.5))
                            tmp_x--;
                        else if (prevEdge.x2 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += sign(dx);
                    }
                }
                painter->drawPoint(int(tmp_x + 0.5), y);
                //cout << "(" << int(tmp_x + 0.5) << "; " << int(y) << ")" << endl;
                x += dx;
                if (isDelay)
                {
                    Sleep(delay);
                    repaint();
                }
            }

            //y = y2-1
            {
                double tmp_x = x;
                while (getPixelAt(int(tmp_x + 0.5), y) == color_border)
                    //if (getPixelAt(int(tmp_x + 0.5), y1) == color_border)
                {
                    if (!swapFlag)
                    {
                        if (nextEdge.x2 < int(tmp_x + 0.5)) //!=
                            tmp_x--;
                        else if (nextEdge.x2 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += -sign(dx);
                    }
                    else
                    {
                        if (nextEdge.x1 < int(tmp_x + 0.5))
                            tmp_x--;
                        else if (nextEdge.x1 > int(tmp_x + 0.5))
                            tmp_x++;
                        else
                            tmp_x += -sign(dx);
                    }
                }
                painter->drawPoint(int(tmp_x + 0.5), y);
                //cout << "end(" << int(tmp_x + 0.5) << "; " << y << ")" << endl;
                x += dx; y++;
                if (isDelay)
                {
                    Sleep(delay);
                    repaint();
                }
            }
        }

    }
    //cout << endl;

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
                //cout << "(" << x << "; " << y << ")" << endl;
            }
            else
            {
                painter->setPen(color_background);
            }
            painter->drawPoint(x,y);
        }
        //painter->setPen(color_background);
        //painter->drawPoint(x_max + 1, y);

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }
    }
    this->update();
}*/

//stable fill
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

    //Обрисовка старая
    my_pixmap->fill(QColor(0,0,0,0));
    painter->setPen(color_border);
    for (size_t i = 0; i < edges.size(); i++)
    {
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

        //обрисовка ?X + 1/2 > Xпересечения?
        double dx = (x2 - x1)/double(y2-y1);
        double x = x1;
        for (double y = y1; y < y2; y++)
        {
            double tmp_x = x;
            //cout << "(" << x << "; " << y << ") - ";
            while (getPixelAt(int(tmp_x + 0.5), y) == color_border)
            //if (getPixelAt(int(tmp_x + 0.5), y) == color_border)
            {
                tmp_x++;
            }
            painter->drawPoint(int(tmp_x + 0.5), y);
            cout << "(" << int(tmp_x + 0.5) << "; " << int(y) << ")" << endl;
            x += dx;
            if (isDelay)
            {
                Sleep(delay);
                repaint();
            }
        }
    }
    cout << endl;

    //Зарисовка
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
                //cout << "(" << x << "; " << y << ")" << endl;
            }
            else
            {
                painter->setPen(color_background);
            }
            painter->drawPoint(x,y);
        }
        painter->setPen(color_background);
        painter->drawPoint(x_max + 1, y);

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }
    }
    this->update();
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

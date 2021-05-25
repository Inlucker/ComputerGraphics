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

    isLMBPressed = false;

    edgeFlag = true;

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
        isLMBPressed = true;
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

        if (edgeFlag)
            addPoint(x, y);
        else
            setZatravka(x, y);
        //addPoint(x, y);
    }
    else
    {
        isLMBPressed = false;
        if (event->button() == Qt::RightButton && rect().contains(event->pos()))
        {
            if (edgeFlag)
                setZatravka(event->position().x(), event->position().y());
            else
                addPoint(event->position().x(), event->position().y());
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isLMBPressed && rect().contains(event->pos()))
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

        if (edgeFlag)
            addPoint(x, y);
        //addPoint(x, y);
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
        DrawLineBrezenheimFloat(prev_x, prev_y, int_x, int_y);
    }
    prev_x = int_x;
    prev_y = int_y;
    update();
}

void Canvas::setZatravka(double x, double y)
{
    xz = x;
    yz = y;
    isZatravka = true;
    painter->setPen(mainPen);
    painter->drawPoint(x, y);
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

void Canvas::find_next(stack<Point> &stack, int &x_left, int &x_right, const int &y)
{
    bool flag = false;
    int x = x_left;
    int xn;
    while (x <= x_right)
    {
        flag = false;
        QColor color = getPixelAt(x,y);
        while (color != color_border && color != color_shading && x <= x_right)
        {
            flag = true;
            x++;
            color = getPixelAt(x,y);
        }
        if (flag == true)
        {
            Point p(x, y);
            if (x == x_right && getPixelAt(x,y) != color_border && getPixelAt(x,y) != color_shading)
            {
                stack.push(p);
                cout << "HERE~@4124" << endl;
            }
            else
            {
                p.x--;
                stack.push(p);
            }
        }

        xn = x;
        color = getPixelAt(x,y);
        while ((color == color_border || color == color_shading) && x < x_right)
        {
            x++;
            color = getPixelAt(x,y);
        }
        if (x == xn)
            x++;

    }
}

void Canvas::findNext(stack<Point> &stack, int x_left, int x_right, int y)
{
    bool pushFlag = false;
    int x = x_left;
    while (x <= x_right)
    {
        pushFlag = false;
        while (getPixelAt(x,y) != color_border && getPixelAt(x,y) != color_shading && x <= x_right)
        {
            pushFlag = true;
            x++;
        }
        if (pushFlag)
        {
            stack.push(Point(x-1, y));
        }

        x++;
        while ((getPixelAt(x,y) == color_border || getPixelAt(x,y) == color_shading) && x < x_right)
        {
            x++;
        }
    }
}

void Canvas::checkPoint(stack<Point> &stack, int x, int y)
{
    if (getPixelAt(x,y) != color_border && getPixelAt(x,y) != color_shading)
        stack.push(Point(x,y));
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

void Canvas::fill_lines(int del)
{
    if (isDelay)
        delay = del;

    painter->setPen(color_shading);

    int x_left, x_right;

    stack<Point> myStack;
    Point z(xz, yz);
    myStack.push(z);

    int x_max = this->geometry().width();
    int y_max = this->geometry().height()-1;

    while (!myStack.empty())
    {
        Point p = myStack.top();
        myStack.pop();
        painter->drawPoint(p.x, p.y);
        int x = p.x + 1;
        int y = p.y;
        while (getPixelAt(x,y) != color_border && x < x_max)
        {
            painter->drawPoint(x,y);
            x++;
        }
        x_right = x-1;

        x = p.x-1;
        //y = p.y
        while (getPixelAt(x,y) != color_border && x >= 0)
        {
            painter->drawPoint(x,y);
            x--;
        }
        x_left = x+1;

        if (y < y_max)
        {
            findNext(myStack, x_left, x_right, y + 1);
        }
        if (y > 0)
        {
            findNext(myStack, x_left, x_right, y - 1);
        }

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }
    }
    this->update();

    /*while (!myStack.empty())
    {
        Point p = myStack.top();
        myStack.pop();
        painter->drawPoint(p.x,p.y);
        int x = p.x + 1;
        int y = p.y;
        while (getPixelAt(x,y) != color_border && x < x_max)
        {
            painter->drawPoint(x,y);
            x++;
        }
        x_right = x-1;
        x = p.x-1;
        while (getPixelAt(x,y) != color_border && x > 0)
        {
            painter->drawPoint(x,y);
            x--;
        }
        x_left = x+1;
        x = p.x;

        if (p.y < y_max-1)
        {
            y = p.y+1;
            find_next(myStack, x_left, x_right, y);
        }
        if (p.y > 1)
        {
            y = p.y - 1;
            find_next(myStack, x_left, x_right, y);
        }

        if (isDelay)
        {
            Sleep(delay);
            repaint();
        }
    }
    this->update();*/
}

void Canvas::fill_dots(int del)
{
    if (isDelay)
        delay = del;

    painter->setPen(color_shading);

    stack<Point> stck;
    Point z(xz, yz);
    stck.push(z);

    while(!stck.empty())
    {
        Point p = stck.top();
        stck.pop();
        int x = p.x;
        int y = p.y;
        painter->drawPoint(x,y);

        checkPoint(stck, x+1, y);
        checkPoint(stck, x-1, y);
        checkPoint(stck, x, y+1);
        checkPoint(stck, x, y-1);
        /*checkPoint(stck, x+1, y);
        checkPoint(stck, x-1, y);
        checkPoint(stck, x, y+1);
        checkPoint(stck, x, y-1);*/
        if (isDelay)
        {
            //Sleep(delay);
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

bool Canvas::zatravka()
{
    return isZatravka;
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
    xz = 0, yz = 0;
    isFirstPoint = true;
    isLocked = false;
    isZatravka = false;

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

void Canvas::DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end)
{
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

    painter->drawPoint(X, Y);
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
        painter->drawPoint(X, Y);
    }
}

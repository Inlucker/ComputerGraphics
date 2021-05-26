#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    linePen = QPen(Qt::red);
    cutterPen = QPen(Qt::black);
    rezPen = QPen(Qt::blue);
    setStyleSheet("background-color:white;");
    isDelay = true;

    color_line = QColor(Qt::red);
    color_cutter = QColor(Qt::black);
    color_rez = QColor(Qt::blue);

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
        double x = prev_x_line;
        double y = prev_y_line;
        if (event->modifiers() == Qt::ALT && !firstPointCheck())
        {
            x = event->x();
            if ((event->x() > prev_x_line && event->y() < prev_y_line) || (event->x() < prev_x_line && event->y() > prev_y_line))
                y = y - (x - prev_x_line);
            else
                y = y + (x - prev_x_line);
        }
        else if (event->modifiers() == Qt::CTRL && !firstPointCheck())
        {
            x = event->x();
        }
        else if (event->modifiers() == Qt::SHIFT && !firstPointCheck())
        {
            y = event->y();
        }
        else
        {
            x = event->x();
            y = event->y();
        }

        if (edgeFlag)
            addPoint(x, y);
        else
            setCuttuer(x, y);
        //addPoint(x, y);
    }
    else
    {
        isLMBPressed = false;
        if (event->button() == Qt::RightButton && rect().contains(event->pos()))
        {
            if (edgeFlag)
                setCuttuer(event->x(), event->y());
            else
                addPoint(event->x(), event->y());
        }
    }
}

void Canvas::setCutterPenColor(QColor color)
{
    color_cutter = color;
    cutterPen.setColor(color);
}

void Canvas::setLinePenColor(QColor color)
{
    color_line = color;
    linePen.setColor(color);
}

void Canvas::setRezColor(QColor color)
{
    color_rez = color;
    rezPen.setColor(color);
}

/*void Canvas::setDelay(bool val)
{
    isDelay = val;
}*/

void Canvas::addPoint(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    painter->setPen(linePen);
    plot(int_x, int_y);
    if (isFirstPointLine)
    {
        prev_x_line = int_x;
        prev_y_line = int_y;
        isFirstPointLine = false;
    }
    else
    {
        DrawLineBrezenheimFloat(prev_x_line, prev_y_line, int_x, int_y);
        lines.push_back(Line(Point(prev_x_line, prev_y_line), Point(int_x, int_y)));

        isFirstPointLine = true;
    }
    //prev_x_line = int_x;
    //prev_y_line = int_y;
    update();
}

void Canvas::setCuttuer(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    painter->setPen(cutterPen);
    plot(int_x, int_y);
    if (isFirstPointCutter)
    {
        prev_x_cutter = int_x;
        prev_y_cutter = int_y;
        isFirstPointCutter = false;
    }
    else
    {
        DrawLineBrezenheimFloat(prev_x_cutter, prev_y_cutter, int_x, prev_y_cutter);
        DrawLineBrezenheimFloat(int_x, prev_y_cutter, int_x, int_y);
        DrawLineBrezenheimFloat(int_x, int_y, prev_x_cutter, int_y);
        DrawLineBrezenheimFloat(prev_x_cutter, int_y, prev_x_cutter, prev_y_cutter);
        //cutter = Cutter(min(int_y, prev_y_cutter), min(int_x, prev_x_cutter), max(int_y, prev_y_cutter), max(int_x, prev_x_cutter));
        cutters.push_back(Cutter(min(int_y, prev_y_cutter), min(int_x, prev_x_cutter), max(int_y, prev_y_cutter), max(int_x, prev_x_cutter)));
        //painter->drawRect(QRect(prev_x_cutter, prev_y_cutter, int_x, int_y));

        isFirstPointCutter = true;
    }
    //prev_x_cutter = int_x;
    //prev_y_cutter = int_y;
    update();
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
        while (color != color_line && color != color_cutter && x <= x_right)
        {
            flag = true;
            x++;
            color = getPixelAt(x,y);
        }
        if (flag == true)
        {
            Point p(x, y);
            if (x == x_right && getPixelAt(x,y) != color_line && getPixelAt(x,y) != color_cutter)
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
        while ((color == color_line || color == color_cutter) && x < x_right)
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
        while (getPixelAt(x,y) != color_line && getPixelAt(x,y) != color_cutter && x <= x_right)
        {
            pushFlag = true;
            x++;
        }
        if (pushFlag)
        {
            stack.push(Point(x-1, y));
        }

        x++;
        while ((getPixelAt(x,y) == color_line || getPixelAt(x,y) == color_cutter) && x < x_right)
        {
            x++;
        }
    }
}

void Canvas::checkPoint(stack<Point> &stack, int x, int y)
{
    if (getPixelAt(x,y) != color_line && getPixelAt(x,y) != color_cutter)
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

bool Canvas::firstPointCheck()
{
    return isFirstPointLine && isFirstPointCutter;
}

bool Canvas::firstPointCutterCheck()
{
    return isFirstPointCutter;
}

int Canvas::linesSize()
{
    return lines.size();
}

int Canvas::cuttersSize()
{
    return cutters.size();
}

void Canvas::cut()
{
    cout << "cut" << endl;
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
    isFirstPointLine = true;
    isFirstPointCutter = true;
    isLocked = false;
    isZatravka = false;

    if (painter)
        delete painter;

    if (my_pixmap)
        delete my_pixmap;
    my_pixmap = new QPixmap(2000, 2000);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    //my_pixmap->fill(color_rez);

    painter = new QPainter(my_pixmap);
    painter->setPen(linePen);

    lines.clear();
    cutters.clear();

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

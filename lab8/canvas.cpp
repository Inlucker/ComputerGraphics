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
            setCutter(x, y);
        //addPoint(x, y);
    }
    else
    {
        isLMBPressed = false;
        if (event->button() == Qt::RightButton && rect().contains(event->pos()))
        {
            if (edgeFlag)
                setCutter(event->x(), event->y());
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
    prev_x_line = int_x;
    prev_y_line = int_y;
    //setupUpdate();
    update();
}

void Canvas::lock()
{
    if (!isLocked)
    {
        setCutter(x0, y0);
        isLocked = true;
        isFirstPointCutter = true;
    }
}

void Canvas::setCutter(double x, double y)
{
    if (!cutterSize() || !isLocked)
    {
        int int_x = round(x);
        int int_y = round(y);
        //QPainter painter(my_pixmap);
        painter->setPen(cutterPen);
        plot(int_x, int_y);
        if (isFirstPointCutter)
        {
            x0 = int_x;
            y0 = int_y;
            isFirstPointCutter = false;
            isLocked = false;
            cutter.insert(cutter.end(), Point(int_x, int_y));
        }
        else
        {
            cutter.insert(cutter.end(), Point(int_x, int_y));
            painter->drawLine(prev_x_cutter, prev_y_cutter, int_x, int_y);
        }
        prev_x_cutter = int_x;
        prev_y_cutter = int_y;
        update();
    }
}

/*void Canvas::setupUpdate()
{
    painter->setPen(linePen);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    for (auto line : lines)
        DrawLineBrezenheimFloat(line);

    if (canvas->locked())
    {
        painter->setPen(cutterPen);
        DrawLineBrezenheimFloat(cutter->left, cutter->top, cutter->right, cutter->top);
        DrawLineBrezenheimFloat(cutter->right, cutter->top, cutter->right, cutter->bottom);
        DrawLineBrezenheimFloat(cutter->right, cutter->bottom, cutter->left, cutter->bottom);
        DrawLineBrezenheimFloat(cutter->left, cutter->bottom, cutter->left, cutter->top);
    }
    update();
}*/

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

int Canvas::cutterSize()
{
    return cutter.size();
}

bool Canvas::locked()
{
    return isLocked;
}

/*void printBits (char T)
{
    string out = "";
    for (int i = 0; i < 8; i++)
    {
        //Проверяем старший бит)
        if (T & 0x80)
            out += "1";
        else
            out += "0";
        //Сдвигаем влево на 1 бит
        T = T << 1;

        if (i == 3)
            out += " ";
    }
    cout << out << endl;
}

char setBits(Cutter c, Point p)
{
    //cout << c.bottom << " " << c.top << endl;
    char T = 0b0000;

    if (p.x < c.left)
        T |= (1 << 3);
    if (p.x > c.right)
        T |= (1 << 2);
    if (p.y < c.bottom)
        T |= (1 << 1);
    if (p.y > c.top)
        T |= (1 << 0);

    return T;
}

char sumButs(char T)
{
    char S = 0b0;
    for (int i = 0; i < 8; i++)
    {
        if (T & 0x80)
        {
            S += 0b1;
            //S %= 0b10;
        }

        T = T << 1;
    }
    return S;
}

void Canvas::find_p(Point second_p, Point &R)
{
    int x_l = cutter->left;
    int x_r = cutter->right;
    int y_t = cutter->top;
    int y_b = cutter->bottom;

    int x1 = R.x;
    int y1 = R.y;
    int x2 = second_p.x;
    int y2 = second_p.y;

    double m = double(y2 - y1)/double(x2-x1);
    if (x1 <= x_l)
    {
        int y_p = round(m*double(x_l-x1)+double(y1));
        if (y_p >= y_b && y_p <= y_t)
        {
            R.x = x_l;
            R.y = y_p;
        }
    }
    else if (x1 >= x_r)
    {
        int y_p = round(m*double(x_r-x1)+double(y1));
        if (y_p >= y_b && y_p <= y_t)
        {
            R.x = x_r;
            R.y = y_p;
        }
    }

    if (m != 0)
    {
        if (y1 >= y_t)
        {
            int x_p = double(y_t-y1)/m+x1;
            if (x_p >= x_l && x_p <= x_r)
            {
                R.x = x_p;
                R.y = y_t;
            }
        }

        if (y1 <= y_b)
        {
            int x_p = double(y_b-y1)/m+x1;
            if (x_p >= x_l && x_p <= x_r)
            {
                R.x = x_p;
                R.y = y_b;
            }
        }
    }
}*/

void Canvas::cut()
{
    // lab7 cut
    /*painter->setPen(rezPen);
    int x_l = cutter->left;
    int x_r = cutter->right;
    int y_t = cutter->top;
    int y_b = cutter->bottom;

    painter->fillRect(QRect(x_l+1, y_b+1, x_r-x_l-1, y_t-y_b-1), QBrush(Qt::white));
    for (auto line : lines)
    {
        //int i = 0;

        int x1 = line.p1.x;
        int x2 = line.p2.x;
        int y1 = line.p1.y;
        int y2 = line.p2.y;

        double m = 1e30;

        char T1 = setBits(*cutter, line.p1);
        char T2 = setBits(*cutter, line.p2);
        char S1 = sumButs(T1);
        char S2 = sumButs(T2);

        if (!S1 && !S2) // Полностью видим
        {
            DrawLineBrezenheimFloat(line);
            continue;
        }

        char PL = T1 & T2;
        //cout << "PL = "; printBits(PL);
        if (PL) // Тривиально невидим
            continue;

        if (x2 != x1)
        {
            m = double(y2 - y1)/double(x2-x1);
            if (!S1) // Первая точка внутри
            {
                if (x2 <= x_l) // Пересечение с левой границей
                {
                    int y_p = round(m*double(x_l-x2)+double(y2));
                    if (y_p >= y_b && y_p <= y_t)
                    {
                        DrawLineBrezenheimFloat(x1, y1, x_l, y_p);
                        //DrawLineBrezenheimFloat(x1, y1, x_l, (m*(x_l-x2)+(y2)));
                        //painter->drawLine(x1, y1, x_l, m*(x_l-x2)+y2);
                        continue;
                    }
                }

                if (x2 >= x_r) // Пересечение с правой границей
                {
                    int y_p = round(m*double(x_r-x2)+double(y2));
                    if (y_p >= y_b && y_p <= y_t)
                    {
                        DrawLineBrezenheimFloat(x1, y1, x_r, y_p);
                        continue;
                    }
                }

                if (m != 0) //Отрезок не горизонтальный
                {
                    if (y2 >= y_t) // Пересечение с верхней границей
                    {
                        int x_p = double(y_t-y2)/m+x2;
                        if (x_p >= x_l && x_p <= x_r)
                        {
                            DrawLineBrezenheimFloat(x1, y1, x_p, y_t);
                            continue;
                        }
                    }

                    if (y2 <= y_b) // Пересечение с нижней границей
                    {
                        int x_p = double(y_b-y2)/m+x2;
                        if (x_p >= x_l && x_p <= x_r)
                        {
                            DrawLineBrezenheimFloat(x1, y1, x_p, y_b);
                            continue;
                        }
                    }
                }
            }

            if (!S2) // Вторая точка внутри
            {
                if (x1 <= x_l) // Пересечение с левой границей
                {
                    int y_p = round(m*double(x_l-x1)+double(y1));
                    if (y_p >= y_b && y_p <= y_t)
                    {
                        DrawLineBrezenheimFloat(x2, y2, x_l, y_p);
                        continue;
                    }
                }

                if (x1 >= x_r) // Пересечение с правой границей
                {
                    int y_p = round(m*double(x_r-x1)+double(y1));
                    if (y_p >= y_b && y_p <= y_t)
                    {
                        DrawLineBrezenheimFloat(x2, y2, x_r, y_p);
                        continue;
                    }
                }

                if (m != 0)
                {
                    if (y1 >= y_t) // Пересечение с верхней границей
                    {
                        int x_p = double(y_t-y1)/m+x1;
                        if (x_p >= x_l && x_p <= x_r)
                        {
                            DrawLineBrezenheimFloat(x2, y2, x_p, y_t);
                            continue;
                        }
                    }

                    if (y1 <= y_b) // Пересечение с нижней границей
                    {
                        int x_p = double(y_b-y1)/m+x1;
                        if (x_p >= x_l && x_p <= x_r)
                        {
                            DrawLineBrezenheimFloat(x2, y2, x_p, y_b);
                            continue;
                        }
                    }
                }
            }
        }
        else // Вертикальный отрезок
        {
            int x_p = x2;
            if (!S1) // Первая точка внутри
            {
                if (y2 >= y_t) // Пересечение с верхней границей
                {
                    //if (x_p >= x_l && x_p <= x_r)
                    //Проверка не нужна
                    DrawLineBrezenheimFloat(x1, y1, x_p, y_t);
                    continue;
                }

                if (y2 <= y_b) // Пересечение с нижней границей
                {
                    //if (x_p >= x_l && x_p <= x_r)
                    //Проверка не нужна
                    DrawLineBrezenheimFloat(x1, y1, x_p, y_b);
                    continue;
                }
            }

            if (!S2) // Вторая точка внутри
            {
                if (y1 >= y_t) // Пересечение с верхней границей
                {
                    //Проверка не нужна
                    DrawLineBrezenheimFloat(x2, y2, x_p, y_t);
                    continue;
                }

                if (y1 <= y_b) // Пересечение с нижней границей
                {
                    //Проверка не нужна
                    DrawLineBrezenheimFloat(x2, y2, x_p, y_b);
                    continue;
                }
            }
        }

        //нетривиальный случай
        if (x2 != x1)
        {
            Point R1 = line.p1;
            Point R2 = line.p2;
            find_p(line.p2, R1);
            find_p(line.p1, R2);
            //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            //cout << R1.x << " " << R1.y << " " << R2.x << " " << R2.y << endl;

            // На всякий случай :)
            if ((R1.x >= x_l && R1.x <= x_r) && (R2.x >= x_l && R2.x <= x_r) && (R1.y >= y_b && R1.y <= y_t) && (R2.y >= y_b && R2.y <= y_t))
            {
                DrawLineBrezenheimFloat(R1.x, R1.y, R2.x, R2.y);
                continue;
            }
        }


    }*/

    update();
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
    cutter.clear();

    update();
}


void Canvas::DrawLineBrezenheimFloat(Line l)
{
    DrawLineBrezenheimFloat(l.p1.x, l.p1.y, l.p2.x, l.p2.y);
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

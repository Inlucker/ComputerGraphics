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
    delete cutter;
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
    //painter->setPen(linePen);
    //plot(int_x, int_y);
    if (isFirstPointLine)
    {
        prev_x_line = int_x;
        prev_y_line = int_y;
        isFirstPointLine = false;
    }
    else
    {
        //DrawLineBrezenheimFloat(prev_x_line, prev_y_line, int_x, int_y);
        lines.push_back(Line(Point(prev_x_line, prev_y_line), Point(int_x, int_y)));

        isFirstPointLine = true;
    }
    //prev_x_line = int_x;
    //prev_y_line = int_y;
    setupUpdate();
    //update();
}

void Canvas::setCutter(double x, double y)
{
    int int_x = round(x);
    int int_y = round(y);
    //painter->setPen(cutterPen);
    //plot(int_x, int_y);
    if (isFirstPointCutter)
    {
        prev_x_cutter = int_x;
        prev_y_cutter = int_y;
        isFirstPointCutter = false;
    }
    else
    {
        /*DrawLineBrezenheimFloat(prev_x_cutter, prev_y_cutter, int_x, prev_y_cutter);
        DrawLineBrezenheimFloat(int_x, prev_y_cutter, int_x, int_y);
        DrawLineBrezenheimFloat(int_x, int_y, prev_x_cutter, int_y);
        DrawLineBrezenheimFloat(prev_x_cutter, int_y, prev_x_cutter, prev_y_cutter);*/

        //cutters.push_back(Cutter(min(int_y, prev_y_cutter), min(int_x, prev_x_cutter), max(int_x, prev_x_cutter), max(int_y, prev_y_cutter)));
        //cutters.push_back(Cutter(max(int_y, prev_y_cutter), min(int_x, prev_x_cutter), max(int_x, prev_x_cutter), min(int_y, prev_y_cutter)));
        cutter = new Cutter(max(int_y, prev_y_cutter), min(int_x, prev_x_cutter), max(int_x, prev_x_cutter), min(int_y, prev_y_cutter));
        //painter->drawRect(QRect(prev_x_cutter, prev_y_cutter, int_x, int_y));

        isFirstPointCutter = true;
    }
    //prev_x_cutter = int_x;
    //prev_y_cutter = int_y;
    setupUpdate();
    //update();
}

void Canvas::setupUpdate()
{
    painter->setPen(linePen);
    my_pixmap->fill(QColor(0, 0, 0, 0));
    for (auto line : lines)
        DrawLineBrezenheimFloat(line);

    if (cutter->isExist)
    {
        painter->setPen(cutterPen);
        DrawLineBrezenheimFloat(cutter->left, cutter->top, cutter->right, cutter->top);
        DrawLineBrezenheimFloat(cutter->right, cutter->top, cutter->right, cutter->bottom);
        DrawLineBrezenheimFloat(cutter->right, cutter->bottom, cutter->left, cutter->bottom);
        DrawLineBrezenheimFloat(cutter->left, cutter->bottom, cutter->left, cutter->top);
    }
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
    if (cutter)
        return 1;
    else
        return 0;
}

//not mine
void set_bits(int xmax, int xmin, int ymax, int ymin, int x, int y, int *arr)
{
    arr[3] = x < xmin ? 1:0;
    arr[2] = x > xmax ? 1:0;
    arr[1] = y < ymin ? 1:0;
    arr[0] = y > ymax ? 1:0;
}

int get_sum(int *arr, int n)
{
    int sum = 0;
    for(int i = 0;i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int get_p(int *arr1, int *arr2, int n)
{
    int sum = 0;
    for(int i = 0;i < n; i++)
    {
        sum += arr1[i]*arr2[i];
    }
    return sum;
}

void Canvas::cut2()
{
    painter->setPen(rezPen);

    /*int xmax = x_up>x_down?x_up:x_down;
    int xmin = x_up>x_down?x_down:x_up;
    int ymax = y_up>y_down?y_up:y_down;
    int ymin = y_up>y_down?y_down:y_up;*/

    int xmax = cutter->right;
    int xmin = cutter->left;
    //int ymax = cutters[0].top;
    //int ymin = cutters[0].bottom;
    int ymax = cutter->bottom;
    int ymin = cutter->top;

    qDebug() << xmin << xmax << ymax << ymin;
    for (size_t j = 0; j < lines.size(); j++)
    {
        int x1 = lines[j].p1.x;
        int x2 = lines[j].p2.x;
        int y1 = lines[j].p1.y;
        int y2 = lines[j].p2.y;
        Point p1(x1,y1);
        Point p2(x2,y2);
        //qDebug() << p1 << p2;
        int i = 1;
        double eps = sqrt(2);
        int T1[4], T2[4];
        int s1,s2;
        while(1)
        {
            set_bits(xmax,xmin,ymax,ymin,p1.x,p1.y,T1);
            set_bits(xmax,xmin,ymax,ymin,p2.x,p2.y,T2);
            s1 = get_sum(T1, 4);
            s2 = get_sum(T2, 4);

            if (s1 == 0 && s2 == 0)
            {
                qDebug() <<"полностью видим";
                cout << "полностью видим" << endl;
                //draw_line(p1.x,p1.y,p2.x,p2.y);
                DrawLineBrezenheimFloat(p1.x, p2.x, p1.y, p2.y);
                break;
            }
            int p = get_p(T1,T2, 4);
            if (p)
            {
                qDebug() <<"тривиально невидим";
                break;
            }

            Point r = p1;
            if (i > 2)
            {
                 int pr = get_p(T1,T2, 4);
                 if (pr)
                     break;
                 //qDebug() << p1 << p2;
                 //draw_line(p1.x(),p1.y(),p2.x(),p2.y());
                 DrawLineBrezenheimFloat(p1.x, p2.x, p1.y, p2.y);
                 break;
            }
            if (s2 == 0)
            {
                p1 = p2;
                p2 = r;
                i++;
                continue;
            }


            while (fabs(p1.x - p2.x) > eps || fabs(p1.y - p2.y) > eps)
            {

                Point pm;
                pm.x = ((p1.x+p2.x)/2);
                pm.y =((p1.y+p2.y)/2);

                Point tmp = p1;
                p1 = pm;
                set_bits(xmax,xmin,ymax,ymin,p1.x,p1.y,T1);
                int pr = get_p(T1,T2, 4);
                if (pr != 0)
                {
                    p1 = tmp;
                    p2 = pm;
                }
            }
            p1 = p2;
            p2 = r;
            i++;
        }
    }
    painter->setPen(linePen);
    update();
}

void printBits (char T)
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

void Canvas::cut()
{
    painter->setPen(rezPen);
    int x_l = cutter->left;
    int x_r = cutter->right;
    int y_t = cutter->top;
    int y_b = cutter->bottom;

    painter->fillRect(QRect(x_l+1, y_b+1, x_r-x_l-1, y_t-y_b-1), QBrush(Qt::white));
    for (auto line : lines)
    {
        int i = 0;

        int x1 = line.p1.x;
        int x2 = line.p2.x;
        int y1 = line.p1.y;
        int y2 = line.p2.y;

        double m = 1e30;

        char T1 = setBits(*cutter, line.p1);
        char T2 = setBits(*cutter, line.p2);
        char S1 = sumButs(T1);
        char S2 = sumButs(T2);
        cout << "T1 = "; printBits(T1);
        cout << "T2 = "; printBits(T2);
        cout << "S1 = "; printBits(S1);
        cout << "S2 = "; printBits(S2);
        if (!S1 && !S2) //полностью видим
        {
            DrawLineBrezenheimFloat(line);
            continue;
        }

        char PL = T1 & T2;
        cout << "PL = "; printBits(PL);
        if (PL) //тривиально невидим
            continue;

        if (x2 != x1)
        {
            m = double(y2 - y1)/double(x2-x1);
            if (!S1)
            {
                //i = 2;
                if (x2 <= x_l)
                {
                    DrawLineBrezenheimFloat(x1, y1, x_l, round(m*double(x_l-x2)+double(y2)));
                    //DrawLineBrezenheimFloat(x1, y1, x_l, (m*(x_l-x2)+(y2)));
                    //painter->drawLine(x1, y1, x_l, m*(x_l-x2)+y2);
                    continue;
                }

                //if (m = 0)
                if (x2 >= x_r)
                {
                    DrawLineBrezenheimFloat(x1, y1, x_r, round(m*double(x_r-x2)+double(y2)));
                    continue;
                }

                if (m != 0)
                {
                    if (y2 >= y_t)
                    {
                        int x_p = double(y_t-y2)/m+x2;
                        DrawLineBrezenheimFloat(x1, y1, x_p, y_t);
                        continue;
                    }

                    if (y2 <= y_b)
                    {
                        int x_p = double(y_b-y2)/m+x2;
                        DrawLineBrezenheimFloat(x1, y1, x_p, y_b);
                        continue;
                    }
                }
            }

            if (!S2)
            {
                //i = 2;
                if (x1 <= x_l)
                {
                    DrawLineBrezenheimFloat(x2, y2, x_l, round(m*double(x_l-x1)+double(y1)));
                    //DrawLineBrezenheimFloat(x1, y1, x_l, (m*(x_l-x2)+(y2)));
                    //painter->drawLine(x1, y1, x_l, m*(x_l-x2)+y2);
                    continue;
                }

                if (x1 >= x_r)
                {
                    DrawLineBrezenheimFloat(x2, y2, x_r, round(m*double(x_r-x1)+double(y1)));
                    continue;
                }

                //if (m = 0)
                if (m != 0)
                {
                    if (y1 >= y_t)
                    {
                        int x_p = double(y_t-y1)/m+x1;
                        DrawLineBrezenheimFloat(x2, y2, x_p, y_t);
                        continue;
                    }

                    if (y1 <= y_b)
                    {
                        int x_p = double(y_b-y1)/m+x1;
                        DrawLineBrezenheimFloat(x2, y2, x_p, y_b);
                        continue;
                    }
                }
            }
        }
        else // vertical
        {
            int x_p = x2;
            if (!S1)
            {
                if (y2 >= y_t)
                {
                    //if (x_p >= x_l && x_p <= x_r)
                    DrawLineBrezenheimFloat(x1, y1, x_p, y_t);
                    continue;
                }

                if (y2 <= y_b)
                {
                    //if (x_p >= x_l && x_p <= x_r)
                    DrawLineBrezenheimFloat(x1, y1, x_p, y_b);
                    continue;
                }
            }

            if (!S2)
            {
                if (y1 >= y_t)
                {
                    DrawLineBrezenheimFloat(x2, y2, x_p, y_t);
                    continue;
                }

                if (y1 <= y_b)
                {
                    DrawLineBrezenheimFloat(x2, y2, x_p, y_b);
                    continue;
                }
            }
        }

        //???????????????????
        /*i++;
        if (i > 2)
            continue;*/


    }

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
    cutter->isExist = 0;

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

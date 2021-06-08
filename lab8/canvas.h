#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "windows.h"
#include <cmath>
#include <QKeyEvent>
#include <stack>

#include <iostream>

using namespace std;

/*struct Point
{
    int x;
    int y;
    Point() = default;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    double get_x() const {return this->x;}
    double get_y() const {return this->y;}
    void setY(double _y){this->y = _y;}
    void setX(double _x){this->x = _x;}
};

struct Line
{
    Point p1;
    Point p2;
    Line() = default;
    Line(int x1, int x2, int y1, int y2)
    {
        p1 = Point(x1, y1);
        p2 = Point(x2, y2);
    }
    Line(Point _p1, Point _p2)
    {
        p1 = _p1;
        p2 = _p2;
    }
};*/

struct Line
{
    Line(): x1(0), x2(0), y1(0), y2(0) {};
    Line(int x1, int x2, int y1, int y2): x1(x1), x2(x2), y1(y1), y2(y2){}
    int x1;
    int x2;
    int y1;
    int y2;
};

typedef struct Point point_t;
struct Point
{
    Point():X(0),Y(0){}
    Point(double x, double y):X(x),Y(y){}
    double X;
    double Y;

    double x() const {return this->X;}
    double y() const {return this->Y;}
    void setY(double y){this->Y = y;}
    void setX(double x){this->X = x;}

    point_t& operator =(const point_t &p)
    {
        this->X = p.x();
        this->Y = p.y();
        return *this;
    }
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void setCutterPenColor(QColor color);
    void setLinePenColor(QColor color);
    void setRezColor(QColor color);
    //void setDelay(bool val);
    void addPoint(double x, double y);
    void lock();
    void setCutter(double x, double y);

    //void setupUpdate();

    bool firstPointCheck();
    bool firstPointCutterCheck();
    int linesSize();
    int cutterSize();
    bool locked();

    bool isConvex(int &obhod);
    void alg(Point p1, Point p2, int obhod);
    void cut();
    void clean();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    int x0, y0;
    int prev_x_line, prev_y_line;
    int prev_x_cutter, prev_y_cutter;
    int xz, yz;

    bool edgeFlag;

private:
    QPainter *painter = nullptr;
    QPixmap *my_pixmap = nullptr;
    QPen cutterPen;
    QPen linePen;
    QPen rezPen;

    QColor color_line;
    QColor color_cutter;
    QColor color_rez;

    bool isDelay;
    int delay;

    bool isFirstPointLine;
    bool isFirstPointCutter;
    bool isLocked;
    bool isZatravka;

    vector<Line> lines;
    //vector<Point> cutter;
    vector<Line> cutter;

    bool isLMBPressed;

private:
    void plot(int x, int y);

    void DrawLineBrezenheimFloat(Line l);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H

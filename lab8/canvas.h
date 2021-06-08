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

struct Point
{
    Point() = default;
    Point(double _x, double _y)
    {
        X = _x;
        Y = _y;
    }
    double X;
    double Y;

    Point& operator =(const Point &p)
    {
        this->X = p.X;
        this->Y = p.Y;
        return *this;
    }
};


struct Line
{
    Line(): x1(0), x2(0), y1(0), y2(0) {};
    Line(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        p1 = Point(x1, y1);
        p2 = Point(x2, y2);
    }
    Line(Point _p1, Point _p2)
    {
        p1 = _p1;
        p2 = _p2;
        x1 = p1.X;
        y1 = p1.Y;
        x2 = p2.X;
        y2 = p2.Y;
    }
    Point p1;
    Point p2;
    int x1;
    int x2;
    int y1;
    int y2;
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void setCutterPenColor(QColor color);
    void setLinePenColor(QColor color);
    void setRezColor(QColor color);
    void addPoint(double x, double y);
    void lock();
    void setCutter(double x, double y);

    void cutterUpdate();
    void setupUpdate();

    bool firstPointCheck();
    bool firstPointLineCheck();
    bool firstPointCutterCheck();
    int linesSize();
    int cutterSize();
    bool locked();

    bool isConvex(int &obhod);
    void alg(Line line, int obhod);
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

private:
    void plot(int x, int y);

    void DrawLineBrezenheimFloat(Line l);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H

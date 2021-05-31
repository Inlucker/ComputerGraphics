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

struct Point
{
    int x;
    int y;
    Point() = default;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

struct Line
{
    Point p1;
    Point p2;
    Line() = default;
    Line(Point _p1, Point _p2)
    {
        p1 = _p1;
        p2 = _p2;
    }
};

struct Cutter
{
    int top;
    int left;
    int right;
    int bottom;
    bool isExist;
    Cutter()
    {
        isExist = false;
    }
    Cutter(int _top, int _left, int _right, int _bottom)
    {
        top = _top;
        left = _left;
        right = _right;
        bottom = _bottom;
        isExist = true;
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
    void setCutter(double x, double y);

    void setupUpdate();

    bool firstPointCheck();
    bool firstPointCutterCheck();
    int linesSize();
    int cuttersSize();
    void cut2();
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

    //std::vector<Edge> edges;
    vector<Line> lines;
    //vector<Cutter> cutters;
    Cutter *cutter;

    bool isLMBPressed;

private:
    void plot(int x, int y);
    QColor getPixelAt(int x, int y);

    void find_next(stack<Point> &stack, int &x_left, int &x_right, const int &y);
    void findNext(stack<Point> &stack, int x_left, int x_right, int y);
    void checkPoint(stack<Point> &stack, int x, int y);


    void DrawLineBrezenheimFloat(Line l);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);

};

#endif // CANVAS_H

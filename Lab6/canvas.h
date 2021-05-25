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

//typedef struct Point point_t;
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

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void setMainPenColor(QColor color);
    void setSemiPenColor(QColor color);
    void setBackgroundColor(QColor color);
    void setDelay(bool val);
    void addPoint(double x, double y);
    void setZatravka(double x, double y);
    void lock();
    void fill_lines(int del);
    void fill_dots(int del);
    bool firstPointCheck();
    bool locked();
    bool zatravka();
    void clean();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    int x0, y0;
    int prev_x, prev_y;
    int xz, yz;

    bool edgeFlag;

private:
    QPainter *painter = nullptr;
    QPixmap *my_pixmap = nullptr;
    QPen mainPen;
    QPen semiPen;
    QPen bgPen;

    QColor color_border;
    QColor color_shading;
    QColor color_background;

    bool isDelay;
    int delay;

    bool isFirstPoint;
    bool isLocked;
    bool isZatravka;

    //std::vector<Edge> edges;

    bool isLMBPressed;

private:
    void plot(int x, int y);
    QColor getPixelAt(int x, int y);

    void find_next(stack<Point> &stack, int &x_left, int &x_right, const int &y);
    void checkPoint(stack<Point> &stack, int x, int y);

    void DrawLineBrezenheimFloat(int X_start, int X_end, int Y_start, int Y_end);

};

#endif // CANVAS_H

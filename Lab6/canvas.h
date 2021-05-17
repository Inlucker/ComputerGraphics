#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "windows.h"
#include <cmath>
#include <QKeyEvent>

#include <iostream>

using namespace std;

class Edge
{
public:
    Edge(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }
    int x1;
    int y1;
    int x2;
    int y2;

    bool isExtremum(Edge edge2)
    {
        bool rez = false;
        //local min
        if (this->y1 <= this->y2 && this->y1 <= edge2.y1)
            rez = true;
        //local max
        if (this->y1 >= this->y2 && this->y1 >= edge2.y1)
            rez = true;
        return rez;
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
    void lock();
    void fill(int del);
    bool firstPointCheck();
    bool locked();
    int getEdgesNumber();
    void clean();

protected:
   virtual void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:
    int x0, y0;
    int prev_x, prev_y;

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

    std::vector<Edge> edges;

private:
    void plot(int x, int y);
    QColor getPixelAt(int x, int y);

};

#endif // CANVAS_H

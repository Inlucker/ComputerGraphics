#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <math.h>
#include <map>

using namespace std;

class Canvas : public QWidget
{
    //Q_OBJECT

public:
    Canvas();
    ~Canvas();

private:
    float rotate_x(float x0, float y0);
    float rotate_y(float x0, float y0);
    void rotate(float *x0, float *y0);
    void draw_ellipse(QPainter *painter, const float xc, const float yc, float a, float b);

protected:
    void paintEvent(QPaintEvent *);

public:
    float float_x = 0;
    float float_y = 0;
    int x = 0;
    int y = 0;
    //float size = 1 * 1.5;
    float size_x = 1;
    float size_y = 1;

    float angle = 0;
    float radians = 0;
    float rotate_center_x = 0;
    float rotate_center_y = 0;

private:
    QPainter painter;

};

#endif // CANVAS_H

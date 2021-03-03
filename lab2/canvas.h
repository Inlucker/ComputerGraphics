#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <math.h>
#include <map>

#define GAP 100

#define NOTHING -1
#define CREATE 0
#define MOVE 1
#define SCALE 2
#define ROTATE 3

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
    void scale(float *x0, float *y0);
    void draw_ellipse(QPainter *painter, const float xc, const float yc, float a, float b);

protected:
    void paintEvent(QPaintEvent *);

public:
    float base_size = 1;

    float float_x[GAP];
    float float_y[GAP];
    int x[GAP];
    int y[GAP];

    float size_center_x[GAP];
    float size_center_y[GAP];
    float size_x[GAP];
    float size_y[GAP];

    float angle[GAP];
    float radians = 0;
    float rotate_center_x[GAP];
    float rotate_center_y[GAP];
    int cur_id = 0;
    int first_id = 0;

    bool is_visible[GAP];

    int transofrmation[GAP];

private:
    QPainter painter;

};

#endif // CANVAS_H

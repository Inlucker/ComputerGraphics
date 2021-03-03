#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <QList>
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
    //void scale(float *x0, float *y0);
    //void draw_ellipse(QPainter *painter, const float xc, const float yc, float a, float b);

    QPolygonF *create_ellipse(const float xc, const float yc, const float a, const float b, int *dots_number);

protected:
    void paintEvent(QPaintEvent *);

public:
    float float_x[GAP];
    float float_y[GAP];
    int x[GAP];
    int y[GAP];

    float size_center_x[GAP];
    float size_center_y[GAP];
    float size_x[GAP];
    float size_y[GAP];

    float angle[GAP];
    float rotate_center_x[GAP];
    float rotate_center_y[GAP];
    int cur_id = 0;
    int first_id = 0;

    bool is_visible[GAP];

    int transofrmation[GAP];

private:
    //Base params
    float base_size = 1;
    float rad_x = base_size * 25;
    float rad_y = base_size * 25;

    //Angle params
    float radians = 0;

    //Head params
    QPolygonF *head = NULL;
    int head_dots_number = 0;

    float head_center_x = x[cur_id];
    float head_center_y = y[cur_id] - rad_y * 2;
    int head_size_x = rad_x;
    int head_size_y = rad_y;

    //Set ears params
    QPointF ear1_dots[3];
    QPointF ear2_dots[3];

    float ear_offset = base_size * 5;
    float ear_height = base_size * 15;
    float ear_width = base_size * 7;
    float delta_y1 = sqrt((1 - pow((ear_offset) / rad_x, 2)) * pow(rad_y, 2));
    float delta_y2 = sqrt((1 - pow((ear_width * 2 + ear_offset) / rad_x, 2)) * pow(rad_y, 2));

    //Set eyes params
    QPolygonF *eye1 = NULL;
    int eye1_dots_number = 0;
    QPolygonF *eye2 = NULL;
    int eye2_dots_number = 0;

    float eye_width = base_size * 10;
    float eye_height = base_size * 5;
    int eye_size_x = base_size * 5;
    int eye_size_y = base_size * 5;
    float eye1_x = head_center_x - eye_width;
    float eye1_y = head_center_y - eye_height;
    float eye2_x = head_center_x + eye_width;
    float eye2_y = head_center_y - eye_height;

    //Set whiskers params
    QPointF wiskers_dots[7];

    float len = base_size * 35;
    float wisk_height = base_size * 10;
    float wisk_center_x = x[cur_id];
    float wisk_center_y = y[cur_id] - rad_y * 2 + wisk_height;
    float wisk_x1 = wisk_center_x - len;
    float wisk_x2 = wisk_center_x + len;
    float wisk_y1 = wisk_center_y;
    float wisk_y2 = wisk_center_y + wisk_height;
    float wisk_y3 = wisk_center_y - wisk_height;

    //Set body params
    QPolygonF *body;
    int body_dots_number = 0;

    int body_width = rad_x;
    int body_height = rad_y * 2;
    float body_center_x = x[cur_id];
    float body_center_y = y[cur_id] + rad_y;

    QPainter painter;

};

#endif // CANVAS_H

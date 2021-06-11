#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include <iostream>

using namespace std;

double func1(double x, double z);

double func2(double x, double z);

double func3(double x, double z);

double func4(double x, double z);

class Canvas : public QWidget
{
public:
    typedef vector<double> point_3d;
    typedef double matrix[4][4];

    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    /*void setCutterPenColor(QColor color);
    void setLinePenColor(QColor color);
    void setRezColor(QColor color);

    void clean();*/

    void clear();
    void set_bg(const QColor &color);
    void set_fg(const QColor &color);
    void rotate_trans_matrix(matrix rotate_matrix);
    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);
    void set_scale(double sc);
    void trans_point(point_3d &point);
    bool is_visible(double x, double y);
    bool draw_point(double x, double y, vector<double> &hh, vector<double> &lh);
    void draw_horizon_part(point_3d p1, point_3d p2, vector<double> &hh, vector<double> &lh);
    void draw_horizon(double (*func)(double x, double z), vector<double> &hh, vector<double> &lh, double fr, double to, double step, double z);
    void draw(double (*f)(double x, double z), double x_min, double x_max, double x_step, double z_min, double z_max, double z_step);


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public:

private:
    /*QPainter *painter = nullptr;
    QPixmap *my_pixmap = nullptr;
    QPen cutterPen;
    QPen linePen;
    QPen rezPen;

    QColor color_line;
    QColor color_cutter;
    QColor color_rez;*/

    QColor bg = QColor(255, 255, 255);
    QColor fg = QColor(0, 0, 0);
    QRect field;
    matrix trans_matrix = { { 1, 0, 0, 0}, { 0, 1, 0, 0}, { 0, 0, 1, 0}, { 0, 0, 0, 1} };
    double scale = 50;

    QImage image;
    QPainter painter;


private:
    /*void plot(int x, int y);
    void DrawLineBrezenheimFloat(int X_start, int Y_start, int X_end, int Y_end);*/

};

#endif // CANVAS_H

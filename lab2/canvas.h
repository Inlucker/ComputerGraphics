#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <math.h>

using namespace std;

class Canvas : public QWidget
{
    //Q_OBJECT

public:
    Canvas();
    ~Canvas();

protected:
    void paintEvent(QPaintEvent *);

public:
    float float_x = 0;
    float float_y = 0;
    int x = 0;
    int y = 0;
    float size = 1 * 1.5;

private:
    QPainter painter;

};

#endif // CANVAS_H

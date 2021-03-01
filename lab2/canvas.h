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
    double x = 0;
    double y = 0;
    int size = 5;

private:
    QPainter painter;

};

#endif // CANVAS_H

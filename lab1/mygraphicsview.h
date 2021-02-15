#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

#define MAX_POINT_NUMBER 100
#define TRIANGLE_POINTS_NUMBER 3

class MyGraphicsView : public QWidget
{
public:
    MyGraphicsView();
    ~MyGraphicsView();
    void clearPoints();

protected:
    void paintEvent(QPaintEvent *);

public:
    int x[MAX_POINT_NUMBER];
    int y[MAX_POINT_NUMBER];
    int x_rez[TRIANGLE_POINTS_NUMBER];
    int y_rez[TRIANGLE_POINTS_NUMBER];
};

#endif // MYGRAPHICSVIEW_H

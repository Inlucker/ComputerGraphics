#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <map>
#include <iostream>

using namespace std;

#define MAX_POINT_NUMBER 100
#define TRIANGLE_POINTS_NUMBER 3
#define HEIGHT 0//(height())

class MyGraphicsView : public QWidget
{
public:
    MyGraphicsView();
    ~MyGraphicsView();
    void clearPoints();

protected:
    void paintEvent(QPaintEvent *);

public:
    pair<int, int> *points_mn = NULL;
    int points_number = -1;
    //int x[MAX_POINT_NUMBER];
    //int y[MAX_POINT_NUMBER];
    /*int x_rez[TRIANGLE_POINTS_NUMBER];
    int y_rez[TRIANGLE_POINTS_NUMBER];*/

    bool rez = false;

    int rez_x1 = 0;
    int rez_y1 = 0;
    int rez_x2 = 0;
    int rez_y2 = 0;
    int rez_x3 = 0;
    int rez_y3 = 0;

    int id1 = -1;
    int id2 = -2;
    int id3 = -3;

private:
    QPainter painter;
};

#endif // MYGRAPHICSVIEW_H

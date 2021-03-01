#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <iostream>

using namespace std;

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas();
    ~Canvas();

protected:
    void paintEvent(QPaintEvent *);

private:
    QPainter painter;

};

#endif // CANVAS_H

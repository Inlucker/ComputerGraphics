#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void setMainPenColor(QColor color);
    void setSemiPenColor(QColor color);
    void setDelay(bool val);
    void addPoint(double x, double y);
    void lock();
    void clean();

protected:
    void paintEvent(QPaintEvent *);

public:
    int x0, y0;
    int prev_x, prev_y;

private:
    //QPainter painter;
    QPen mainPen;
    QPen semiPen;
    QPixmap my_pixmap;
    bool delay;
    bool isFirstPoint;
    bool isLocked;

private:
    void plot(QPainter *p, int x, int y);

};

#endif // CANVAS_H

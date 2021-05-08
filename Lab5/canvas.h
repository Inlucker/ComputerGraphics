#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <vector>

class Edge
{
public:
    int x1;
    int y1;
    int x2;
    int y2;
};

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
    void fill();
    void clean();

protected:
    void paintEvent(QPaintEvent *);

public:
    int x0, y0;
    int prev_x, prev_y;

private:
    QPainter *painter = nullptr;
    QPixmap *my_pixmap = nullptr;
    QPen mainPen;
    QPen semiPen;
    bool delay;
    bool isFirstPoint;
    bool isLocked;

    std::vector<Edge> edges;

private:
    void plot(int x, int y);

};

#endif // CANVAS_H

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <vector>

class Edge
{
public:
    Edge(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }
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
    void setBackgroundColor(QColor color);
    void setDelay(bool val);
    void addPoint(double x, double y);
    void lock();
    void fill();
    bool locked();
    int getEdgesNumber();
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


    QColor color_border;
    QColor color_shading;
    QColor color_background;

    bool delay;
    bool isFirstPoint;
    bool isLocked;

    std::vector<Edge> edges;

private:
    void plot(int x, int y);
    QColor getPixelAt(int x, int y);

};

#endif // CANVAS_H

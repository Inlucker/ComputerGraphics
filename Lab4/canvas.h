#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

enum Algoritm
{
    NO_ALG,
    CANON,
    PARAM,
    BREZENHAM,
    MIDPOINT,
    STANDART
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void drawCircle();
    void drawEllipse();
    void drawCircleSpectre();
    void drawEllipseSpectre();
    void setPenColor(QColor color);
    void clean();

    double getTime(float length, Algoritm alg);
    //int getStages(int angle);

protected:
    void paintEvent(QPaintEvent *);

public:
    Algoritm method;// = CANON;
    int X_center;
    int Y_center;
    int Radius;
    int a;
    int b;
    int RadiusStart;
    int RadiusEnd;
    int FiguresNumber;
    int a_start;
    int b_start;
    int stepA;
    int stepB;

    //QColor background_color;

private:
    //QPainter painter;
    QPen pen;
    QPixmap my_pixmap;
    //algroitm metod;

private:
    void plot(QPainter *p, int x, int y);
    //void DrawPoint(QPainter *p, bool steep, int x, int y);
    void DrawCircleCanon(int X_c, int Y_c, int R);
    void DrawEllipseCanon(int X_c, int Y_c, int A, int B);
    void DrawCircleParam(int X_c, int Y_c, int R);
    void DrawEllipseParam(int X_c, int Y_c, int A, int B);
    void DrawCircleBrezenham(int X_c, int Y_c, int R);
    void DrawEllipseBrezenham(int X_c, int Y_c, int A, int B);
    void DrawCircleMidpoint(int X_c, int Y_c, int R);
    void DrawEllipseMidpoint(int X_c, int Y_c, int A, int B);

    void DrawCircleQt(int X_c, int Y_c, int R);
    void DrawEllipseQt(int X_c, int Y_c, int A, int B);
    //void draw_point(QPoint);
    //void clean();

};

#endif // CANVAS_H

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

enum Algroitm
{
    NO_ALG,
    DIG_DIF_ANALIZ,
    BREZENHAM_FLOAT,
    BREZENHAM_INT,
    BREZENHAM_STEP_REM,
    VU,
    STANDART
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void draw();
    void drawSpectre();
    void setPenColor(QColor color);
    void clean();

protected:
    void paintEvent(QPaintEvent *);

public:
    //bool isClean;// = false;
    Algroitm method;// = DIG_DIF_ANALIZ;
    int X_start;
    int Y_start;
    int X_end;
    int Y_end;
    double angle;
    double length;

    //QColor background_color;

private:
    //QPainter painter;
    QPen pen;
    QPixmap my_pixmap;
    //algroitm metod;

private:
    void plot(QPainter *p, int x, int y, int c);
    void DrawPoint(QPainter *p, bool steep, int x, int y, int c);
    void DrawLineDGA(int X_start, int X_end, int Y_start, int Y_end);
    void DrawLineBrezenheimInt(int X_start, int X_end, int Y_start, int Y_end);
    void DrawLineBrezenheimFloat(int X_start, int X_end, int Y_start, int Y_end);
    void DrawLineBrezenheimSmooth(int X_start, int X_end, int Y_start, int Y_end);
    void DrawLineVu(int X_start, int X_end, int Y_start, int Y_end);
    void DrawLineQt(int X_start, int X_end, int Y_start, int Y_end);
    //void draw_point(QPoint);
    //void clean();

};

#endif // CANVAS_H

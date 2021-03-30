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
    void setPenColor(QColor color);
    void clean();

protected:
    void paintEvent(QPaintEvent *);

public:
    //bool isClean;// = false;
    Algroitm method;// = DIG_DIF_ANALIZ;
    double X_start;
    double Y_start;
    double X_end;
    double Y_end;

    //QColor background_color;

private:
    //QPainter painter;
    QPen pen;
    QPixmap my_pixmap;
    //algroitm metod;

private:
    //void draw_point(QPoint);
    //void clean();

};

#endif // CANVAS_H

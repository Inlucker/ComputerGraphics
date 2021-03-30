#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

enum Algroitm
{
    NO_ALG,
    DIG_DIF_ANALIZ,
    CLEAN,
};

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void setPenColor(QColor color);

protected:
    void paintEvent(QPaintEvent *);

public:
    Algroitm method;
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
    void clean();

};

#endif // CANVAS_H

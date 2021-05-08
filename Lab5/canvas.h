#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void clean();

protected:
    void paintEvent(QPaintEvent *);

private:
    //QPainter painter;
    QPen mainPen;
    QPen semiPen;
    QPixmap my_pixmap;

};

#endif // CANVAS_H

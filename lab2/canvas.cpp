#include "canvas.h"

Canvas::Canvas()
{
    //setGeometry(QRect(0, 0, 600, 600));
    //setStyleSheet("background-color:grey;");
}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent *event)
{
    //setGeometry(QRect(0, 0, 600, 600));
    //setStyleSheet("background-color:grey;");
    //создание рисовальщика
    painter.begin(this); //захват контекста

    double x_center = width() / 2;
    double y_center = height() / 2;
    //cout << x_center << " " << y_center << endl;
    cout << this->width() << " " << this->height() << endl;

    painter.translate(x_center, y_center);

    painter.end();//освобождение контекста
}

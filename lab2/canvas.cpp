#include "canvas.h"

Canvas::Canvas()
{
    //setGeometry(QRect(0, 0, 600, 600));
    setStyleSheet("background-color:white;");
}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent *event)
{
    //Создание рисовальщика
    painter.begin(this); //Захват контекста

    float x_center = width() / 2;
    float y_center = height() / 2;
    //cout << x_center << " " << y_center << endl;
    //cout << this->width() << " " << this->height() << endl;

    painter.translate(x_center, y_center);

    //Set radius by size
    int rad = size * 25;

    //Set head params
    int head_center_x = x;
    int head_center_y = y - rad * 2;
    QPoint head_center = QPoint(head_center_x, head_center_y);
    int head_size = rad;
    //Draw head
    painter.drawEllipse(head_center, head_size, head_size);

    //Set ears params
    int ear_offset = size * 5;
    int ear_height = size * 15;
    int ear_width = size * 7;
    int delta_y1 = int(rad - sqrt(pow(rad, 2) - pow(ear_offset, 2)));
    int delta_y2 = int(rad - sqrt(pow(rad, 2) - pow(ear_width * 2 + ear_offset, 2)));
    QPoint ear11 = QPoint(head_center_x - ear_offset, head_center_y - rad + delta_y1);
    QPoint ear21 = QPoint(head_center_x + ear_offset, head_center_y - rad + delta_y1);
    QPoint ear12 = QPoint(head_center_x - ear_offset - ear_width, head_center_y - head_size - ear_height);
    QPoint ear22 = QPoint(head_center_x + ear_offset + ear_width, head_center_y - head_size - ear_height);
    QPoint ear13 = QPoint(head_center_x - ear_offset - ear_width * 2, head_center_y - rad + delta_y2);
    QPoint ear23 = QPoint(head_center_x + ear_offset + ear_width * 2, head_center_y - rad + delta_y2);
    //Draw ears
    painter.drawLine(ear11, ear12);
    painter.drawLine(ear12, ear13);

    painter.drawLine(ear21, ear22);
    painter.drawLine(ear22, ear23);

    //Set eyes params
    int eye_width = size * 10;
    int eye_height = size * 5;
    int eye_size = size * 5;
    QPoint eye_center1 = QPoint(head_center_x - eye_width, head_center_y - eye_height);
    QPoint eye_center2 = QPoint(head_center_x + eye_width, head_center_y - eye_height);
    //Draw eyes
    painter.drawEllipse(eye_center1, eye_size, eye_size);
    painter.drawEllipse(eye_center2, eye_size, eye_size);

    //Set whiskers params
    int len = size * 35;
    int wisk_height = size * 10;
    int wisk_center_x = x;
    int wisk_center_y = y - rad * 2 + wisk_height;
    QPoint wisk_center = QPoint(wisk_center_x, wisk_center_y);
    //Draw cat's whiskers
    QLine whiskers1 = QLine(wisk_center, QPoint(wisk_center_x - len, wisk_center_y));
    QLine whiskers2 = QLine(wisk_center, QPoint(wisk_center_x - len, wisk_center_y + wisk_height));
    QLine whiskers3 = QLine(wisk_center, QPoint(wisk_center_x - len, wisk_center_y - wisk_height));
    QLine whiskers4 = QLine(wisk_center, QPoint(wisk_center_x + len, wisk_center_y));
    QLine whiskers5 = QLine(wisk_center, QPoint(wisk_center_x + len, wisk_center_y + wisk_height));
    QLine whiskers6 = QLine(wisk_center, QPoint(wisk_center_x + len, wisk_center_y - wisk_height));
    painter.drawLine(whiskers1);
    painter.drawLine(whiskers2);
    painter.drawLine(whiskers3);
    painter.drawLine(whiskers4);
    painter.drawLine(whiskers5);
    painter.drawLine(whiskers6);

    //Set body params
    //int b_center_x = x;
    //int b_center_y = y + rad;
    QPoint body_center = QPoint(x, y + rad);
    //Draw body
    painter.drawEllipse(body_center, rad, rad * 2);
    //painter.drawEllipse(QPoint(x, y), rad, rad);
    //painter.drawEllipse(QPoint(x, y + rad * 2), rad, rad);

    painter.end(); //Освобождение контекста
}

#include "canvas.h"

#define PI 3.14159265

Canvas::Canvas()
{
    //setGeometry(QRect(0, 0, 600, 600));
    setStyleSheet("background-color:white;");
}

Canvas::~Canvas()
{

}

float Canvas::rotate_x(float x0, float y0)
{
    //cout << x0 << " " << y0 << " " << x_center << " " << y_center << " " << radians << endl;
    //return x_center + (x - x_center) * cos(radians) + (y - y_center) * sin(radians);
    float rez = rotate_center_x + (x0 - rotate_center_x) * cos(radians) + (y0 - rotate_center_y) * sin(radians);
    //cout << "x1 = " << x_center << " + (" << x0 << " - " << x_center << ") * " << cos(radians) << " + (" << y0 << " - " << y_center << ") * " << sin(radians) << " = " << rez << endl;
    //cout << "x1 = " << x_center << " + (" << y0 << " - " << y_center << ") = " << rez << endl;
    return rez;
}

float Canvas::rotate_y(float x0, float y0)
{
    //cout << x0 << " " << y0 << " " << x_center << " " << y_center << " " << radians << endl;
    //return y_center - (x - x_center) * sin(radians) + (y - y_center) * cos(radians);
    float rez = rotate_center_y - (x0 - rotate_center_x) * sin(radians) + (y0 - rotate_center_y) * cos(radians);
    //cout << "y1 = " << y_center << " - (" << x0 << " - " << x_center << ") * " << sin(radians) << " + (" << y0 << " - " << y_center << ") * " << cos(radians) << " = " << rez << endl;
    //cout << "y1 = " << y_center << " - (" << x0 << " - " << x_center << ") = " << rez << endl;
    return rez;
}

void Canvas::rotate(float *x0, float *y0)
{
    float new_x = rotate_x(*x0, *y0);
    float new_y = rotate_y(*x0, *y0);
    *x0 = new_x;
    *y0 = new_y;
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
    //painter.drawPoint(0, 0);
    //painter.rotate(angle);

    //Set radians by angle
    radians = angle * PI / 180;

    //Set radius by size
    //float rad = size * 25;
    float rad_x = size_x * 25;
    float rad_y = size_y * 25;

    //Set head params
    float head_center_x = x;
    float head_center_y = y - rad_y * 2;
    rotate(&head_center_x, &head_center_y);
    QPointF head_center = QPointF(head_center_x, head_center_y);
    //int head_size = rad;
    int head_size_x = rad_x;
    int head_size_y = rad_y;
    //Draw head
    painter.drawEllipse(head_center, head_size_x, head_size_y);

    //Set ears params
    float ear_offset = size_x * 5;
    float ear_height = size_y * 15;
    float ear_width = size_x * 7;

    float delta_y1 = sqrt((1 - pow((ear_offset) / rad_x, 2)) * pow(rad_y, 2));
    float delta_y2 = sqrt((1 - pow((ear_width * 2 + ear_offset) / rad_x, 2)) * pow(rad_y, 2));

    QPointF ear1_dots[3];
    QPointF ear2_dots[3];
    float x11 = head_center_x - ear_offset;
    float y11 = head_center_y - delta_y1;
    ear1_dots[0].setX(x11);
    ear1_dots[0].setY(y11);

    float x21 = head_center_x + ear_offset;
    float y21 = head_center_y - delta_y1;
    ear2_dots[0].setX(x21);
    ear2_dots[0].setY(y21);

    float x12 = head_center_x - ear_offset - ear_width;
    float y12 = head_center_y - head_size_y - ear_height;
    ear1_dots[1].setX(x12);
    ear1_dots[1].setY(y12);

    float x22 = head_center_x + ear_offset + ear_width;
    float y22 = head_center_y - head_size_y - ear_height;
    ear2_dots[1].setX(x22);
    ear2_dots[1].setY(y22);

    float x13 = head_center_x - ear_offset - ear_width * 2;
    float y13 = head_center_y - delta_y2;
    ear1_dots[2].setX(x13);
    ear1_dots[2].setY(y13);

    float x23 = head_center_x + ear_offset + ear_width * 2;
    float y23 = head_center_y - delta_y2;
    ear2_dots[2].setX(x23);
    ear2_dots[2].setY(y23);

    rotate(&x11, &y11);
    rotate(&x21, &y21);
    rotate(&x12, &y12);
    rotate(&x22, &y22);
    rotate(&x13, &y13);
    rotate(&x23, &y23);

    for (int i = 0; i < 3; i++)
    {
        float tmp_x = ear1_dots[i].x();
        float tmp_y = ear1_dots[i].y();
        rotate(&tmp_x, &tmp_y);
        ear1_dots[i].setX(tmp_x);
        ear1_dots[i].setY(tmp_y);

        tmp_x = ear2_dots[i].x();
        tmp_y = ear2_dots[i].y();
        rotate(&tmp_x, &tmp_y);
        ear2_dots[i].setX(tmp_x);
        ear2_dots[i].setY(tmp_y);
    }
    //Draw ears
    for (int i = 0; i < 2; i++)
    {
        painter.drawLine(ear1_dots[i], ear1_dots[i + 1]);
        painter.drawLine(ear2_dots[i], ear2_dots[i + 1]);
    }

    //Set eyes params
    float eye_width = size_x * 10;
    float eye_height = size_y * 5;
    //int eye_size = size * 5;
    int eye_size_x = size_x * 5;
    int eye_size_y = size_y * 5;
    float eye1_x = head_center_x - eye_width;
    float eye1_y = head_center_y - eye_height;
    float eye2_x = head_center_x + eye_width;
    float eye2_y = head_center_y - eye_height;
    rotate(&eye1_x, &eye1_y);
    QPointF eye_center1 = QPointF(eye1_x, eye1_y);
    QPointF eye_center2 = QPointF(eye2_x, eye2_y);
    //Draw eyes
    painter.drawEllipse(eye_center1, eye_size_x, eye_size_y);
    painter.drawEllipse(eye_center2, eye_size_x, eye_size_y);

    //Set whiskers params DONE
    float len = size_x * 35;
    float wisk_height = size_y * 10;
    float wisk_center_x = x;
    float wisk_center_y = y - rad_y * 2 + wisk_height;

    float wisk_x1 = wisk_center_x - len;
    float wisk_x2 = wisk_center_x + len;
    float wisk_y1 = wisk_center_y;
    float wisk_y2 = wisk_center_y + wisk_height;
    float wisk_y3 = wisk_center_y - wisk_height;
    QPointF wiskers_dots[7];
    wiskers_dots[0].setX(wisk_center_x); wiskers_dots[0].setY(wisk_center_y);
    wiskers_dots[1].setX(wisk_x1); wiskers_dots[1].setY(wisk_y1);
    wiskers_dots[2].setX(wisk_x1); wiskers_dots[2].setY(wisk_y2);
    wiskers_dots[3].setX(wisk_x1); wiskers_dots[3].setY(wisk_y3);
    wiskers_dots[4].setX(wisk_x2); wiskers_dots[4].setY(wisk_y1);
    wiskers_dots[5].setX(wisk_x2); wiskers_dots[5].setY(wisk_y2);
    wiskers_dots[6].setX(wisk_x2); wiskers_dots[6].setY(wisk_y3);
    for (int i = 0; i < 7; i++)
    {
        float tmp_x = wiskers_dots[i].x();
        float tmp_y = wiskers_dots[i].y();
        rotate(&tmp_x, &tmp_y);
        wiskers_dots[i].setX(tmp_x);
        wiskers_dots[i].setY(tmp_y);
    }
    //QPointF wisk_center = QPointF(wisk_center_x, wisk_center_y);
    //Draw cat's whiskers DONE
    for (int i = 1; i < 7; i++)
    {
        painter.drawLine(wiskers_dots[0], wiskers_dots[i]);
    }

    //Set body params
    float body_center_x = x;
    float body_center_y = y + rad_y;
    int body_width = rad_x;
    int body_height = rad_y * 2;
    QPointF body_center = QPointF(body_center_x, body_center_y);
    //Draw body
    painter.drawEllipse(body_center, body_width, body_height);
    //painter.drawEllipse(QPointF(x, y), rad, rad);
    //painter.drawEllipse(QPointF(x, y + rad * 2), rad, rad);


    pair<float, float> square[4];
    float a = -100;
    float b = 100;
    //float c = (b + a) / 2;
    square[0] = make_pair(float(a), float(a));
    square[1] = make_pair(float(b), float(a));
    square[2] = make_pair(float(b), float(b));
    square[3] = make_pair(float(a), float(b));
    /*for (int i = 0; i < 4; i++)
    {
        cout << i << ": X = " << square[i].first << "; Y = " << square[i].second << ";" << endl;
    }
    cout << endl;*/

    //cout << endl;
    for (int i = 0; i < 4; i++)
    {
        //cout << i << ": X = " << square[i].first << " -> ";
        //cout << i << ": X = " << square[i].first << "; Y = " << square[i].second << endl;
        /*float new_x = rotate_x(square[i].first, square[i].second, c, c, angle * PI / 180);
        float new_y = rotate_y(square[i].first, square[i].second, c, c, angle * PI / 180);
        square[i].first = new_x;
        //cout << square[i].first << endl;
        //cout << i << ": Y = " << square[i].second << " -> ";
        square[i].second = new_y;*/
        //cout << square[i].second << endl;

        rotate(&square[i].first, &square[i].second);
    }
    //cout << endl;

    /*for (int i = 0; i < 4; i++)
    {
        cout << i << ": X = " << square[i].first << "; Y = " << square[i].second << ";" << endl;
    }
    cout << endl;*/

    for (int i = 0; i < 3; i++)
    {
        painter.drawLine(square[i].first, square[i].second, square[i + 1].first, square[i + 1].second);
    }
    painter.drawLine(square[3].first, square[3].second, square[0].first, square[0].second);

    painter.end(); //Освобождение контекста
}

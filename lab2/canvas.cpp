#include "canvas.h"

Canvas::Canvas()
{
    setStyleSheet("background-color:white;");

    float_x[0] = 0;
    float_y[0] = 0;
    x[0] = 0;
    y[0] = 0;

    size_center_x[0] = 0;
    size_center_y[0] = 0;
    size_x[0] = 1;
    size_y[0] = 1;

    angle[0] = 0;
    rotate_center_x[0] = 0;
    rotate_center_y[0] = 0;
    cur_id = 0;
    first_id = cur_id;

    is_visible[0] = false;

    transofrmation[0] = NOTHING;

    reverse = false;

    //-----------------------SET PARAMS START-----------------------//
    //Base params
    base_size = 1;
    rad_x = base_size * 25;
    rad_y = base_size * 25;

    //Angle params
    radians = 0;

    //Head params
    head = NULL;
    head_size_x = rad_x;
    head_size_y = rad_y;

    //Set ears params
    ear_offset = base_size * 5;
    ear_height = base_size * 15;
    ear_width = base_size * 7;

    delta_y1 = sqrt((1 - pow((ear_offset) / rad_x, 2)) * pow(rad_y, 2));
    delta_y2 = sqrt((1 - pow((ear_width * 2 + ear_offset) / rad_x, 2)) * pow(rad_y, 2));

    //Set eyes params
    eye_width = base_size * 10;
    eye_height = base_size * 5;
    eye_size_x = base_size * 5;
    eye_size_y = base_size * 5;

    //Set whiskers params
    len = base_size * 35;
    wisk_height = base_size * 10;

    //Set body params
    body_width = rad_x;
    body_height = rad_y * 2;
    //------------------------SET PARAMS END------------------------//
}

Canvas::~Canvas()
{

}

float Canvas::rotate_x(float x0, float y0)
{
    float rez = rotate_center_x[cur_id] + (x0 - rotate_center_x[cur_id]) * cos(radians) + (y0 - rotate_center_y[cur_id]) * sin(radians);
    return rez;
}

float Canvas::rotate_y(float x0, float y0)
{
    float rez = rotate_center_y[cur_id] - (x0 - rotate_center_x[cur_id]) * sin(radians) + (y0 - rotate_center_y[cur_id]) * cos(radians);
    return rez;
}

void Canvas::rotate(float *x0, float *y0)
{
    float new_x = rotate_x(*x0, *y0);
    float new_y = rotate_y(*x0, *y0);
    *x0 = new_x;
    *y0 = new_y;
}

/*void Canvas::scale(float *x0, float *y0)
{
    //float new_x = size_x[cur_id] * (*x0) + size_center_x[cur_id] * (1 - size_x[cur_id]);
    //float new_y = size_y[cur_id] * (*y0) + size_center_y[cur_id] * (1 - size_y[cur_id]);
    float new_x = size_x[cur_id] * (*x0) + x[cur_id] * (1 - size_x[cur_id]);
    float new_y = size_y[cur_id] * (*y0) + y[cur_id] * (1 - size_y[cur_id]);
    *x0 = new_x;
    *y0 = new_y;
}*/

/*void Canvas::draw_ellipse(QPainter *painter, const float xc, const float yc, float a, float b)
{
    float i = - a;
    while (i <= a)
    {
        float x0 = xc + i;
        float y0 = yc + sqrt((1 - (pow(i/a, 2))) * pow(b, 2));
        //cout << i << ": " << x0 << " " << y0 << endl;
        rotate(&x0, &y0);
        scale(&x0, &y0);
        QPointF cur_dot = QPointF(x0, y0);
        painter->drawPoint(cur_dot);

        x0 = xc + i;
        y0 = yc - sqrt((1 - (pow(i/a, 2))) * pow(b, 2));
        rotate(&x0, &y0);
        scale(&x0, &y0);
        cur_dot.setX(x0);
        cur_dot.setY(y0);
        painter->drawPoint(cur_dot);
        i += 1.0 / size_x[cur_id];
    }
    i = - b;
    while (i <= b)
    {
        float y0 = yc + i;
        float x0 = xc + sqrt((1 - (pow(i/b, 2))) * pow(a, 2));
        //cout << i << ": " << x0 << " " << y0 << endl;
        rotate(&x0, &y0);
        scale(&x0, &y0);
        QPointF cur_dot = QPointF(x0, y0);
        //cout << i << ": " << int(cur_dot.x()) << " " << int(cur_dot.y()) << endl;
        painter->drawPoint(cur_dot);

        y0 = yc + i;
        x0 = xc - sqrt((1 - (pow(i/b, 2))) * pow(a, 2));
        rotate(&x0, &y0);
        scale(&x0, &y0);
        cur_dot.setX(x0);
        cur_dot.setY(y0);
        painter->drawPoint(cur_dot);
        i += 1.0 / size_y[cur_id];
    }
}*/

QPolygonF* Canvas::create_ellipse(const float xc, const float yc, const float a, const float b, int *dots_number)
{
    QPolygonF *new_ellipse = new QPolygonF;
    *dots_number = 0;
    float i = - a;
    while (i <= a)
    {
        float x0 = xc + i;
        float y0 = yc + sqrt((1 - (pow(i/a, 2))) * pow(b, 2));
        QPointF cur_dot = QPointF(x0, y0);
        new_ellipse->append(cur_dot);
        *dots_number = *dots_number + 1;
        i += 0.1;
    }
    i = a;
    while (i >= - a)
    {
        float x0 = xc + i;
        float y0 = yc - sqrt((1 - (pow(i/a, 2))) * pow(b, 2));
        QPointF cur_dot = QPointF(x0, y0);
        new_ellipse->append(cur_dot);
        *dots_number = *dots_number + 1;
        i -= 0.1;
    }
    return new_ellipse;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    //Создание рисовальщика
    painter.begin(this); //Захват контекста

    float x_center = width() / 2;
    float y_center = height() / 2;
    //cout << width() << " " << height() << endl;
    //cout << x_center << " " << y_center << endl;
    //cout << this->width() << " " << this->height() << endl;

    painter.translate(x_center, y_center);
    //painter.drawPoint(0, 0); //Проверка центра координат

    if (is_visible[cur_id])
    {
        switch (transofrmation[cur_id])
        {
            case CREATE:
            {
                if (!reverse)
                {
                //HEAD
                {
                    head_center_x = x[cur_id];
                    head_center_y = y[cur_id] - rad_y * 2;

                    head = create_ellipse(head_center_x, head_center_y, head_size_x, head_size_y, &head_dots_number);
                    //cout << head_dots_number << endl;
                }

                //EARS
                {
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
                }

                //EYES
                {
                    eye1_x = head_center_x - eye_width;
                    eye1_y = head_center_y - eye_height;
                    eye2_x = head_center_x + eye_width;
                    eye2_y = head_center_y - eye_height;

                    eye1 = create_ellipse(eye1_x, eye1_y, eye_size_x, eye_size_y, &eye1_dots_number);
                    //cout << eye1_dots_number << endl;
                    eye2 = create_ellipse(eye2_x, eye2_y, eye_size_x, eye_size_y, &eye2_dots_number);
                    //cout << eye2_dots_number << endl;
                }

                //WHISKERS
                {
                    wisk_center_x = x[cur_id];
                    wisk_center_y = y[cur_id] - rad_y * 2 + wisk_height;
                    wisk_x1 = wisk_center_x - len;
                    wisk_x2 = wisk_center_x + len;
                    wisk_y1 = wisk_center_y;
                    wisk_y2 = wisk_center_y + wisk_height;
                    wisk_y3 = wisk_center_y - wisk_height;

                    wiskers_dots[0].setX(wisk_center_x); wiskers_dots[0].setY(wisk_center_y);
                    wiskers_dots[1].setX(wisk_x1); wiskers_dots[1].setY(wisk_y1);
                    wiskers_dots[2].setX(wisk_x1); wiskers_dots[2].setY(wisk_y2);
                    wiskers_dots[3].setX(wisk_x1); wiskers_dots[3].setY(wisk_y3);
                    wiskers_dots[4].setX(wisk_x2); wiskers_dots[4].setY(wisk_y1);
                    wiskers_dots[5].setX(wisk_x2); wiskers_dots[5].setY(wisk_y2);
                    wiskers_dots[6].setX(wisk_x2); wiskers_dots[6].setY(wisk_y3);
                }

                //BODY
                {
                    body_center_x = float_x[cur_id];
                    body_center_y = float_y[cur_id] + rad_y;

                    body = create_ellipse(body_center_x, body_center_y, body_width, body_height, &body_dots_number);
                    //cout << body_dots_number << endl;
                }
                }
            }
            case MOVE:
            {
                if (reverse)
                {
                    cur_id++;
                    float_x[cur_id] *= -1;
                    float_y[cur_id] *= -1;
                }

                //HEAD
                QPolygonF ellipse = *head;
                for (int i = 0; i < head_dots_number; i++)
                {
                    QPointF tmp = ellipse[i];
                    //cout << float(tmp.x()) << " " << float(tmp.y()) << endl;
                    (*head)[i].setX(tmp.x() + float_x[cur_id]);
                    (*head)[i].setY(tmp.y() + float_y[cur_id]);
                }

                //EARS
                for (int i = 0; i < 3; i++)
                {
                    ear1_dots[i].setX(ear1_dots[i].x() + float_x[cur_id]);
                    ear1_dots[i].setY(ear1_dots[i].y() + float_y[cur_id]);

                    ear2_dots[i].setX(ear2_dots[i].x() + float_x[cur_id]);
                    ear2_dots[i].setY(ear2_dots[i].y() + float_y[cur_id]);
                }

                //EYES
                {
                    QPolygonF ellipse = *eye1;
                    for (int i = 0; i < eye1_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*eye1)[i].setX(tmp.x() + float_x[cur_id]);
                        (*eye1)[i].setY(tmp.y() + float_y[cur_id]);
                    }
                    ellipse = *eye2;
                    for (int i = 0; i < eye2_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*eye2)[i].setX(tmp.x() + float_x[cur_id]);
                        (*eye2)[i].setY(tmp.y() + float_y[cur_id]);
                    }
                }

                //WHISKERS
                for (int i = 0; i < 7; i++)
                {
                    wiskers_dots[i].setX(wiskers_dots[i].x() + float_x[cur_id]);
                    wiskers_dots[i].setY(wiskers_dots[i].y() + float_y[cur_id]);
                }

                //BODY
                {
                    QPolygonF ellipse = *body;
                    for (int i = 0; i < body_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*body)[i].setX(tmp.x() + float_x[cur_id]);
                        (*body)[i].setY(tmp.y() + float_y[cur_id]);
                    }
                }

                if (reverse)
                {
                    cur_id--;
                }
            }
            case SCALE:
            {
                if (reverse)
                {
                    cur_id++;
                    size_x[cur_id] = 1 / size_x[cur_id];
                    size_y[cur_id] = 1 / size_y[cur_id];
                }

                //HEAD
                {
                    QPolygonF ellipse = *head;
                    for (int i = 0; i < head_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*head)[i].setX(size_x[cur_id] * tmp.x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                        (*head)[i].setY(size_y[cur_id] * tmp.y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                    }
                }

                //EARS
                for (int i = 0; i < 3; i++)
                {
                    ear1_dots[i].setX(size_x[cur_id] * ear1_dots[i].x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                    ear1_dots[i].setY(size_y[cur_id] * ear1_dots[i].y() + size_center_y[cur_id] * (1 - size_y[cur_id]));

                    ear2_dots[i].setX(size_x[cur_id] * ear2_dots[i].x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                    ear2_dots[i].setY(size_y[cur_id] * ear2_dots[i].y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                }

                //EYES
                {
                    QPolygonF ellipse = *eye1;
                    for (int i = 0; i < eye1_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*eye1)[i].setX(size_x[cur_id] * tmp.x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                        (*eye1)[i].setY(size_y[cur_id] * tmp.y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                    }
                    ellipse = *eye2;
                    for (int i = 0; i < eye2_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*eye2)[i].setX(size_x[cur_id] * tmp.x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                        (*eye2)[i].setY(size_y[cur_id] * tmp.y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                    }
                }

                //WHISKERS
                for (int i = 0; i < 7; i++)
                {
                    wiskers_dots[i].setX(size_x[cur_id] * wiskers_dots[i].x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                    wiskers_dots[i].setY(size_y[cur_id] * wiskers_dots[i].y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                }

                //BODY
                {
                    QPolygonF ellipse = *body;
                    for (int i = 0; i < body_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        (*body)[i].setX(size_x[cur_id] * tmp.x() + size_center_x[cur_id] * (1 - size_x[cur_id]));
                        (*body)[i].setY(size_y[cur_id] * tmp.y() + size_center_y[cur_id] * (1 - size_y[cur_id]));
                    }
                }

                if (reverse)
                {
                    cur_id--;
                }
            }
            case ROTATE:
            {
                if (reverse)
                {
                    cur_id++;
                    angle[cur_id] *= -1;
                }

                //HEAD
                {
                    //Set radians by angle
                    radians = angle[cur_id] * PI / 180;
                    QPolygonF ellipse = *head;
                    for (int i = 0; i < head_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        float new_x = tmp.x();
                        float new_y = tmp.y();
                        rotate(&new_x, &new_y);

                        (*head)[i].setX(new_x);
                        (*head)[i].setY(new_y);
                    }
                }

                //EARS
                for (int i = 0; i < 3; i++)
                {
                    float new_x = ear1_dots[i].x();
                    float new_y = ear1_dots[i].y();
                    rotate(&new_x, &new_y);
                    ear1_dots[i].setX(new_x);
                    ear1_dots[i].setY(new_y);

                    new_x = ear2_dots[i].x();
                    new_y = ear2_dots[i].y();
                    rotate(&new_x, &new_y);
                    ear2_dots[i].setX(new_x);
                    ear2_dots[i].setY(new_y);
                }

                //EYES
                {
                    QPolygonF ellipse = *eye1;
                    for (int i = 0; i < eye1_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        float new_x = tmp.x();
                        float new_y = tmp.y();
                        rotate(&new_x, &new_y);
                        (*eye1)[i].setX(new_x);
                        (*eye1)[i].setY(new_y);
                    }
                    ellipse = *eye2;
                    for (int i = 0; i < eye2_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        float new_x = tmp.x();
                        float new_y = tmp.y();
                        rotate(&new_x, &new_y);
                        (*eye2)[i].setX(new_x);
                        (*eye2)[i].setY(new_y);
                    }
                }

                //WHISKERS
                for (int i = 0; i < 7; i++)
                {
                    float new_x = wiskers_dots[i].x();
                    float new_y = wiskers_dots[i].y();
                    rotate(&new_x, &new_y);
                    wiskers_dots[i].setX(new_x);
                    wiskers_dots[i].setY(new_y);
                }

                //BODY
                {
                    QPolygonF ellipse = *body;
                    for (int i = 0; i < body_dots_number; i++)
                    {
                        QPointF tmp = ellipse[i];
                        float new_x = tmp.x();
                        float new_y = tmp.y();
                        rotate(&new_x, &new_y);
                        (*body)[i].setX(new_x);
                        (*body)[i].setY(new_y);
                    }
                }

                if (reverse)
                {
                    cur_id--;
                }
            }
            default:
            {
                //nothing
            }
        }
        //--------------------------DRAW START--------------------------//
        //Draw head
        painter.drawPolygon(*head);

        //Draw ears
        for (int i = 0; i < 2; i++)
        {
            painter.drawLine(ear1_dots[i], ear1_dots[i + 1]);
            painter.drawLine(ear2_dots[i], ear2_dots[i + 1]);
        }

        //Draw eyes
        painter.drawPolygon(*eye1);
        painter.drawPolygon(*eye2);

        //Draw cat's whiskers
        for (int i = 1; i < 7; i++)
        {
            painter.drawLine(wiskers_dots[0], wiskers_dots[i]);
        }

        //Draw body
        painter.drawPolygon(*body);
        //---------------------------DRAW END---------------------------//
    }
    painter.end(); //Освобождение контекста
}

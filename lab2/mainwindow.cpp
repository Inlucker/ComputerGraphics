#include "mainwindow.h"
#include "ui_mainwindow.h"

#define EPS 1e-4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    canvas = new Canvas();
    ui->gridLayout->addWidget(canvas);

    ui->x_start->setText("0");
    ui->y_start->setText("0");
    ui->x_move->setText("0");
    ui->y_move->setText("0");
    ui->x_size_center->setText("0");
    ui->y_size_center->setText("0");
    ui->x_size->setText("1.0");
    ui->y_size->setText("1.0");

    ui->x_rotate_center->setText("0");
    ui->y_rotate_center->setText("0");
    ui->rotate_angle->setText("0");
    ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");

    connect(ui->get_coords_info, SIGNAL(triggered()), this, SLOT(on_get_coords_info_clicked())); // Обработчик удаления записи
}

MainWindow::~MainWindow()
{
    delete ui;
}

float MainWindow::rotate_x(float x0, float y0, float xc, float yc, float radians)
{
    float rez = xc + (x0 - xc) * cos(radians) + (y0 - yc) * sin(radians);
    return rez;
}

float MainWindow::rotate_y(float x0, float y0, float xc, float yc, float radians)
{
    float rez = yc - (x0 - xc) * sin(radians) + (y0 - yc) * cos(radians);
    return rez;
}

void MainWindow::rotate(float *x0, float *y0, float xc, float yc, float radians)
{
    float new_x = rotate_x(*x0, *y0, xc, yc, radians);
    float new_y = rotate_y(*x0, *y0, xc, yc, radians);
    *x0 = new_x;
    *y0 = new_y;
}

void MainWindow::on_create_btn_clicked()
{
    bool isXFloat = false;
    float x = ui->x_start->text().toFloat(&isXFloat);
    bool isYFloat = false;
    float y = ui->y_start->text().toFloat(&isYFloat);
    if (isXFloat && isYFloat)
    {
        //int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
        {
            canvas->first_id++;
            if (canvas->first_id >= GAP)
                canvas->first_id = 0;
        }

        center_x = x;
        center_y = y;

        canvas->transofrmation[canvas->cur_id] = CREATE;
        canvas->reverse = false;

        canvas->float_x[canvas->cur_id] = x;
        canvas->float_y[canvas->cur_id] = y;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->size_center_x[canvas->cur_id] = 0;
        canvas->size_center_y[canvas->cur_id] = 0;
        canvas->size_x[canvas->cur_id] = 1;
        canvas->size_y[canvas->cur_id] = 1;
        canvas->angle[canvas->cur_id] = 0;
        canvas->rotate_center_x[canvas->cur_id] = 0;
        canvas->rotate_center_y[canvas->cur_id] = 0;
        canvas->is_visible[canvas->cur_id] = true;
        canvas->update();
    }
    else if (!isXFloat && !isYFloat)
    {
        QMessageBox::information(this, "Error", "X и Y должны быть вещественными числами");
    }
    else if (!isXFloat)
    {
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");
    }
    else if (!isYFloat)
    {
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");
    }
    if (!canvas->is_visible[canvas->cur_id])
        ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");
    else
        ui->coords_label->setText(tr("Текущее состояние:\nКоординаты центра:\nX: %1 Y: %2").arg(center_x).arg(center_y));
}

void MainWindow::on_move_btn_clicked()
{
    bool isXFloat = false;
    float x = ui->x_move->text().toFloat(&isXFloat);
    bool isYFloat = false;
    float y = ui->y_move->text().toFloat(&isYFloat);
    if (isXFloat && isYFloat)
    {
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
        {
            canvas->first_id++;
            if (canvas->first_id >= GAP)
                canvas->first_id = 0;
        }

        center_x += x;
        center_y += y;

        canvas->transofrmation[canvas->cur_id] = MOVE;
        canvas->reverse = false;

        canvas->float_x[canvas->cur_id] = x;
        canvas->float_y[canvas->cur_id] = y;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        //Без изменений
        canvas->size_center_x[canvas->cur_id] = 0;
        canvas->size_center_y[canvas->cur_id] = 0;
        canvas->size_x[canvas->cur_id] = 1;
        canvas->size_y[canvas->cur_id] = 1;
        canvas->angle[canvas->cur_id] = 0;
        canvas->rotate_center_x[canvas->cur_id] = 0;
        canvas->rotate_center_y[canvas->cur_id] = 0;
        canvas->is_visible[canvas->cur_id] = canvas->is_visible[prev_id];
        canvas->update();
    }
    else if (!isXFloat && !isYFloat)
    {
        QMessageBox::information(this, "Error", "X и Y должны быть вещественными числами");
    }
    else if (!isXFloat)
    {
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");
    }
    else if (!isYFloat)
    {
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");
    }
    if (!canvas->is_visible[canvas->cur_id])
        ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");
    else
        ui->coords_label->setText(tr("Текущее состояние:\nКоординаты центра:\nX: %1 Y: %2").arg(center_x).arg(center_y));
}

void MainWindow::on_change_size_btn_clicked()
{
    bool isXcFloat = false;
    float xc = ui->x_size_center->text().toFloat(&isXcFloat);
    bool isYcFloat = false;
    float yc = ui->y_size_center->text().toFloat(&isYcFloat);

    bool isKxFloat = false;
    float kx = ui->x_size->text().toFloat(&isKxFloat);
    bool isKyFloat = false;
    float ky = ui->y_size->text().toFloat(&isKyFloat);
    if (isXcFloat && isYcFloat &&isKxFloat && isKyFloat)
    {
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
        {
            canvas->first_id++;
            if (canvas->first_id >= GAP)
                canvas->first_id = 0;
        }

        center_x = kx * center_x + xc * (1 - kx);
        center_y = ky * center_y + yc * (1 - ky);

        canvas->transofrmation[canvas->cur_id] = SCALE;
        canvas->reverse = false;

        canvas->size_center_x[canvas->cur_id] = xc;
        canvas->size_center_y[canvas->cur_id] = yc;
        canvas->size_x[canvas->cur_id] = kx;
        canvas->size_y[canvas->cur_id] = ky;
        //Без изменений
        canvas->float_x[canvas->cur_id] = 0;
        canvas->float_y[canvas->cur_id] = 0;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->angle[canvas->cur_id] = 0;
        canvas->rotate_center_x[canvas->cur_id] = 0;
        canvas->rotate_center_y[canvas->cur_id] = 0;
        canvas->is_visible[canvas->cur_id] = canvas->is_visible[prev_id];
        canvas->update();
    }
    else if (!isKxFloat || !isKyFloat|| isXcFloat || isYcFloat)
    {
        QMessageBox::information(this, "Error", "Xc, Yc, Kx и Ky должны быть вещественными числами");
    }
    /*else if (!isKxFloat)
    {
        QMessageBox::information(this, "Error", "Kx должен быть вещественным числом");
    }
    else if (!isKyFloat)
    {
        QMessageBox::information(this, "Error", "Ky должен быть вещественным числом");
    }*/
    if (!canvas->is_visible[canvas->cur_id])
        ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");
    else
        ui->coords_label->setText(tr("Текущее состояние:\nКоординаты центра:\nX: %1 Y: %2").arg(center_x).arg(center_y));
}

void MainWindow::on_rotate_btn_clicked()
{
    bool isXcFloat = false;
    float xc = ui->x_rotate_center->text().toFloat(&isXcFloat);
    bool isYcFloat = false;
    float yc = ui->y_rotate_center->text().toFloat(&isYcFloat);

    bool isAngleFloat = false;
    float angle = ui->rotate_angle->text().toFloat(&isAngleFloat);
    if (isXcFloat && isYcFloat && isAngleFloat)
    {
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
        {
            canvas->first_id++;
            if (canvas->first_id >= GAP)
                canvas->first_id = 0;
        }

        float radians = angle * PI / 180;
        float new_x = center_x;
        float new_y = center_y;
        rotate(&new_x, &new_y, xc, yc, radians);

        center_x = new_x;
        center_y = new_y;

        canvas->transofrmation[canvas->cur_id] = ROTATE;
        canvas->reverse = false;

        canvas->angle[canvas->cur_id] = angle;
        if (abs(canvas->angle[canvas->cur_id] - 360) <= EPS || canvas->angle[canvas->cur_id] > 360)
        {
            canvas->angle[canvas->cur_id] -= int(canvas->angle[canvas->cur_id] / 360) * 360;
        }
        if (abs(canvas->angle[canvas->cur_id] - int(canvas->angle[canvas->cur_id] / 360) * 360) <= EPS)
            canvas->angle[canvas->cur_id] = 0;

        canvas->rotate_center_x[canvas->cur_id] = xc;
        canvas->rotate_center_y[canvas->cur_id] = yc;
        //Без изменений
        canvas->float_x[canvas->cur_id] = 0;
        canvas->float_y[canvas->cur_id] = 0;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->size_center_x[canvas->cur_id] = 0;
        canvas->size_center_y[canvas->cur_id] = 0;
        canvas->size_x[canvas->cur_id] = 1;
        canvas->size_y[canvas->cur_id] = 1;
        canvas->is_visible[canvas->cur_id] = canvas->is_visible[prev_id];
        canvas->update();
    }
    if (!isXcFloat || !isYcFloat)
    {
        QMessageBox::information(this, "Error", "Xc и Yc должны быть вещественными числами");
    }
    if (!isAngleFloat)
    {
        QMessageBox::information(this, "Error", "Угол φ должен быть вещественным числом");
    }
    if (!canvas->is_visible[canvas->cur_id])
        ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");
    else
        ui->coords_label->setText(tr("Текущее состояние:\nКоординаты центра:\nX: %1 Y: %2").arg(center_x).arg(center_y));
}

void MainWindow::on_pushButton_clicked()
{
    if (canvas->cur_id == canvas->first_id)
    {
        QMessageBox::information(this, "Error", "Действий не найдено");
        canvas->is_visible[canvas->cur_id] = false;
    }
    else
    {
        int prev_id = canvas->cur_id;
        canvas->cur_id -= 1;
        if (canvas->cur_id < 0)
            canvas->cur_id = GAP - 1;
        canvas->reverse = true;
        switch (canvas->transofrmation[prev_id])
        {
            case MOVE:
            {
                center_x -= canvas->float_x[prev_id];
                center_y -= canvas->float_y[prev_id];
            }
            case SCALE:
            {
                center_x = (1 / canvas->size_x[prev_id]) * center_x + canvas->size_center_x[prev_id] * (1 - (1 / canvas->size_x[prev_id]));
                center_y = (1 / canvas->size_y[prev_id]) * center_y + canvas->size_center_y[prev_id] * (1 - (1 / canvas->size_y[prev_id]));
            }
            case ROTATE:
            {
                float radians = (-canvas->angle[prev_id]) * PI / 180;
                float new_x = center_x;
                float new_y = center_y;
                rotate(&new_x, &new_y, canvas->rotate_center_x[prev_id], canvas->rotate_center_x[prev_id], radians);
                center_x = new_x;
                center_y = new_y;
            }
            default:
            {
                //nothing
            }

        }
    }
    canvas->update();
    if (!canvas->is_visible[canvas->cur_id])
        ui->coords_label->setText("Текущее состояние:\nИзображение\nне отображается");
    else
        ui->coords_label->setText(tr("Текущее состояние:\nКоординаты центра:\nX: %1 Y: %2").arg(center_x).arg(center_y));
}

void MainWindow::on_get_coords_info_clicked()
{
    QMessageBox::information(this, "Информация о системе координат", "Центр данной системы координат находится в центре.\n"
                                   "Ось Ox направлена вправо, а ось Oy вниз.");
}


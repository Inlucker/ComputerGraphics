#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->method_comboBox->addItem("ЦДА");
    ui->method_comboBox->addItem("Брезенхем (int)");
    ui->method_comboBox->addItem("Брезенхем (float)");
    ui->method_comboBox->addItem("Брезенхем с устранением ступенчатости");
    ui->method_comboBox->addItem("Ву");
    ui->method_comboBox->addItem("QT");

    ui->penColor_comboBox->addItem("Чёрный");
    ui->penColor_comboBox->addItem("Красный");
    ui->penColor_comboBox->addItem("Зелёный");
    ui->penColor_comboBox->addItem("Синий");
    ui->penColor_comboBox->addItem("Белый");

    ui->backgroundColor_comboBox->addItem("Белый");
    ui->backgroundColor_comboBox->addItem("Красный");
    ui->backgroundColor_comboBox->addItem("Зелёный");
    ui->backgroundColor_comboBox->addItem("Синий");
    ui->backgroundColor_comboBox->addItem("Чёрный");

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    canvas = new Canvas();
    ui->gridLayout->addWidget(canvas);

    graphForm = new GraphForm();
    //graphForm->makePlot();
    //graphForm->show();

    stageForm = new StageForm();
}

MainWindow::~MainWindow()
{
    delete canvas;
    delete graphForm;
    delete stageForm;
    delete ui;
}


void MainWindow::on_draw_Btn_clicked()
{
    bool isXsFloat = false;
    float Xs = ui->X_start_Edit->text().toFloat(&isXsFloat);

    bool isYsFloat = false;
    float Ys = ui->Y_start_Edit->text().toFloat(&isYsFloat);

    bool isXeFloat = false;
    float Xe = ui->X_end_Edit->text().toFloat(&isXeFloat);

    bool isYeFloat = false;
    float Ye = ui->Y_end_Edit->text().toFloat(&isYeFloat);

    if (isXsFloat)
        canvas->X_start = round(Xs);
    else
        QMessageBox::information(this, "Error", "X начальный должен быть вещественным числом");

    if (isYsFloat)
        canvas->Y_start = round(Ys);
    else
        QMessageBox::information(this, "Error", "Y начальный должен быть вещественным числом");

    if (isXsFloat)
        canvas->X_end = round(Xe);
    else
        QMessageBox::information(this, "Error", "X конечный должен быть вещественным числом");

    if (isXsFloat)
        canvas->Y_end = round(Ye);
    else
        QMessageBox::information(this, "Error", "Y конечный должен быть вещественным числом");


    /*double dX = fabs(Xs - Xe), dY = abs(Ys - Ye);
    double l = fmax(dX, dY);
    dX = (Xe - Xs) / l;
    dY = (Ye - Ys) / l;
    //dX /= l;
    //dY /= l;
    double X = Xs, Y = Ys;

    while (fabs(X - Xe) > 1 || fabs(Y - Ye) > 1)
    {
        //painter.drawPoint(int(X), int(Y));
        QPoint p = QPoint(int(X), int(Y));
        canvas->draw_point(p);
        X = X + dX, Y += dY;
    }*/
    //canvas->setPenColor(Qt::green);
    if (isXsFloat && isYsFloat && isXsFloat && isXsFloat)
    {
        canvas->draw();
        canvas->update();
    }

}

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clean();
}

void MainWindow::on_penColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setPenColor(Qt::black);
            break;
        case 1:
            canvas->setPenColor(Qt::red);
            break;
        case 2:
            canvas->setPenColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setPenColor(Qt::blue);
            break;
        case 4:
            canvas->setPenColor(Qt::white);
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_backgroundColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setStyleSheet("background-color:white;");
            break;
        case 1:
            canvas->setStyleSheet("background-color:red;");
            break;
        case 2:
            canvas->setStyleSheet("background-color:green;");
            break;
        case 3:
            canvas->setStyleSheet("background-color:blue;");
            break;
        case 4:
            canvas->setStyleSheet("background-color:black;");
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_method_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->method = DIG_DIF_ANALIZ;
            break;
        case 1:
            canvas->method = BREZENHAM_INT;
            break;
        case 2:
            canvas->method = BREZENHAM_FLOAT;
            break;
        case 3:
            canvas->method = BREZENHAM_STEP_REM;
            break;
        case 4:
            canvas->method = VU;
            break;
        case 5:
            canvas->method = STANDART;
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_Create_Spectre_Btn_clicked()
{
    bool isAngleFloat = false;
    float Angle = ui->Angle_Edit->text().toFloat(&isAngleFloat);

    bool isLengthFloat = false;
    float Length = ui->Length_Edit->text().toFloat(&isLengthFloat);

    if (isAngleFloat)
        canvas->angle = Angle;
    else
        QMessageBox::information(this, "Error", "Угол должен быть вещественным числом");

    if (isLengthFloat)
        canvas->length = Length;
    else
        QMessageBox::information(this, "Error", "Длина отрезка должна быть вещественным числом");

    if (isAngleFloat && isLengthFloat)
    {
        canvas->drawSpectre();
        canvas->update();
    }
}

#include <iostream>

void MainWindow::on_show_graphs_Btn_clicked()
{
    bool isLengthFloat = false;
    float Len = ui->Len_Edit->text().toFloat(&isLengthFloat);

    if (isLengthFloat)
    {
        double times[6];
        times[0] = canvas->getTime(Len, DIG_DIF_ANALIZ);
        times[1] = canvas->getTime(Len, BREZENHAM_INT);
        times[2] = canvas->getTime(Len, BREZENHAM_FLOAT);
        times[3] = canvas->getTime(Len, BREZENHAM_STEP_REM);
        times[4] = canvas->getTime(Len, VU);
        times[5] = canvas->getTime(Len, STANDART);
        /*for (int i = 0; i < 6; i++)
        {
            std::cout << times[i] << std::endl;
            //if (times[i] <= 0.00001)
                //times[i] = 2 + 0.1 * i;
        }*/
        graphForm->makePlot(times, Len);
        //printf("%.6f", Len);
        graphForm->show();
        graphForm->activateWindow();
    }
    else
        QMessageBox::information(this, "Error", "Длина отрезка должна быть вещественным числом");

}

void MainWindow::on_stage_Btn_clicked()
{

    bool isLengthFloat = false;
    float Len = ui->Len_Edit->text().toFloat(&isLengthFloat);

    if (isLengthFloat)
    {
        QVector<double> x, y;
        int n = 0;
        getXYs(&x, &y, &n, Len, canvas->method);

        if (n != -1 || canvas->method != STANDART)
        {
            stageForm->makePlot(x, y, n, canvas->method);
            stageForm->show();
            stageForm->activateWindow();
        }
        else
        {
            QMessageBox::information(this, "Error", "Нельзя оценить ступенчатость для алгоритма QT");
        }
    }
    else
        QMessageBox::information(this, "Error", "Длина отрезка должна быть вещественным числом");

}

#define MAX_ANGLE 90

void MainWindow::getXYs(QVector<double> *x, QVector<double> *y, int *n, double length, Algoritm method)
{
    QVector<double> res_x, res_y;
    int res_n = 0;
    double X0 = 350, Y0 = 300;
    //double X1 = X0, Y1 = Y0 - length;
    switch (method)
    {
        case DIG_DIF_ANALIZ:
        {
            double tmpAngle = 0;
            while (tmpAngle <= MAX_ANGLE) //2 * M_PI)
            {
                res_x.append(tmpAngle);
                res_y.append(double(getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_INT:
        {
            double tmpAngle = 0;
            while (tmpAngle <= MAX_ANGLE)
            {
                res_x.append(tmpAngle);
                res_y.append(double(getStairsBrezenheimInt(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_FLOAT:
        {
            double tmpAngle = 0;
            while (tmpAngle <= MAX_ANGLE)
            {
                res_x.append(tmpAngle);
                res_y.append(double(getStairsBrezenheimFloat(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_STEP_REM:
        {
            double tmpAngle = 0;
            while (tmpAngle <= MAX_ANGLE)
            {
                res_x.append(tmpAngle);
                res_y.append(double(getStairsBrezenheimSmooth(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case VU:
        {
            double tmpAngle = 0;
            while (tmpAngle <= MAX_ANGLE)
            {
                res_x.append(tmpAngle);
                res_y.append(double(getStairsVu(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                printf("x:%f y:%f;\n", res_x[res_n], res_y[res_n]);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case STANDART:
        {
            res_n = -1;
            break;
        }
        default:
        //???
        break;
    }
    *x = res_x;
    *y = res_y;
    *n = res_n;
}

int MainWindow::sign(double val)
{
  if (val > 0)
      return 1;
  if (val < 0)
      return -1;
  else
      return 0;
}

int MainWindow::getStairsDGA(int X_start, int X_end, int Y_start, int Y_end)
{
    double dX = fabs(X_start - X_end), dY = fabs(Y_start - Y_end);
    double tg;
    if (dX)
        tg = dY / dX;
    else
        tg = 0;
    double steep = fmax(dX, dY);
    dX = (X_end - X_start) / steep;
    dY = (Y_end - Y_start) / steep;
    double X = X_start, Y = Y_start;

    int stairsNumber = 1;
    while (fabs(X - X_end) > 1 || fabs(Y - Y_end) > 1)
    {
        if ((abs(int(X) - int(X + dX)) >= 1 && tg > 1) || (abs(int(Y) - int(Y + dY)) >= 1 && 1 >= tg && tg != 0))
            stairsNumber++;
        X = X + dX, Y += dY;
    }
    return stairsNumber;
}

int MainWindow::getStairsBrezenheimInt(int X_start, int X_end, int Y_start, int Y_end)
{
    int X = X_start, Y = Y_start;
    int dX = X_end - X_start, dY = Y_end - Y_start;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        //dX, dY = dY, dX;
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1; // шагаем по y
    }
    else
        steep = 0;

    int er = 2 * dY - dX; // отличие от вещественного (e = tg - 1 / 2) tg = dy / dx

    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);

    //painter.drawPoint(X, Y);
    int stairsNumber = 1;
    while (X != X_end || Y != Y_end)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 2 * dX; // отличие от вещественного (e -= 1)
            stairsNumber++;
            //stairs.append(st)
            //st = 0
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            //st += 1
            er += 2 * dY; // отличие от вещественного (e += tg)
        }
        //painter.drawPoint(X, Y);
    }
    return stairsNumber;
}

int MainWindow::getStairsBrezenheimFloat(int X_start, int X_end, int Y_start, int Y_end)
{
    int X = X_start, Y = Y_start;
    int dX = X_end - X_start, dY = Y_end - Y_start;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        //dX, dY = dY, dX;
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1; // шагаем по y
    }
    else
        steep = 0;

    double tg = double(dY) / double(dX) ; // tангенс угла наклона
    double er = tg - 0.5; // начальное значение ошибки

    //QPainter painter(&my_pixmap);
    //painter.setPen(pen);

    //painter.drawPoint(X, Y);
    int stairsNumber = 1;
    while (X != X_end || Y != Y_end)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 1; // отличие от целого
            stairsNumber++;
            //stairs.append(st)
            //st = 0
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            //st += 1
            er += tg; // отличие от целого
        }
        //painter.drawPoint(X, Y);
    }
    return stairsNumber;
}

int MainWindow::getStairsBrezenheimSmooth(int X_start, int X_end, int Y_start, int Y_end)
{
    int X = X_start, Y = Y_start;
    int I = 255;
    int dX = X_end - X_start, dY = Y_end - Y_start;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1;
    }
    else
        steep = 0;

    double tg = double(dY) / double(dX) * double(I); // тангенс угла наклона (умножаем на инт., чтобы не приходилось умножать внутри цикла
    double er = double(I) / 2; // интенсивность для высвечивания начального пикселя
    double w = double(I) - tg; // пороговое значение

    //plot(&painter, X, Y, int(er));
    int stairsNumber = 1;
    while (X != X_end || Y != Y_end)
    {
        if (er < w)
        {
            if (steep == 0) // dy < dx
                X += SX; // -1 if dx < 0, 0 if dx = 0, 1 if dx > 0
            else // dy >= dx
                Y += SY; // -1 if dy < 0, 0 if dy = 0, 1 if dy > 0
            //st += 1 // steepping
            er += tg;
        }
        else if (er >= w)
        {
            X += SX;
            Y += SY;
            er -= w;
            stairsNumber++;
            //stairs.append(st)
            //st = 0
        }
        //plot(&painter, X, Y, int(er));
    }
    return stairsNumber;
}

int MainWindow::getStairsVu(int X_start, int X_end, int Y_start, int Y_end)
{
    //int I = 255;
    bool steep = abs(Y_end - Y_start) > abs(X_end - X_start);

    if (steep)
    {
        int tmp = X_start;
        X_start = Y_start;
        Y_start = tmp;

        tmp = X_end;
        X_end = Y_end;
        Y_end = tmp;
    }
    if (X_start > X_end)
    {
        int tmp = X_start;
        X_start = X_end;
        X_end = tmp;

        tmp = Y_start;
        Y_start = Y_end;
        Y_end = tmp;
    }

    //DrawPoint(&painter, steep, X_start, Y_start, I);
    //DrawPoint(&painter, steep, X_end, Y_end, I);
    int stairsNumber = 1;

    double dX = X_end - X_start, dY = Y_end - Y_start;

    double tg;
    if (dX == 0)
        tg = 1;
    else
        tg = dY / dX;

    double y = Y_start + tg;

    for (int x = X_start + 1; x < X_end; x++)
    {
        //DrawPoint(&painter, steep, x, int(y), I*(abs(1.0 - y + int(y))));
        //DrawPoint(&painter, steep, x, int(y)+1, I*(abs(y - int(y))));
        if ((abs(int(x) - int(x + 1)) >= 1 && fabs(tg) > 1) || !( 1 > abs(int(y) - int(y + tg)) >= fabs(tg)))
            stairsNumber++;
        y += tg;
    }
    return stairsNumber;
}

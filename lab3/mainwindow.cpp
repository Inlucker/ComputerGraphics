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
    QVector<double> x, y;
    int n = 0;
    getXYs(&x, &y, &n, 100, canvas->method);
    /*QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i - 50; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    n = 101;*/
    stageForm->makePlot(x, y, n);
    stageForm->show();
    stageForm->activateWindow();
}

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
            while (tmpAngle < 90) //2 * M_PI)
            {
                res_y.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_x.append(tmpAngle);
                printf("x:%f y:%f;\n", res_x[res_n], res_y[res_n]);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_FLOAT:
        {
            double tmpAngle = 0;
            while (tmpAngle < 90)
            {
                res_x.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_y.append(tmpAngle);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_INT:
        {
            double tmpAngle = 0;
            while (tmpAngle < 90)
            {
                res_x.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_y.append(tmpAngle);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case BREZENHAM_STEP_REM:
        {
            double tmpAngle = 0;
            while (tmpAngle < 90)
            {
                res_x.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_y.append(tmpAngle);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case VU:
        {
            double tmpAngle = 0;
            while (tmpAngle < 90)
            {
                res_x.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_y.append(tmpAngle);
                res_n++;
                tmpAngle += 1.0;
            }
            break;
        }
        case STANDART:
        {
            double tmpAngle = 0;
            while (tmpAngle < 90)
            {
                res_x.append(double(canvas->getStairsDGA(X0, round(length * cos(tmpAngle * M_PI / 180.0) + X0), Y0, round(length * cos((90 - tmpAngle) * M_PI / 180.0) + Y0))));
                res_y.append(tmpAngle);
                res_n++;
                tmpAngle += 1.0;
            }
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

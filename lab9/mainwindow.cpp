#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedHeight(height());
    setFixedWidth(width());


    ui->MainPenColor_comboBox->addItem("Чёрный");
    ui->MainPenColor_comboBox->addItem("Красный");
    ui->MainPenColor_comboBox->addItem("Зелёный");
    ui->MainPenColor_comboBox->addItem("Синий");

    ui->SemiPenColor_comboBox->addItem("Красный");
    ui->SemiPenColor_comboBox->addItem("Чёрный");
    ui->SemiPenColor_comboBox->addItem("Зелёный");
    ui->SemiPenColor_comboBox->addItem("Синий");

    ui->backgroundColor_comboBox->addItem("Синий");
    ui->backgroundColor_comboBox->addItem("Красный");
    ui->backgroundColor_comboBox->addItem("Зелёный");
    ui->backgroundColor_comboBox->addItem("Чёрный");

    canvas = new Canvas();
    ui->gridLayout_2->addWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MainPenColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setCutterPenColor(Qt::black);
            break;
        case 1:
            canvas->setCutterPenColor(Qt::red);
            break;
        case 2:
            canvas->setCutterPenColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setCutterPenColor(Qt::blue);
            break;
        default:
            //???
            break;
    }
    canvas->clean();
}

void MainWindow::on_SemiPenColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setLinePenColor(Qt::red);
            break;
        case 1:
            canvas->setLinePenColor(Qt::black);
            break;
        case 2:
            canvas->setLinePenColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setLinePenColor(Qt::blue);
            break;
        default:
            //???
            break;
    }
    canvas->clean();
}

void MainWindow::on_backgroundColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            //canvas->setStyleSheet("background-color:white;");
            canvas->setRezColor(Qt::blue);
            break;
        case 1:
            //canvas->setStyleSheet("background-color:red;");
            canvas->setRezColor(Qt::red);
            break;
        case 2:
            //canvas->setStyleSheet("background-color:green;");
            canvas->setRezColor(Qt::darkGreen);
            break;
        case 3:
            //canvas->setStyleSheet("background-color:blue;");
            canvas->setRezColor(Qt::black);
            break;
        default:
            //???
            break;
    }
    canvas->clean();
}

void MainWindow::on_add_point_Btn_clicked()
{
    bool isXFloat = false;
    float X = ui->X_Edit->text().toFloat(&isXFloat);

    bool isYFloat = false;
    float Y = ui->Y_Edit->text().toFloat(&isYFloat);

    if (!isXFloat)
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");

    if (!isYFloat)
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");

    if (isXFloat && isYFloat)
    {
        if (ui->Edge_mode_radioButton->isChecked())
            canvas->addPoint(round(X), round(Y));
        else if (ui->Cut_mode_radioButton->isChecked())
            canvas->setCutter(round(X), round(Y));
    }
}

void MainWindow::on_fill_Btn_clicked()
{
    if (!canvas->linesSize())
    {
        QMessageBox::information(this, "Error", "Нет многоугольника. Пожалуйста, введите многоугольник.");
        return;
    }

    if (!canvas->lockedLines())
    {
        QMessageBox::information(this, "Error", "Многоугольник не замкнут. Пожалуйста, замкните многоугольник.");
        return;
    }

    /*if (!canvas->isLinesPolygon())
    {
        QMessageBox::information(this, "Error", "Рёбра многоугольника не могут пересекаться.");
        return;
    }*/

    if (!canvas->cutterSize())
    {
        QMessageBox::information(this, "Error", "Нет отсекателя. Пожалуйста, введите отсекатель.");
        return;
    }

    if (!canvas->lockedCutter())
    {
        QMessageBox::information(this, "Error", "Отсекатель не замкнут. Пожалуйста, замкните отсекатель.");
        return;
    }

    if (!canvas->isCutterPolygon())
    {
        QMessageBox::information(this, "Error", "Рёбра отсекателя не могут пересекаться.");
        return;
    }

    canvas->cut();
}

void MainWindow::on_Edge_mode_radioButton_clicked()
{
    canvas->edgeFlag = true;
}

void MainWindow::on_Cut_mode_radioButton_clicked()
{
    canvas->edgeFlag = false;
}

void MainWindow::on_lock_Btn_2_clicked()
{
    canvas->lockLines();
}

void MainWindow::on_lock_Btn_clicked()
{
    canvas->lockCutter();
}


void MainWindow::on_clean_Btn_clicked()
{
    canvas->resetLines();
}

void MainWindow::on_clean_Btn_2_clicked()
{
    canvas->resetCutter();
}

void MainWindow::on_clean_Btn_3_clicked()
{
    canvas->resetLines();
    canvas->resetCutter();
}

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

/*void MainWindow::mousePressEvent(QMouseEvent *event)
{
    cout << canvas->geometry().x() << endl;
    if (event->button() == Qt::LeftButton && this->canvas->rect().contains(event->pos()))
    {
        double x = canvas->prev_x;
        double y = canvas->prev_y;
        if (event->modifiers() == Qt::ALT && !canvas->firstPointCheck())
        {
            x = event->position().x() - canvas->x();
            if (event->position().y() < y)
                y = y - (x - canvas->prev_x) - canvas->y();
            else
                y = y + (x - canvas->prev_x);
            cout << "HERE" << endl;
        }
        else if (event->modifiers() == Qt::CTRL && !canvas->firstPointCheck())
        {
            x = event->position().x() - canvas->x();
        }
        else if (event->modifiers() == Qt::SHIFT && !canvas->firstPointCheck())
        {
            y = event->position().y() - canvas->y();
        }
        else
        {
            x = event->position().x() - canvas->x();
            y = event->position().y() - canvas->y();
        }

        canvas->addPoint(x, y);
    }
}*/


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

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clean();
}

void MainWindow::on_fill_Btn_clicked()
{
    /*if (!canvas->locked())
    {
        QMessageBox::information(this, "Error", "Фигура не замкнута. Пожалуйста, замкните фигуру.");
        return;
    }*/

    if (canvas->linesSize() <= 0)
    {
        QMessageBox::information(this, "Error", "Нету отрезков. Пожалуйста, введите хотя бы один.");
        return;
    }

    if (!canvas->cutterSize())
    {
        QMessageBox::information(this, "Error", "Нет отсекателя. Пожалуйста, введите отсекатель.");
        return;
    }

    if (!canvas->locked())
    {
        QMessageBox::information(this, "Error", "Отсекатель не замкнут. Пожалуйста, замкните отсекатель.");
        return;
    }

    canvas->cut();
}

void MainWindow::on_get_time_Btn_clicked()
{
    if (canvas->linesSize() <= 0)
    {
        QMessageBox::information(this, "Error", "Нету отрезков. Пожалуйста, введите хотя бы один.");
        return;
    }

    if (!canvas->cutterSize())
    {
        QMessageBox::information(this, "Error", "Нет отсекателя. Пожалуйста, введите отсекатель.");
        return;
    }
    auto start = chrono::high_resolution_clock::now();
    canvas->cut();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> dur = end - start;
    QMessageBox::information(this, "Время отсечения", QString("Время отсечения = %1").arg(dur.count()));
}

void MainWindow::on_Edge_mode_radioButton_clicked()
{
    canvas->edgeFlag = true;
}

void MainWindow::on_Cut_mode_radioButton_clicked()
{
    canvas->edgeFlag = false;
}

void MainWindow::on_lock_Btn_clicked()
{
    canvas->lock();
}

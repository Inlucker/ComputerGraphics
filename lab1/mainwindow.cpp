#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "X" << "Y");

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg((i + 1)*6));

            ui->tableWidget->setItem(i, j, itm);
        }

    myPicture = new MyGraphicsView();
    ui->gridLayout->addWidget(myPicture);
    myPicture->setStyleSheet("background-color:white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enterDotsNumberBtn_clicked()
{
    QString text = ui->lineEdit->text();
    bool isInt = false;
    int tmp = text.toInt(&isInt);
    if (isInt && tmp >= 3 && tmp <= 100)
    {
        ui->tableWidget->setRowCount(tmp);
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
            for (int j = 0; j < ui->tableWidget->columnCount(); j++)
            {
                QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg((i + 1)*6));

                ui->tableWidget->setItem(i, j, itm);
            }
        //ui->tableWidget->setColumnCount(2);
    }
    else
    {
        QMessageBox::information(this, "Rez", "Нужно ввести целое число принадлежащее интервалу [3; 100]");
    }
}

void MainWindow::on_outputBtn_clicked()
{
    myPicture->clearPoints();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString xText = ui->tableWidget->item(i, 0)->text();
        bool xIsInt = false;
        int x = xText.toInt(&xIsInt);

        QString yText = ui->tableWidget->item(i, 1)->text();
        bool yIsInt = false;
        int y = yText.toInt(&yIsInt);

        if (xIsInt && yIsInt)
        {
            QPen penBlack(Qt::black); // Задаём чёрную кисть
            myPicture->x[i] = x;
            myPicture->y[i] = y;
        }
        else
        {
            QMessageBox::information(this, "Rez", "Все координаты должны быть целыми числами");
            break;
        }
    }

    myPicture->update();
}

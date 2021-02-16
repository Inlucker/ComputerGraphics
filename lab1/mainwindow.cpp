#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculations.h"

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
            QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg((rand() % 100 + 1)*5));

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
        {
            QTableWidgetItem *itm_x = new QTableWidgetItem(tr("%1").arg((rand() % 100 + 1)*5));
            ui->tableWidget->setItem(i, 0, itm_x);

            QTableWidgetItem *itm_y = new QTableWidgetItem(tr("%1").arg((rand() % 100 + 1)*5));
            ui->tableWidget->setItem(i, 1, itm_y);
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
    pair<int, int> dots[ui->tableWidget->rowCount()];
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
            dots[i].first = x;
            dots[i].second = y;
        }
        else
        {
            QMessageBox::information(this, "Rez", "Все координаты должны быть целыми числами");
            break;
        }
    }

    //here

    int max_dif = -1;
    /*int rez_x1;
    int rez_y1;
    int rez_x2;
    int rez_y2;
    int rez_x3;
    int rez_y3;*/

    int c = 0;
    for (int i = 0; i < ui->tableWidget->rowCount() - 2; i++)
    {
        for (int j = i + 1; j < ui->tableWidget->rowCount() - 1; j++)
        {
            for (int k = j + 1; k < ui->tableWidget->rowCount(); k++)
            {
                int cur_ids[THREE] = {i, j , k};
                int tmp = get_max_dif(dots, ui->tableWidget->rowCount(), cur_ids);
                c++;
                cout << "i = " << i << "; j = "<< j << "; k = " << k << "; c = " << c << "; tmp = " << tmp << endl;
                if (tmp > max_dif)
                {
                    max_dif = tmp;

                    myPicture->rez_x1 = dots[i].first;
                    myPicture->rez_y1 = dots[i].second;
                    myPicture->rez_x2 = dots[j].first;
                    myPicture->rez_y2 = dots[j].second;
                    myPicture->rez_x3 = dots[k].first;
                    myPicture->rez_y3 = dots[k].second;

                    myPicture->id1 = i + 1;
                    myPicture->id2 = j + 1;
                    myPicture->id3 = k + 1;
                }
            }
        }
    }
    cout << max_dif << endl;
    myPicture->update();
}

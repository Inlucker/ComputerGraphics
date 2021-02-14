#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <iostream>

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

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);        // Устанавливаем сцену в виджет

    //group_1 = new QGraphicsItemGroup();

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(i + 1));

            ui->tableWidget->setItem(i, j, itm);
        }

    /*timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);          // Запускаем таймер*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::slotTimer()
{
    // Переопределяем размеры графической сцены в зависимости от размеров окна
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}*/

void MainWindow::on_outputBtn_clicked()
{
    /* Удаляем все элементы со сцены,
     * если они есть перед новой отрисовкой
     * */
    this->deleteItemsFromGroup(group_1);

    int width = this->width();      // определяем ширину нашего виджета
    int height = this->height();    // определяем высоту нашего виджета

    /* Устанавливаем размер сцены по размеру виджета
     * Первая координата - это левый верхний угол,
     * а Вторая - это правый нижний угол
     * */
    scene->setSceneRect(0, 0, width, height);

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

            //group_1->addToGroup(scene->addLine(x, y, x, y + 10, penBlack));    group_1->addToGroup(scene->addLine(20,20, width - 20, 20, penBlack));
            group_1->addToGroup(scene->addLine(width - 20, 20, width - 20, height -20, penBlack));
            group_1->addToGroup(scene->addLine(width - 20, height -20, 20, height -20, penBlack));
            group_1->addToGroup(scene->addLine(20, height -20, 20, 20, penBlack));
        }
        else
        {
            QMessageBox::information(this, "Rez", "Все координаты должны быть целыми числами");
            break;
        }
    }


}

void MainWindow::on_enterDotsNumberBtn_clicked()
{
    QString text = ui->lineEdit->text();
    bool isInt = false;
    int tmp = text.toInt(&isInt);
    if (isInt && tmp >= 3)
    {
        ui->tableWidget->setRowCount(tmp);
        //ui->tableWidget->setColumnCount(2);
    }
    else
    {
        QMessageBox::information(this, "Rez", "Нужно ввести целое не меньше 3");
    }
}

/* Метод для удаления всех элементов из группы
 * */
void MainWindow::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    /* Перебираем все элементы сцены, и если они принадлежат группе,
     * переданной в метод, то удаляем их
     * */
    foreach(QGraphicsItem *item, scene->items(group->boundingRect()))
    {
       if (item->group() == group)
       {
          delete item;
       }
    }
}

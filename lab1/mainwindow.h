#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Таймер для изменения размеров сцены при изменении размеров Окна приложения
    //void slotTimer();

    void on_outputBtn_clicked();

    void on_enterDotsNumberBtn_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_1;   // Объявляем первую группу элементов

    //QTimer *timer;

    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
};
#endif // MAINWINDOW_H

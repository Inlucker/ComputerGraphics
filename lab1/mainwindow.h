#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mygraphicsview.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QKeyEvent>
#include <random>

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
    void on_enterDotsNumberBtn_clicked();

    void on_outputBtn_clicked();

private:
    Ui::MainWindow *ui;

    MyGraphicsView *myPicture;

    int cur_dots_number;

    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);

protected:
   virtual void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H

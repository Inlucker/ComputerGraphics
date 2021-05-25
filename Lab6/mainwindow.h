#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <chrono>
#include <QString>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   //virtual void mousePressEvent(QMouseEvent *event);

private slots:
    void on_MainPenColor_comboBox_activated(int index);

    void on_SemiPenColor_comboBox_activated(int index);

    void on_backgroundColor_comboBox_activated(int index);

    void on_add_point_Btn_clicked();

    void on_lock_Btn_clicked();

    void on_Delay_on_radioButton_clicked();

    void on_Delay_off_radioButton_clicked();

    void on_fill_Btn_clicked();

    void on_clean_Btn_clicked();

    void on_get_time_Btn_clicked();

    void on_Edge_mode_radioButton_clicked();

    void on_Fill_mode_radioButton_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
};
#endif // MAINWINDOW_H

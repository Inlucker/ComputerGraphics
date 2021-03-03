#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvas.h"
#include <QMainWindow>
#include <QMessageBox>

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
    void on_create_btn_clicked();

    void on_move_btn_clicked();

    void on_change_size_btn_clicked();

    void on_rotate_btn_clicked();

    void on_pushButton_clicked();

    void on_get_coords_info_clicked();

private:
    Ui::MainWindow *ui;

    float center_x = 0;
    float center_y = 0;

    Canvas *canvas;
};
#endif // MAINWINDOW_H

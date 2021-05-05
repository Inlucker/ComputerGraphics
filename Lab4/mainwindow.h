#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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

private slots:
    void on_method_comboBox_activated(int index);

    void on_penColor_comboBox_activated(int index);

    void on_backgroundColor_comboBox_activated(int index);

    void on_clean_Btn_clicked();

    void on_draw_circle_Btn_clicked();

    void on_draw_ellipse_Btn_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
};
#endif // MAINWINDOW_H

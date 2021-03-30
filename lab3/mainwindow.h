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
    void on_draw_Btn_clicked();

    void on_clean_Btn_clicked();

    void on_penColor_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;

    Canvas *canvas;
};
#endif // MAINWINDOW_H

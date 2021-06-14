#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
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

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void on_SemiPenColor_comboBox_activated(int index);

    void on_backgroundColor_comboBox_activated(int index);

    void on_clean_Btn_clicked();

    void on_cut_col_btn_clicked();

    void on_pushButton_clicked();

    //void on_end_cutter_clicked();

    void on_rotate_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    Canvas *canvas;

    double (*cur_func)(double x, double z);

    bool LMB_is_pressed;
    int previous_x, previous_y;
};
#endif // MAINWINDOW_H

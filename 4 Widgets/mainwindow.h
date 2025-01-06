#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Button_add_city__toggled(bool checked);

    void on_Big_radio_button__clicked();

    void on_Small_radio_button__clicked();

private:
    Ui::MainWindow *ui;
    int CountBar = 0;
    bool letter_check_ = false;
    void setText();
};
#endif // MAINWINDOW_H

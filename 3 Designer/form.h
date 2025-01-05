#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "mainwindow.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    MainWindow main_windoow_;
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_just_button__clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H

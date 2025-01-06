#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Qchar.h>
#define MAX_BAR 10
#define MIN_BAR 0
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Small_radio_button_->setChecked(false);
    ui->Big_radio_button_->setChecked(true);
    ui->progressbar->setMinimum(MIN_BAR);
    ui->progressbar->setMaximum(MAX_BAR);
    ui->progressbar->setValue(0);
    ui->Button_add_city_->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_add_city__toggled(bool checked)
{
    if(checked == true)
    {
        if(CountBar > MAX_BAR)
        {
            CountBar = 0;
            ui->progressbar->setValue(0);
            ui->List_city_->clear();
        }else{
            ui->progressbar->setValue(++CountBar);
            setText();
        }

    }

}

void MainWindow::setText(){

    QString text = ui->Line_edit_city_->text();

    if(letter_check_){
        text = text.toLower();
    }else{
        text = text.toUpper();
    }
    ui->List_city_->addItem(text);
}


void MainWindow::on_Big_radio_button__clicked()
{
    letter_check_ = false;
}


void MainWindow::on_Small_radio_button__clicked()
{
    letter_check_ = true;
}


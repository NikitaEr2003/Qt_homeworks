#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_cancel__clicked()
{
    ui->line_edit_login_->clear();
    ui->line_edit_name_base_->clear();
    ui->line_edit_name_host_->clear();
    ui->line_edit_password_->clear();
    ui->spin_box_port_->setValue(0);
}


void MainWindow::on_button_exit__clicked()
{
    this->close();
}


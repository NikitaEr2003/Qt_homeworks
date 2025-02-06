#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsBlurEffect>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("://images/picture.jpg"));
    ui->tabWidget_main_->setStyleSheet("QTabBar::tab {"
                                       "   background: transparent;"
                                       "   margin-right: 15px; "
                                       "   border: none;"
                                       "}"
                                       "QTabBar::tab:selected {"
                                       "   color: rgb(50, 205, 50);"
                                       "   font-weight: bold"
                                       "}"
                                       "QTabWidget::pane {"
                                       "   border: none;"
                                       "}");
    ui->label_status_connect_->setStyleSheet("QLabel { color: #00FFFF; } ");
    ui->lineEdit_name_bd_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }""QLineEdit {""font-family: Arial;"  "font-size: 13px;"   "}");
    ui->lineEdit_name_host_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }""QLineEdit {""font-family: Arial;"  "font-size: 13px;"   "}");
    ui->lineEdit_port_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }""QLineEdit {""font-family: Arial;"  "font-size: 13px;"   "}");
    ui->lineEdit_user_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5);  }""QLineEdit {""font-family: Arial;"  "font-size: 13px;"   "}");
    ui->lineEdit_user_password_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }""QLineEdit {""font-family: Arial;"  "font-size: 13px;"   "}");
    ui->pushButton_clear_->setStyleSheet("QPushButton {"
                                         "   background-color: rgb(60, 179, 113);"
                                         "   color: rgb(255, 255, 255);"
                                         "   border: 2px solid rgb(144, 238, 144);"
                                         "   border-radius: 5px;"
                                         "   padding: 5px;"
                                         "}"
                                         "QPushButton:hover {"
                                         "   background-color: rgb(50, 205, 50);"
                                         "}");
    ui->pushButton_connect_->setStyleSheet("QPushButton {"
                                           "   background-color: rgb(60, 179, 113);"
                                           "   color: rgb(255, 255, 255);"
                                           "   border: 2px solid rgb(144, 238, 144);"
                                           "   border-radius: 5px;"
                                           "   padding: 5px;"
                                           "}"
                                           "QPushButton:hover {"
                                           "   background-color: rgb(50, 205, 50);"
                                           "}");

    ui->groupBox_menu_->setStyleSheet("QGroupBox {"
                                      "    border: 2px solid rgb(169, 169, 169);"
                                      "    margin-top: 20px;"
                                      "}"
                                      "QGroupBox::title {"
                                      "    subcontrol-origin: margin;"
                                      "    subcontrol-position: top left;"
                                      "    padding: 0 1px;"
                                      "    color: black;"

                                      "}"
                                      "QLabel {"
                                      "     color: black;"

                                      "}"
                                      "QLineEdit {"
                                      "    background-color: white;"
                                           "border: 1px solid rgb(192, 192, 192);"
                                      "    color: black;"
                                      "}");

    ui->groupBox_buttons_->setStyleSheet("QGroupBox {   border: none; }");
    ui->lineEdit_name_host_->setText("981757-ca08998.tmweb.ru");
    ui->lineEdit_port_->setText("5432");
    ui->lineEdit_name_bd_->setText("demo");
    ui->lineEdit_user_->setText("netology_usr_cpp");
    ui->lineEdit_user_password_->setText("CppNeto3");

    QPixmap pixmap("://images/plane.jpg");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);

    myDataBase = new DataBase(this);
    msg  = new QMessageBox(this);
    timer = new QTimer(this);
    myDataBase->addDataBase(POSTGRE_DRIVER, DB_NAME);
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    connect(myDataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::slot_status_connection);
    connect(timer, &QTimer::timeout, this, &MainWindow::slot_refresh_connection);
    myConnect();

}

MainWindow::~MainWindow()
{
    myDataBase->disconnectFromDataBase(DB_NAME);
    delete ui;
}

void MainWindow::on_pushButton_connect__clicked()
{
    myConnect();
    qDebug() << myDataBase->isOpen();

}

void MainWindow::slot_status_connection(bool flag){
    connectionStatus = flag;
    if(!flag){
        msg->setText(myDataBase->getLastError().text());
        msg->setIcon(QMessageBox::Critical);
        timer->start(5000);
        msg->show();

    }

}


void MainWindow::on_pushButton_clear__clicked()
{
    if(ui->tabWidget_main_->currentIndex() == 0)
    {
        ui->lineEdit_name_bd_->clear();
        ui->lineEdit_name_host_->clear();
        ui->lineEdit_port_->clear();
        ui->lineEdit_user_->clear();
        ui->lineEdit_user_password_->clear();
    }
}

void MainWindow::slot_refresh_connection()
{
    msg->close();
    myConnect();
}

void MainWindow::myConnect()
{
    if(ui->label_status_connect_->text() == "Отключено")
    {
        dataForConnect[HOST_NAME_] = ui->lineEdit_name_host_->text();
        dataForConnect[DBNAME_] = ui->lineEdit_name_bd_->text();
        dataForConnect[LOGIN_] = ui->lineEdit_user_->text();
        dataForConnect[PASS_] = ui->lineEdit_user_password_->text();
        dataForConnect[PORT_] = ui->lineEdit_port_->text();
        myDataBase->connectToDataBase(dataForConnect);
        if(connectionStatus){
            ui->label_status_connect_->setText("Подключено");
            ui->pushButton_connect_->setText("Отключится");
        }
    }
    else if(ui->label_status_connect_->text() == "Подключено")
    {
        ui->label_status_connect_->setText("Отключено");
        ui->pushButton_connect_->setText("Подключится");
        myDataBase->disconnectFromDataBase(DB_NAME);
    }
}

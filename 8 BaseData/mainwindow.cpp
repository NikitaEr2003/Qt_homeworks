#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qdebug.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Исходное состояние виджетов
    ui->setupUi(this);


    /*
     * Выделим память под необходимые объекты. Все они наследники
     * QObject, поэтому воспользуемся иерархией.
    */

    dataBase = new DataBase(this);

    msg = new QMessageBox(this);



    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);

    ui->button_clear_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->button_exit_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->button_clear_request_->setStyleSheet("QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->button_request_->setStyleSheet("QPushButton { color: red; } ");
    ui->lineEdit_request_->setStyleSheet("QLineEdit { color: red; } ");
    ui->button_connect_->setStyleSheet("QPushButton { color: red; } "
                                       "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
    ui->line_edit_login_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }");
    ui->line_edit_password_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }");
    ui->line_edit_name_base_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }");
    ui->line_edit_name_host_->setStyleSheet("QLineEdit:hover { background-color: rgba(144, 238, 144, 0.5); }");
    ui->spin_box_port_->setStyleSheet("QSpinBox:hover { background-color: rgba(144, 238, 144, 0.5); }");
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0, "Connection");
    ui->tabWidget->setTabText(1, "Accepting Data");
    ui->groupBox_data_->setObjectName("groupBox_data_");
    ui->groupBox_data_->setStyleSheet("#groupBox_data_{border:0}");
    ui->button_request_->setEnabled(false);
    ui->lineEdit_request_->setEnabled(false);
    ui->lineEdit_request_->setText("Add request here");
    ui->line_edit_name_host_->setText("981757-ca08998.tmweb.ru");
    ui->line_edit_name_base_->setText("netology_cpp");
    ui->spin_box_port_->setValue(5432);
    ui->line_edit_login_->setText("netology_usr_cpp");
    ui->line_edit_password_->setText("CppNeto3");
    ui->button_connect_->setText("Disconnected");

    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    ui->lineEdit_request_->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    connect(this, &MainWindow::sig_SendFull, dataBase, &DataBase::slot_ChangeCheckFull);
    connect(this, &MainWindow::sig_RequestToDb, dataBase, &DataBase::slot_RequestToDB);
    ui->lineEdit_request_->setText("SELECT title, description FROM film f JOIN film_category fc on f.film_id = fc.film_id JOIN category c on c.category_id = fc.category_id WHERE c.name = 'Comedy' OR c.name = 'Horror'");
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status){
        ui->tabWidget->setCurrentIndex(1);
        ui->button_connect_->setText("Connected");
        ui->button_connect_->setStyleSheet("QPushButton { color: green; } "
                                           "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->button_request_->setEnabled(true);
        ui->button_request_->setStyleSheet("QPushButton { color: green; } " "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->lineEdit_request_->setEnabled(true);
        ui->lineEdit_request_->setStyleSheet("QLineEdit { color: green; } ");

    }
    else{
        ui->tabWidget->setCurrentIndex(0);
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->button_connect_->setText("Disconnected");
        ui->button_connect_->setStyleSheet("QPushButton { color: red; } "
                                           "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->button_request_->setEnabled(false);
        ui->button_request_->setStyleSheet("QPushButton { color: red; } ");
        ui->lineEdit_request_->setEnabled(false);
        ui->lineEdit_request_->setStyleSheet("QLineEdit { color: red; } ");
        msg->exec();
    }

}


void MainWindow::on_button_clear__clicked()
{
    if(ui->tabWidget->currentIndex() == 0){
        ui->line_edit_login_->clear();
        ui->line_edit_name_base_->clear();
        ui->line_edit_name_host_->clear();
        ui->line_edit_password_->clear();
        ui->spin_box_port_->setValue(0);
    }else{
        TypeOfClear = dataBase->GetModelType();
        if(TypeOfClear ==  ClearTableView::FullTable)
        {
            auto ptr_table_model = dataBase->GetModelTable();
            ptr_table_model->clear();
        }else if(TypeOfClear ==  ClearTableView::Request)
        {
            auto ptr_table_query = dataBase->GetModelQuery();
            ptr_table_query->clear();
        }else{
            qDebug() << "Она пустая и так" << Qt::endl;
        }
    }
}

void MainWindow::on_button_connect__clicked()
{
    AcceptDataFromText();

    if(ui->button_connect_->text() == "Disconnected"){
        ui->button_connect_->setText("Connected");
        ui->button_connect_->setStyleSheet("QPushButton { color: green; } "
                                           "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->button_request_->setEnabled(true);
        ui->button_request_->setStyleSheet("QPushButton { color: green; } " "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->lineEdit_request_->setEnabled(true);
        ui->lineEdit_request_->setStyleSheet("QLineEdit { color: green; } ");
        dataBase->ConnectToDataBase(dataForConnect);

    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->tabWidget->setCurrentIndex(0);
        ui->button_connect_->setText("Disconnected");
        ui->button_connect_->setStyleSheet("QPushButton { color: red; } "
                                           "QPushButton:hover { background-color: rgba(199, 171, 171, 0.55); }");
        ui->button_request_->setEnabled(false);
        ui->button_request_->setStyleSheet("QPushButton { color: red; } ");
        ui->lineEdit_request_->setEnabled(false);
        ui->lineEdit_request_->setStyleSheet("QLineEdit { color: red; } ");

    }

}

void MainWindow::AcceptDataFromText()
{
    dataForConnect[HOST_NAME_] = ui->line_edit_name_host_->text(),
    dataForConnect[DBNAME_] = ui->line_edit_name_base_->text();
    dataForConnect[LOGIN_] = ui->line_edit_login_->text();
    dataForConnect[PASS_] = ui->line_edit_password_->text();
    dataForConnect[PORT_] = ui->spin_box_port_->text();

}

void MainWindow::on_button_request__clicked()
{
    if(ui->checkBox_full_table_->isChecked()){
        emit sig_SendFull(true);
        QSqlTableModel * ptr_table = dataBase->GetModelTable();
        ui->tableView_results_->setModel(ptr_table);
        ui->tableView_results_->setWindowTitle("Data View");


    }else{
        QString receiv = ui->lineEdit_request_->text();
        emit sig_RequestToDb(receiv);
        emit sig_SendFull(false);
        QSqlQueryModel * ptr_query = dataBase->GetModelQuery();
        ui->tableView_results_->setModel(ptr_query);
        ui->tableView_results_->setWindowTitle("Data View");

    }
}

void MainWindow::on_button_exit__clicked()
{
    this->close();
}

void MainWindow::on_button_clear_request__clicked()
{

    ui->lineEdit_request_->setText("Add request here");

}

void MainWindow::on_checkBox_full_table__checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == Qt::Checked){
        ui->lineEdit_request_->setEnabled(false);
    }else if(arg1 == Qt::Unchecked){
        ui->lineEdit_request_->setEnabled(true);
    }

}


#include "workload.h"
#include "ui_workload.h"

workload::workload(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::workload)
{
    ui->setupUi(this);
    ui->tabWidget_year_and_month_->setTabText(0, "Загруженность за год");
    ui->tabWidget_year_and_month_->setTabText(1, "Загруженность за месяц");
    chart = new QChart();
    chartView = new QChartView(chart);
    series = new QBarSeries;

}

workload::~workload()
{
    delete ui;
    delete chart;
    delete chartView;
    delete series;
}

#ifndef WORKLOAD_H
#define WORKLOAD_H


#include <QDialog>
#include <QtCharts/QtCharts>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
namespace Ui {
class workload;
}

class workload : public QDialog
{
    Q_OBJECT

public:
    explicit workload(QDialog *parent = nullptr);
    ~workload();

private:
    QChart* chart;
    QChartView* chartView;
    QBarSeries* series;
    Ui::workload *ui;
};

#endif // WORKLOAD_H

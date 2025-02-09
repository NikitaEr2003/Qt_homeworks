#ifndef WORKLOAD_H
#define WORKLOAD_H


#include <QDialog>
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
    Ui::workload *ui;
};

#endif // WORKLOAD_H

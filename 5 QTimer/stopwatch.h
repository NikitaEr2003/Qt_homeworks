#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
class StopWatch : public QObject
{
    Q_OBJECT
public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();
    void setTimeTimer(int time);
    double getTimeTimer();
    void incrementTimer();
    void stopTimer();
    void refreshTimer();
private:
     double duration_timer_ = 0;
     QTimer * timer_;
signals:
     void sendTimeoutSig();
public slots:
     void acceptTimeoutSlot();


};

#endif // STOPWATCH_H

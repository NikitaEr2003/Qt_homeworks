#include "stopwatch.h"
#include <QDebug>
StopWatch::StopWatch(QObject *parent)
    : QObject{parent}
{
    timer_ = new QTimer;
    connect(timer_, &QTimer::timeout, this, &StopWatch::acceptTimeoutSlot);
}

StopWatch::~StopWatch(){
    qDebug() << "Destructor StopWatch" << Qt::endl;
    delete timer_;
}

void StopWatch::setTimeTimer(int time){
    timer_->start(time);
}

double StopWatch::getTimeTimer(){
    return duration_timer_;
}

void StopWatch::incrementTimer(){
    duration_timer_= duration_timer_ + 0.1;
}


void StopWatch::stopTimer(){
    timer_->stop();
}

void StopWatch::refreshTimer(){
    duration_timer_ = 0;
}

void StopWatch:: acceptTimeoutSlot(){
    emit sendTimeoutSig();
}



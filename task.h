#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "sendfiles.h"
#include <QTimer>
#include "docker.h"

class QNetworkAccessManager;
class QStringList;

class Task:public QObject
{
    Q_OBJECT
public:
    explicit Task(QStringList& list, QString& batchName);

    void sendFiles();//调用sendfiles
    void run();//调用docker的run
    void stop();//调用docker的stop
   // void getProgress();//调用docker的getProgress
    static void setNetworkManager(QNetworkAccessManager* netman);

signals:
    void dockerFinished();
    void progressUpdated(int progress);

public slots:

private:
    QString _batchName;
    QStringList _list;
    static QNetworkAccessManager* _netman;
    QTimer *timer;
    Docker* docker;
    int preProgress;
    int curProgress;

};

#endif // TASK_H

#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "sendfiles.h"

class QNetworkAccessManager;
class QStringList;

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QNetworkAccessManager* netman,QStringList& list, QString& batchName,QObject *parent = nullptr);

    void sendFiles();//调用sendfiles
    void run();//调用docker的run
    void stop();//调用docker的stop
    void getProgress();//调用docker的getProgress

signals:

public slots:

private:
    QString _batchName;
    QStringList _list;
    QNetworkAccessManager* _netman;
};

#endif // TASK_H

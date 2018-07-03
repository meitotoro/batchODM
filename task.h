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

private:
    sendFiles();//调用sendfiles
    run();//调用docker的run
    stop();//调用docker的stop
    getProgress();//调用docker的getProgress

signals:

public slots:

private:
    QString _batchName;
    QStringList _list;
    QNetworkAccessManager* _netman;
};

#endif // TASK_H

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
    explicit Task(QStringList& list, QString folder,QString& batchName);

    void sendFiles();//调用sendfiles
    void run();//调用docker的run
    void stop();//调用docker的stop
    void pause();//调用docker的pause
    void restart();//调用docker的restart
   // void getProgress();//调用docker的getProgress
    static void setNetworkManager(QNetworkAccessManager* netman);
    void get_resultFiles();
    bool dockerRun;
    bool aborted;

signals:
    void dockerFinished();
    void progressUpdated(int progress);
    void fileReturned();
    void littleImage();

public slots:

private:
    QString _batchName;
    QString _folder;
    QStringList _list;
    static QNetworkAccessManager* _netman;
    QTimer *timer;
    Docker* docker;
    int preProgress;
    int curProgress;
    SendFiles *files;



};

#endif // TASK_H

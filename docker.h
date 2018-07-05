#ifndef DOCKER_H
#define DOCKER_H
#include <QObject>
#include <QString>

class QNetworkAccessManager;
class Docker:public QObject
{
    Q_OBJECT
public:
    Docker(QString &batchName);
    ~Docker();
    void run(QNetworkAccessManager* netman);
    void stop(QNetworkAccessManager *netman);
    void get_progress(QNetworkAccessManager *netman,int min_progress,int max_progress);
    int get_curProgress();//返回当前的进度值

signals:
    void dockerRun();
    void resultReady();
    void littleImage();

private:
    QString _batchName;
    QWidget* _parent;
    int _curProgress=0;
};

#endif // DOCKER_H

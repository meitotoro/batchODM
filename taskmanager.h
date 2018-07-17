#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <QObject>
#include "task.h"

class QNetworkAccessManager;
class TaskManager:public QObject
{
    Q_OBJECT
public:
    void setParalNum(int num);//设置一次并行任务个数
    void addTask(Task *task);//增加任务
    void runSelected();//运行选中的任务
    void stopSelected();//停止运行选中的任务
    int update(Task task);//更新任务，获取进度,返回进度数组
    void select(int index);//task最后被选中了，返回true
    void deselect(int index);//task没有被选中，返回false
    void pauseSelected(int index);//暂停某个任务
    void restartSelected(int index);//重新启动某个任务
    bool getDockerStatus(int index);//拿到某个task的docker是否运行状态

public:
    TaskManager();

signals:
    void filesSended(int iFile);
    void getPorgress(int iFile,int progress);
    void fileReturned(int iFile);
    void littleImage(int iFile);


private:
    std::vector<Task*> taskList;
    std::vector<bool> selected;
    int _num;
    //QNetworkAccessManager *_netman;

};

#endif // TASKMANAGER_H

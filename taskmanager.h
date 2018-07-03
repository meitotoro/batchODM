#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <QObject>


class TaskManager:public QObject
{
    Q_OBJECT
private:
    setParalNum();//设置一次并行任务个数
    addTask();//增加任务
    runSelected();//运行选中的任务
    stopSelected();//停止运行选中的任务
    update();//更新任务，获取进度
    select();//获取选中的任务
    deselect();//
public:
    TaskManager();
    std::vector<Task> taskList;
    int count;

};

#endif // TASKMANAGER_H

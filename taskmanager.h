#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <QObject>
#include "task.h"


class TaskManager:public QObject
{
    Q_OBJECT
private:
    void setParalNum(int num);//设置一次并行任务个数
    void addTask(Task task);//增加任务
    void runSelected();//运行选中的任务
    void stopSelected();//停止运行选中的任务
    int update(Task task);//更新任务，获取进度,返回进度数组
    void select(int index);//task最后被选中了，返回true
    void deselect(int index);//task没有被选中，返回false

public:
    TaskManager();

private:
    std::vector<Task> taskList;
    std::vector<bool> selected;
    int _num;

};

#endif // TASKMANAGER_H

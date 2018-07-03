#include "taskmanager.h"
#include <QTimer>
TaskManager::TaskManager()
{

}
TaskManager::addTask(Task task){
    taskList.push_back(task);
}

TaskManager::select(Task task){
    taskList_selected.push_back(task);
}
TaskManager::deselect(Task task){
    taskList_deselected.push_back(task);
}
TaskManager::setParalNum(int num){
    _num=num;
}
TaskManager::runSelected(){
    std::deque<2,Task> tasksToSend;
    tasksToSend.push_back(taskList_selected.pop_back());
    tasksToSend.push_back(taskList_selected.pop_back());
    for(Task iter=taskList_selected.begin();iter!=taskList_selected.end();iter++){
        for(int i=0;i<2;i++){
            tasksToSend.push_back(iter);
            iter.sendFiles();
        }
        while(!=tasksToSend.empty()){
            for(int i=0;i<2;i++){
                QTimer timer=new QTimer();
                connect(timer,QTimer::timeout,[=](){
                    int pg=update(iter);
                    if(pg==100){
                        tasksToSend.;
                    }});
            }

        }

    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagelistitem.h"
#include "taskmanager.h"

#include <QDialog>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imagelist->setStyleSheet("#imagelist::Item:hover{background-color:rgb(41, 189, 139);}\n"
                                 "#imagelist::Item:selected{background-color:rgb(0, 148, 98);}");
    //taskManager=new TaskManager();
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog.setModal(true);
    int value=dialog.exec();

    if (value == QDialog::Accepted) {
        QString folder= dialog.folder;
        QString folderName=dialog.folderName;

        ui->imagelist->setResizeMode(QListView::Adjust);
        ui->imagelist->setAutoScroll(true);
        ImageListItem *itemView=new ImageListItem(folder,folderName,ui->imagelist);
        imageList.append(itemView);

        QListWidgetItem *imageItem = new QListWidgetItem(ui->imagelist);
        imageItem->setSizeHint(QSize(0,40));
        ui->imagelist->addItem(imageItem);

        ui->imagelist->setItemWidget(imageItem,itemView);
//        Task task=dialog.task;
//        taskManager->addTask(task);
//        task->setProgressBar(itemView->pb);
    }
}

void MainWindow::on_cb_AllSelected_stateChanged()
{
    if(ui->cb_AllSelected->isChecked()==true){
        for(auto &item:imageList){
            item->cb->setCheckState(Qt::Checked);
        }
    }else{
        for(auto& item:imageList){
            item->cb->setCheckState(Qt::Unchecked);
        }
    }
}


void MainWindow::on_ok_button_clicked()
{
    for(int i=0;i<imageList.size();i++){
        auto &item=imageList[i];
        if(item->cb->checkState()==Qt::Checked){
            taskManager->select(i);
        } else {
            taskManager->deselect(i);
        }
    }
    taskManager->setParalNum(2);//一次运行两个task
    taskManager->runSelected();
}


void MainWindow::on_pushButton_3_clicked()
{
    taskManager->stopSelected();
}

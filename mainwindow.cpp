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
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkRequest>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),netman(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    ui->imagelist->setStyleSheet("#imagelist::Item:hover{background-color:rgb(41, 189, 139);}\n"
                                 "#imagelist::Item:selected{background-color:rgb(0, 148, 98);}");
    taskManager=new TaskManager();
    Task::setNetworkManager(netman);
    
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
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy.MM.dd");
        QString fileName=dialog.folderName+"-"+current_date;
        Task *task=new Task(dialog.fileList,fileName);
        taskManager->addTask(task);
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
    httpConnectTest();
    QEventLoop loop;
    connect(this,&MainWindow::httpConnectSuccess,&loop,&QEventLoop::quit);
    loop.exec();
    for(int i=0;i<imageList.size();i++){
        auto &item=imageList[i];
        if(item->cb->checkState()==Qt::Checked){
            taskManager->select(i);
        } else {
            taskManager->deselect(i);
        }
    }
    taskManager->setParalNum(2);//一次运行两个task
    connect(taskManager,SIGNAL(filesSended(int)),this,SLOT(reminder(int)));
    connect(taskManager,&TaskManager::getPorgress,[=](int iFile,int progress){
        auto &item=imageList[iFile];
        item->pb->setValue(progress);
    });
    taskManager->runSelected();


}
void MainWindow::reminder(int i){
    auto &item=imageList[i];
    item->label->setText("文件传输完成");
}


void MainWindow::httpConnectTest(){
    QUrl url("http://192.168.188.10:9000/httpTest");
    QNetworkRequest request(url);
    QNetworkReply *reply=netman->get(request);
    connect(reply,&QNetworkReply::finished,[=](){
        QNetworkReply::NetworkError code=reply->error();
        if(code==QNetworkReply::ConnectionRefusedError){

            QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("服务器链接不成功,请检查服务器状态"),QMessageBox::Ok);
            reply->abort();
            emit this->httpConnectFailed();
        }
        else{
            emit this->httpConnectSuccess();
        }
    });
}

void MainWindow::on_pushButton_3_clicked()
{
    taskManager->stopSelected();
}

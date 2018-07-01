#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagelistitem.h"

#include <QDialog>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imagelist->setStyleSheet("#imagelist::Item:hover{background-color:rgb(41, 189, 139);}\n"
                                 "#imagelist::Item:selected{background-color:rgb(0, 148, 98);}");
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

        QListWidgetItem *imageItem = new QListWidgetItem(ui->imagelist);
        imageItem->setSizeHint(QSize(0,40));
        ui->imagelist->addItem(imageItem);

        ui->imagelist->setItemWidget(imageItem,itemView);
    }
}

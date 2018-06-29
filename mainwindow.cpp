#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    vLayout=new QVBoxLayout(ui->taskListWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog.setModal(true);
    int value=dialog.exec();

    QString folder= dialog.folder;
    QString folderName=dialog.folderName;
    QWidget *window = new QWidget();
    QCheckBox *cb = new QCheckBox();
    cb->setChecked(true);
    QLabel *folderNameLabel = new QLabel(folderName);
    QLabel *folderLabel = new QLabel(folder);
    QLabel *orthoFlag = new QLabel("正射影像");
    QProgressBar *pb=new QProgressBar();
    pb->setMinimum(0);
    pb->setMaximum(110);
    pb->setValue(0);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(cb);
    layout->addWidget(folderLabel);
    layout->addWidget(folderNameLabel);
    layout->addWidget(orthoFlag);
    layout->addWidget(pb);
    window->setLayout(layout);
    vLayout->addWidget(window);


}

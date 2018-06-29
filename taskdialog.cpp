#include "taskdialog.h"
#include "ui_taskdialog.h"
#include <QFileInfoList>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPalette>

taskDialog::taskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskDialog)
{
    ui->setupUi(this);
}

taskDialog::~taskDialog()
{
    delete ui;
}

void taskDialog::on_ok_button_clicked()
{
    folder=ui->folder->text();
    folderName=ui->folderName->text();
    if(folder!=""&&folderName!="")
    {
        this->close();
    }else{
        QWidget *reminder = new QWidget(ui->widget);
        QLabel *label = new QLabel("*名称不能为空");
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::red);
        QHBoxLayout *layout = new QHBoxLayout;
        label->setPalette(pa);
        layout->addWidget(reminder);
        reminder->setLayout(layout);
        reminder->show();

    }

}

void taskDialog::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this, tr("Open Image"), "D:/test",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    //ui->folderName->text()=filePath;

    ui->folder->setText(filePath);
    QDir dir(filePath);

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    QStringList list=dir.entryList(filters);
    ui->imageList->clear();
    ui->imageList->addItems(list);
    QFileInfoList absoluteList=dir.entryInfoList(filters);
    fileList.clear();
    for(int i=0;i<absoluteList.size();i++){
        fileList.append(absoluteList.at(i).filePath());
    }
}
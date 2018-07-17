#include "imagelistitem.h"
#include "ui_imagelistitem.h"

ImageListItem::ImageListItem(QString folder, QString folderName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageListItem)
{
    ui->setupUi(this);
    ui->folder->setText(folder);
    ui->folderName->setText(folderName);
    cb=ui->checkBox;
    pb=ui->progressBar;
    label=ui->label;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(110);

}

ImageListItem::~ImageListItem()
{
    delete ui;
}

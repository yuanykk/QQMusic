#include "recbox.h"
#include "ui_recbox.h"
#include "recitembox.h"

#include <QJsonObject>
RecBox::RecBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecBox)
    , row(2)
    , col(4)
{
    ui->setupUi(this);
    // recBox.cpp构造函数中添加如下代码
    // RecItemBox* item = new RecItemBox();
    // ui->recListUpHLayout->addWidget(item);
}

RecBox::~RecBox()
{
    delete ui;
}

void RecBox::initRecBoxUi(QJsonArray data, int row)
{


    // 如果是两行，说明当前RecBox是主界面上的supplyMusicBox
    if(2 == row)
    {
        this->row = row;
        this->col = 8;
    }
    else
    {
        // 否则：只有一行，为主界面上recMusicBox
        ui->recPageDown->hide();
        this->row = row;
        this->col = 4;
    }
    // 图片保存起来
    imageList = data;

    // 初始化当前页面索引
    currentIndex = 0;
    totalPages = ceil(imageList.count() / (double)col);
    // 往RecBox中添加图片
    createRecItem();

}

void RecBox::createRecItem()
{
    // 清理 recListUpHLayout 中的所有 RecItemBox 控件
    QList<RecItemBox*> list = ui->recPageUp->findChildren<RecItemBox*>();
    for(auto e : list)
    {
        ui->recListUpHLayout->removeWidget(e);
        delete e;
    }
    if(row == 2)
    {
        QLayout *layout = ui->recListDownHLayout;
        while (layout->count() > 0) {
            QLayoutItem *item = layout->takeAt(0); // 取出并移除项
            if (QWidget *widget = item->widget()) {
                if (RecItemBox *recBox = qobject_cast<RecItemBox*>(widget)) {
                    delete recBox; // 会自动从布局移除（但已通过 takeAt 移除）
                } else {
                    // 如果不是 RecItemBox，可以根据需要处理
                    // 例如重新插入或忽略
                }
            }
            delete item; // 必须删除 QLayoutItem，否则内存泄漏
        }
    }

    // 创建RecBoxItem对象，往RecBox中添加
    // col
    int index = 0;
    for(int i = currentIndex*col; i < col+currentIndex*col /*&& i<imageList.count()*/; ++i)
    {

        RecItemBox* item = new RecItemBox();
        // 设置音乐图片与对应文本
        QJsonObject obj = imageList[i].toObject(); // 会返回空元素，会创建没有图片没有文字的RecItemBox对象，相对与给水平队列末尾站位
        item->setText(obj.value("text").toString());
        item->setImage(obj.value("path").toString());
        // 将RecBoxItem对象添加到RecBox中

        if(index<4)
            ui->recListUpHLayout->addWidget(item);
        else
            ui->recListDownHLayout->addWidget(item);
        index++;
    }

}

void RecBox::on_btUp_clicked()
{
    if(currentIndex==0)return;

    currentIndex--;
    qDebug()<<currentIndex;
    qDebug()<<totalPages;
    createRecItem();
}


void RecBox::on_btDown_clicked()
{
    if(currentIndex==totalPages-1)return;

    currentIndex++;

    createRecItem();
}


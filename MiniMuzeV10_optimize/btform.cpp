#include "btform.h"
#include "qevent.h"
#include "ui_btform.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
btForm::btForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::btForm)
{
    ui->setupUi(this);
    ui->lineBox->hide();
    // // 设置line1的动画效果
     line1Animal = new QPropertyAnimation(ui->line1, "geometry", this);
    // 延迟创建和启动动画 , 虽然ui->setupUi(this); ，但是可能还没完全获取到系统的窗口资源，如果这时候添加动画，动画就会修改控件大小，导致出错
    // QTimer::singleShot 是一个轻量级的延迟执行工具，常用于：
    //  延迟初始化或动画启动

    //          将耗时操作拆分为多次事件处理，避免界面卡顿

    //                  在构造后执行一些需要窗口完全就绪的操作
    // 超时时间 0 的含义：并不是立即执行，而是尽快执行（在当前事件循环的下一次迭代中）。这比直接调用更安全。
    QTimer::singleShot(0, this, [this]() {
        // 再次检查指针是否有效（虽然理论上不会变，但保险）
        if (!ui->line1) {
            qDebug() << "line1 is still null!";
            return;
        }
        line1Animal = new QPropertyAnimation(ui->line1, "geometry", this);
        line1Animal->setDuration(1500);
        line1Animal->setKeyValueAt(0, QRect(2, 0, 2, 15));
        line1Animal->setKeyValueAt(0.5, QRect(2, 15, 2, 1));  // 高度改为1
        line1Animal->setKeyValueAt(1, QRect(2, 0, 2, 15));
        line1Animal->setLoopCount(-1);
        line1Animal->start();
        // 设置line2的动画效果

        line2Animal = new QPropertyAnimation(ui->line2, "geometry", this);
        line2Animal->setDuration(1600);
        line2Animal->setKeyValueAt(0, QRect(13, 0, 2, 15));
        line2Animal->setKeyValueAt(0.5, QRect(13, 15, 2, 1));
        line2Animal->setKeyValueAt(1, QRect(13, 0, 2, 15));
        line2Animal->setLoopCount(-1);
        line2Animal->start();
        // 设置line3的动画效果
        line3Animal = new QPropertyAnimation(ui->line3, "geometry", this);
        line3Animal->setDuration(1700);
        line3Animal->setKeyValueAt(0, QRect(24, 0, 2, 15));
        line3Animal->setKeyValueAt(0.5, QRect(24,15, 2, 1));
        line3Animal->setKeyValueAt(1, QRect(24, 0, 2, 15));
        line3Animal->setLoopCount(-1);
        line3Animal->start();
        // 设置line4的动画效果
        line4Animal = new QPropertyAnimation(ui->line4, "geometry", this);
        line4Animal->setDuration(1800);
        line4Animal->setKeyValueAt(0, QRect(35, 0, 2, 15));
        line4Animal->setKeyValueAt(0.5, QRect(35,15, 2, 1));
        line4Animal->setKeyValueAt(1, QRect(35, 0, 2, 15));
        line4Animal->setLoopCount(-1);
        line4Animal->start();
    });


}

btForm::~btForm()
{
    delete ui;
}

void btForm::setIconAndText(const QString& icon, const QString &text,int pId)
{
    ui->btIcon->setPixmap(QPixmap(icon));
  //ui->btIcon->setScaledContents(true);
    ui->btText->setText(text);
    pageId = pId;
}
// ## Debug
void btForm::mousePressEvent(QMouseEvent *event)
{
    // 1. 点击 左边的按钮时，背景变色
    ui->btStyle->setStyleSheet("#btStyle{ background:rgb(30,206,154);}*{color:#F6F6F6;}");

    event->accept(); // 父组件接收不了  ， QPushbutton 默认情况下处理mousePressEvent事件也是什么也不做，并且不将事件继续传递
    // 2. 发送信号，页面改变
    emit btclicked(this->pageId);

}

int btForm::getPageId()
{
    return pageId;
}

void btForm::clearBackground()
{
    // 将上面void btForm::mousePressEvent(QMouseEvent *event) 里的 qss样式表 重新设置新的样式表
    // 这里没有设置btform按键的背景色，只是设置鼠标悬停效果， 背景颜色默认是跟祖先控件即灰色
    ui->btStyle->setStyleSheet("#btStyle:hover{   background-color:#D8D8D8;}");
}

void btForm::showAnimal(bool isShow)
{
    // 当按钮点击时，根据isShow状态显示或隐藏动画
    if(isShow)
    {
        ui->lineBox->show();
    }
    else
    {
        ui->lineBox->hide();
    }
}



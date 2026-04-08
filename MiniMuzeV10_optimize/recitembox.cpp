#include "recitembox.h"
#include "ui_recitembox.h"

#include <QPropertyAnimation>

RecItemBox::RecItemBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecItemBox)
{
    ui->setupUi(this);


    ui->recMusicImage->installEventFilter(this);
}

RecItemBox::~RecItemBox()
{
    delete ui;
}

bool RecItemBox::eventFilter(QObject *watched, QEvent *event)
{
    // 鼠标触碰到图片以后，需要动画效果， 图片是QLable类， 事件是先经过图片，本应该由QLabel处理，但是我们需要继承QLabel，然后重新对应事件处理函数
    // 为了方便，我们在 QLabel图片 的父组件，即RecItemBox类，添加过滤器，事件会传递到这里
    // 在 Qt 中，事件过滤器必须通过 installEventFilter() 显式安装才会生效。
    // 如果一个控件没有安装任何事件过滤器（即没有其他对象调用过该控件的 installEventFilter），
    // 那么事件不会经过任何“默认过滤器”，而是直接进入该控件的 event() 函数进行处理。
    // 因此还需要给recMusicImage实例 ，安装过滤器
    if(watched == ui->recMusicImage)
    {

        if(event->type() == QEvent::Enter)
        {
            int ImgWidget = ui->musicImageBox->width();
            int ImgHeight = ui->musicImageBox->height();

            QPropertyAnimation* animation = new QPropertyAnimation(ui->musicImageBox, "geometry");
            animation->setDuration(150);
            animation->setStartValue(QRect(9,10,ImgWidget,ImgHeight));
            animation->setEndValue(QRect(9, 0, ImgWidget, ImgHeight));
            animation->start();
            // 注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animation
            connect(animation, &QPropertyAnimation::finished, this, [=](){
                delete animation;// 释放内存 ，防止内存泄露
                //qDebug()<<"图片上移动画结束";
            });
            return true;
        }
        else if(event->type() == QEvent::Leave)
        {
            int ImgWidget = ui->musicImageBox->width();
            int ImgHeight = ui->musicImageBox->height();
            QPropertyAnimation* animation = new QPropertyAnimation(ui->musicImageBox, "geometry");
            animation->setDuration(150);
            animation->setStartValue(QRect(9, 0, ImgWidget, ImgHeight));
            animation->setEndValue(QRect(9,10,ImgWidget,ImgHeight));
            animation->start();
            // 注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animation
            connect(animation, &QPropertyAnimation::finished, this, [=](){
                delete animation; // 释放内存 ，防止内存泄露
                //qDebug()<<"图片下移动画结束";
            });
            return true;
        }
    }

    return QObject::eventFilter(watched,event);
}

void RecItemBox::setText(const QString &text)
{
    ui->recBoxItemText->setText(text);
}

void RecItemBox::setImage(const QString &path)
{
    QString qss = "border-image:url("+path+");";
    ui->recMusicImage->setStyleSheet(qss);
}

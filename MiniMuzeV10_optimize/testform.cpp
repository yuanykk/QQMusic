#include "testform.h"
#include "ui_testform.h"
#include <QGraphicsDropShadowEffect>

TestForm::TestForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestForm)
{
    ui->setupUi(this);
    //#1.设置无边框窗口，即窗口将来无标题栏
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);//无边框窗口。没有标题栏和标准边框，常用于自定义皮肤或悬浮窗。

    setAttribute(Qt::WA_TranslucentBackground); // 让当前窗口变透明

    //setWindowFlag(Qt::FramelessWindowHint);
    //setWindowFlag(Qt::NoDropShadowWindowHint);

    // // // 自定义阴影效果
    //QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);  // 阴影位于 窗口 左上角
    // shadowEffect->setColor("#646464"); // 阴影颜色
    // shadowEffect->setBlurRadius(10); // 圆角效果
    shadowEffect->setColor(Qt::green); // 阴影颜色
    shadowEffect->setBlurRadius(15); // 圆角效果
    ui->bg->setGraphicsEffect(shadowEffect);
}

TestForm::~TestForm()
{
    delete ui;
}

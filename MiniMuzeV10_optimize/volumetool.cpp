#include "volumetool.h"
#include "ui_volumetool.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>

VolumeTool::VolumeTool(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VolumeTool)
    , isMuted(false) // 默认静音
    , volumeRatio(20) // 默认音量为20%
{
    ui->setupUi(this);
    //#1.设置无边框窗口，即窗口将来无标题栏
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);//无边框窗口。没有标题栏和标准边框，常用于自定义皮肤或悬浮窗。

    setAttribute(Qt::WA_TranslucentBackground); // 让当前窗口变透明

    // // // 自定义阴影效果
    //QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);  // 阴影位于 窗口 左上角
    //shadowEffect->setColor("#646464"); // 阴影颜色
    shadowEffect->setColor(QColor(255, 255, 0, 100)); // 阴影颜色

    shadowEffect->setBlurRadius(10); // 圆角效果
    ui->volumeWidget->setGraphicsEffect(shadowEffect);

    // 总结 ：设置 volumetool 的 窗口属性，窗口外观的类型，允许窗口透明
    // ① 窗口类型 是 弹出的方式
    // ② 无边框
    // ③ 禁用窗口的默认阴影效果，自己创建一个阴影效果

    // 给按钮设置图标
    ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    // 音量的默认大小是20
    ui->outSlider->setGeometry(ui->outSlider->x(), ui->outSlider->y()+180-180*0.2, ui->outSlider->width(), 180*0.2);
    ui->sliderBtn->move(ui->sliderBtn->x(), ui->outSlider->y() - ui->sliderBtn->height()/2);
    ui->volumeRatio->setText("20%");

    // 关联静音按钮的信号槽
    connect(ui->silenceBtn, &QPushButton::clicked, this,&VolumeTool::onSilenceBtnClicked);

    // 安装事件过滤器
    ui->sliderBox->installEventFilter(this);
}


VolumeTool::~VolumeTool()
{
    delete ui;
}

void VolumeTool::paintEvent(QPaintEvent *event)
{
    (void)event;
    // 1. 创建绘图对象
    QPainter painter(this);
    // 2. 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 3. 设置画笔
    // 没有画笔时：画出来的图形就没有边框和轮廓线
    painter.setPen(Qt::NoPen);
    // 4. 设置画刷颜色
    painter.setBrush(QColor(217,217,217));
    // 创建一个三角形
    QPolygon polygon;
    polygon.append(QPoint(38, 310));
    polygon.append(QPoint(62, 310));
    polygon.append(QPoint(50, 328));
    // 绘制三角形
    painter.drawPolygon(polygon);
}



void VolumeTool::onSilenceBtnClicked()
{
    isMuted = !isMuted;
    if(isMuted)
    {
        ui->silenceBtn->setIcon(QIcon(":/images/silent.png"));
    }
    else
    {
        ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    }
    emit setSilence(isMuted);

}

bool VolumeTool::eventFilter(QObject *object, QEvent *event)
{
    // 过滤volumeBox上的事件
    if(object == ui->sliderBox)
    {
        if(event->type() == QEvent::MouseButtonPress)// 鼠标点击
        {
            // 如果是鼠标按下事件，修改sliderBtn和outLine的位置，并计算volumeRation
            setVolume();
            emit setMusicVolume(volumeRatio);
        }
        else if(event->type() == QEvent::MouseMove) // 鼠标长按
        {
            // 如果是鼠标滚动事件，修改sliderBtn和outLine的位置，并计算volumeRation，
            setVolume();
            // 并发射setMusicVolume信号
            emit setMusicVolume(volumeRatio);
        }else if(event->type() == QEvent::MouseButtonRelease)// 鼠标释放
        {
            // 如果是鼠标释放事件，直接发射setMusicVolume信号
            emit setMusicVolume(volumeRatio);
        }

        return true;
    }

    return QObject::eventFilter(object, event);
}

void VolumeTool::setVolume()
{
    // 1. // 获取当前鼠标全局坐标QCursor().pos()).y()  ,
    //   然后转换为sliderBox的相对坐标mapFromGlobal(QCursor().pos()).y()
    int height = ui->sliderBox->mapFromGlobal(QCursor().pos()).y();
    // 2. 鼠标在volumeBox中可移动的y范围在[25, 205之间]
    height = height < 25? 25 : height;
    height = height > 205? 205 : height;
    // 3. 更新outline的位置和大小
    ui->outSlider->setGeometry(ui->outSlider->x(), height, ui->outSlider->width(),205 - height);
    // 4. sliderBtn 可以依赖outSlider， 即先设置outSlider 再设置 sliderBtn
    ui->sliderBtn->move(ui->sliderBtn->x(), ui->outSlider->y() - ui->sliderBtn->height()/2);

    // 5. 计算音量比率
    volumeRatio = (int)((int)ui->outSlider->height()/(float)180*100);
    // 6. 设置给label显示出来
    ui->volumeRatio->setText(QString::number(volumeRatio)+"%");

}



















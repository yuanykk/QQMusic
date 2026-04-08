#include "musicslider.h"
#include "ui_musicslider.h"

MusicSlider::MusicSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MusicSlider)
{
    ui->setupUi(this);
    // 初始情况下，还没有开始播放，将当前播放进度设置为0
    currentPos = 0;
    maxWidth = width();
    moveSilder();
}

MusicSlider::~MusicSlider()
{
    delete ui;
}

void MusicSlider::mousePressEvent(QMouseEvent *event)
{
    // 注意：QMouseEvent中的pos()为鼠标相对于widget的坐标，不是相当于screen
    // 因此鼠标位置的 x 坐标可直接作为outLine的宽度
    // event->pos() 是相对于 MusicSlider
    currentPos = event->pos().x();
    moveSilder();
    //emit setMusicSliderPosition((double)currentPos / (double)maxWidth);
}

void MusicSlider::mouseMoveEvent(QMouseEvent *event)
{
    // 如果鼠标不在MusicSlider的矩形内，不进行拖拽
    // QRect rect = QRect(0, 0, width(), height());
    // QPoint pos = event->pos();
    // if(!rect.contains(pos))
    // {
    //     return;
    // }
    // 根据鼠标滑动的位置更新outLine的宽度
    if(event->buttons() == Qt::LeftButton)
    {
        // 验证：鼠标点击的x坐标是否越界，如果越界将其调整到边界
        currentPos = event->pos().x();
        if(currentPos < 0)
        {
            currentPos = 0;
        }
        if(currentPos > maxWidth)
        {
            currentPos = maxWidth;
        }
        moveSilder();
        emit setMusicSliderPosition((double)currentPos / (double)maxWidth);
    }


}

void MusicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    // event->pos() 是相对于 MusicSlider
    currentPos = event->pos().x();
    moveSilder();
    emit setMusicSliderPosition((double)currentPos / (double)maxWidth);
}

void MusicSlider::moveSilder()
{
    ui->outLine->setGeometry(ui->outLine->x(),ui->outLine->y(),currentPos,ui->outLine->height());
    repaint();
}

void MusicSlider::setStep(double bf)
{
    currentPos = maxWidth*bf;
    moveSilder();
}

#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class MusicSlider;
}

class MusicSlider : public QWidget
{
    Q_OBJECT

public:
    explicit MusicSlider(QWidget *parent = nullptr);
    ~MusicSlider();

    void mousePressEvent(QMouseEvent *event); // 重写鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event); // 重写鼠标滚动事件
    void mouseReleaseEvent(QMouseEvent *event); // 重写鼠标释放事件
    void moveSilder(); // 修改outLine的宽度为currentPos
    void setStep(double bf);
signals:
    void setMusicSliderPosition(double);
private:
    Ui::MusicSlider *ui;
    int currentPos; // 滑动条当前位置 px为单位 当前最大值是800px
    int maxWidth;

};

#endif // MUSICSLIDER_H

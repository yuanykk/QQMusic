#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>

namespace Ui {
class VolumeTool;
}

class VolumeTool : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeTool(QWidget *parent = nullptr);
    ~VolumeTool();
    // volumetool.h中新增
    void paintEvent(QPaintEvent *event);
    // 事件过滤器
    bool eventFilter(QObject* object, QEvent* event);
    void setVolume();
public slots:
    void onSilenceBtnClicked(); // 静音按钮槽函数
signals:
    void setSilence(bool); // 设置静音信号
    // volumetool.h 中新增
    // 发射修改音量大小槽函数
    void setMusicVolume(int volume);// 音量改变信号


private:
    Ui::VolumeTool *ui;
    bool isMuted; // 记录静音或非静音，当点击静音按钮时，在true和false之间切换
    int volumeRatio; // 标记音量大小
};

#endif // VOLUMETOOL_H

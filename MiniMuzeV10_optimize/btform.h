#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#include <QString>
#include <QPropertyAnimation>
namespace Ui {
class btForm;
}

class btForm : public QWidget
{
    Q_OBJECT

public:
    explicit btForm(QWidget *parent = nullptr);
    ~btForm();
    void setIconAndText(const QString &icon,const QString& text,int pageId);

    void mousePressEvent(QMouseEvent *event);
    int getPageId();
    void clearBackground();
    // 显示动画效果
    void showAnimal(bool flag);

signals:
    void btclicked(int Id);  // 鼠标点击键事件发生时，发送这个信号 ，返回pageId



private:
    Ui::btForm *ui;
    int pageId; // 按键 对应  的 page 页
    // linebox动画起伏效果
    QPropertyAnimation *line1Animal;
    QPropertyAnimation *line2Animal;
    QPropertyAnimation *line3Animal;
    QPropertyAnimation *line4Animal;
};

#endif // BTFORM_H

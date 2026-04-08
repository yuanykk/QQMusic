#ifndef RECBOX_H
#define RECBOX_H

#include <QJsonArray>
#include <QWidget>

namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();
    void initRecBoxUi(QJsonArray data, int row);
    void createRecItem();
private slots:
    void on_btUp_clicked();

    void on_btDown_clicked();

private:
    Ui::RecBox *ui;
    int row; // 记录当前RecBox实际总行数
    int col; // 记录当前RecBox实际每行有几个元素
    QJsonArray imageList; // 保存界面上的图片, 里面实际为key、value键值对
    int currentIndex; // 当前 第几页
    int totalPages; // 总页
};

#endif // RECBOX_H

#ifndef RECITEMBOX_H
#define RECITEMBOX_H

#include <QWidget>

namespace Ui {
class RecItemBox;
}

class RecItemBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecItemBox(QWidget *parent = nullptr);
    ~RecItemBox();
    // RecBoxItem.h 新增
    bool eventFilter(QObject *watched, QEvent *event);
    void setText(const QString& text);
    void setImage(const QString& path);

private:
    Ui::RecItemBox *ui;
};

#endif // RECITEMBOX_H

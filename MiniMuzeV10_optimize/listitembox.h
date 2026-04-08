#ifndef LISTITEMBOX_H
#define LISTITEMBOX_H

#include <QWidget>

namespace Ui {
class ListItemBox;
}

class ListItemBox : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemBox(QWidget *parent = nullptr);
    ~ListItemBox();

    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void setMusicName(const QString& name);
    void setSinger(const QString& name);
    void setAlbumName(const QString& name);
    void setLikeIcon(bool flag);
private slots:
    void on_likeBtn_clicked();

signals:
    void onLikeBtnClicked(bool liked); // 按钮点击槽函数

private:
    Ui::ListItemBox *ui;
    bool m_hovered;
    bool liked;
};

#endif // LISTITEMBOX_H

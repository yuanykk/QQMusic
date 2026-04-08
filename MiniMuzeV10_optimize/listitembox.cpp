#include "listitembox.h"
#include "ui_listitembox.h"

ListItemBox::ListItemBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListItemBox)
{
    ui->setupUi(this);
    // likeBtn按钮连接其点击槽函数
    // connect(ui->likeBtn, &QPushButton::clicked, this,
    //         &ListItemBox::onLikeBtnClicked);
}

ListItemBox::~ListItemBox()
{
    //qDebug() << "ListItemBox 销毁";
    delete ui;
}




void ListItemBox::leaveEvent(QEvent *event) {
    setStyleSheet("");
}

void ListItemBox::setMusicName(const QString &name)
{
    ui->musicNameLabel->setText(name);
}

void ListItemBox::setSinger(const QString &name)
{
    ui->musicSingerLabel->setText(name);
}

void ListItemBox::setAlbumName(const QString &name)
{
    ui->albumNameLabel->setText(name);
}

void ListItemBox::setLikeIcon(bool flag)
{
   // ui->likeBtn->setText("");
    this->liked = flag;
    if(liked)
        ui->likeBtn->setIcon(QIcon(":/images/like_2.png"));
    else
        ui->likeBtn->setIcon(QIcon(":/images/like_3.png"));
    // 设置图标显示大小（而不是按钮大小）
    ui->likeBtn->setIconSize(QSize(13, 13));
    // 可选：调整按钮大小以适应图标
   // ui->likeBtn->resize(32, 32);  // 按钮比图标稍大一点，便于点击
}

void ListItemBox::enterEvent(QEnterEvent *event)
{
    setStyleSheet("background-color:#EFEFEF");
}

void ListItemBox::on_likeBtn_clicked()
{
    liked = !liked;
    setLikeIcon(liked);
    emit onLikeBtnClicked(liked);
}


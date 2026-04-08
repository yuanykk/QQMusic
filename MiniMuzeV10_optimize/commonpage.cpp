#include "commonpage.h"
#include "listitembox.h"
#include "ui_commonpage.h"

CommonPage::CommonPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommonPage)
{
    ui->setupUi(this);
    // 不要水平滚动条
    ui->pageMusicList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // playAllBtn按钮的信号槽处理
    // 当播放按钮点击时，发射playAll信号，播放当前页面的所有歌曲
    // playAll信号交由QQMusic中处理
    connect(ui->playAllBtn, &QPushButton::clicked, this, [=](){
        emit playAll(musciPageType);
    });

    //
    connect(ui->pageMusicList, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem*item){
        // 鼠标双击后，发射信号告诉QQMusic，博能放this页面中共被双击的歌曲
        // 获取双击项的行索引（从0开始）
        int index = ui->pageMusicList->row(item);

        // 发射自定义信号，携带索引或 item 信息
        emit doubleclickedItem(this, index);  // 或者传递 item 本身
    });

}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setCommonPageUI(const QString &title, const QString &image)
{
    ui->pageTittle->setText(title);
    ui->musicImageLabel->setPixmap(QPixmap(image));
    ui->musicImageLabel->setScaledContents(true);


    // 测试
   //  ListItemBox* listItemBox = new ListItemBox(this);
   // // listItemBox->setAttribute(Qt::WA_Hover, true);
   //  QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
   //  // 给QListWidgetItem设置宽高
   //  listWidgetItem->setSizeHint(QSize(ui->pageMusicList->width(), 45)); // 默认情况QListWidgetItem sizeHint() 为-1，-1，

   //  ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox); // 插入一个QListWidgetItem  +  再插入自定义控件ListItemBox
}

void CommonPage::setPageTYpe(MusicListType type)
{
    musciPageType = type;
}

void CommonPage::addMusicTomusicOfPage(MusicList &musicList)
{

    for(auto& music : musicList)
    {
        switch(musciPageType)
        {
            case LIKE_PAGE:
                if(music.getIsLike())
                {
                    musicOfPage.push_back(music.getMusicId());
                }
                break;
            case LOCAL_PAGE:
                    musicOfPage.push_back(music.getMusicId());
                break;
            case HISTORY_PAGE:
                if(music.getIsHistory())
                {
                    //qDebug()<<"musicOfPage加入";
                    musicOfPage.push_back(music.getMusicId());
                }
                break;
            default:
                qDebug()<<"还没有这个类型的页";

        }
    }
}

void CommonPage::reFresh(MusicList &musicList)
{
    // 1.先清空
    musicOfPage.clear();
    ui->pageMusicList->clear();

    addMusicTomusicOfPage(musicList);
    // 遍历歌单，将歌单中的歌曲显示到界面
    for(auto musicId : musicOfPage)
    {
        auto it = musicList.findMusicById(musicId);
        if(it == musicList.end()) // 没找到
            continue;
        ListItemBox* listItemBox = new ListItemBox(ui->pageMusicList);
        listItemBox->setMusicName(it->getMusicName());
        listItemBox->setSinger(it->getSingerName());
        listItemBox->setAlbumName(it->getAlbumName());
        listItemBox->setLikeIcon(it->getIsLike());
        QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
        listWidgetItem->setSizeHint(QSize(ui->pageMusicList->width(), 45));
        ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox);
        /*

            在您提供的代码中，ListItemBox 对象被设置为 QListWidgetItem 的关联控件，而该 QListWidgetItem
            又被添加到了 QListWidget（即 ui->pageMusicList）中。Qt 的内存管理机制确保了当 QListWidget
            被清理（如调用 clear() 或销毁）时，所有 QListWidgetItem 都会被自动删除，而每个 QListWidgetItem 所关联的控件
                （通过 setItemWidget 设置）也会随之被删除。因此，不会发生内存泄漏。
        */
        connect(listItemBox,&ListItemBox::onLikeBtnClicked,this,[=](bool liked){
            emit updateLikeMusic(liked, it->getMusicId());
        });

        // 测试
        //  ListItemBox* listItemBox = new ListItemBox(this);
        // // listItemBox->setAttribute(Qt::WA_Hover, true);
        //  QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
        //  // 给QListWidgetItem设置宽高
        //  listWidgetItem->setSizeHint(QSize(ui->pageMusicList->width(), 45)); // 默认情况QListWidgetItem sizeHint() 为-1，-1，

        //  ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox); // 插入一个QListWidgetItem  +  再插入自定义控件ListItemBox
    }
    // 更新完成后刷新下界面。显示延迟问题
    repaint();


}

void CommonPage::addMusicToPlayer(MusicList &musicList, QVector<QUrl> &playList)
{
    // 根据音乐列表中音乐所属的页面，将音乐添加到playList中
    for(auto music : musicList)
    {
        switch(musciPageType)
        {
        case LOCAL_PAGE:
        {
            playList.push_back(music.getMusicUrl());
            break;
        }
        case LIKE_PAGE:
        {
            if(music.getIsLike())
            {
                playList.push_back(music.getMusicUrl());
            }
            break;
        }
        case HISTORY_PAGE:
        {
            if(music.getIsHistory())
            {
                playList.push_back(music.getMusicUrl());
            }
            break;
        }
        default:
            break;
        }
    }
}

MusicListType CommonPage::getMudciPageType()
{
    return musciPageType;
}

void CommonPage::setImageLabel(const QPixmap &pixMap)
{
    ui->musicImageLabel->setPixmap(pixMap);
    ui->musicImageLabel->setScaledContents(true);
}

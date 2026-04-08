#include "minimuze.h"
#include "ui_minimuze.h"
#include "volumetool.h"

#include <QDir>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QJsonArray>
#include <QJsonObject>
#include <QMenu>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include "recitembox.h"
MiniMuze::MiniMuze(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MiniMuze)
{
    ui->setupUi(this);

    // #1.UI初始化
    initUI();

    // #3. 初始化Sql
    initSql();

    // 初始化播放器
    initPlayer();

    // #2. 链接槽函数
    connectSlotsAndSignals();

    // #3.从数据库读取，初始化musicList
    initMusicList();


}

MiniMuze::~MiniMuze()
{
    delete ui;
}

void MiniMuze::initUI()
{
    // #1.设置无边框窗口，即窗口将来无标题栏
    setWindowFlag(Qt::WindowType::FramelessWindowHint);//无边框窗口。没有标题栏和标准边框，常用于自定义皮肤或悬浮窗。
    setWindowIcon(QIcon(":/images/tubiao.png")); // 设置主窗口图标

    // #2. 窗口边框阴影
    // 1. 设置无边框窗口
    // setWindowFlags(Qt::FramelessWindowHint);

    // 2. 设置背景透明（阴影必需）
    setAttribute(Qt::WA_TranslucentBackground);

    // 3. 创建并设置阴影
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor(0, 0, 0, 100));  // 黑色半透明
    shadowEffect->setBlurRadius(20);  // 更柔和的阴影
    ui->background->setGraphicsEffect(shadowEffect);


    // #
    // 添加托盘
    // 创建托盘图标
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/tubiao.png"));
    // 创建托盘菜单
    QMenu *trayMenu = new QMenu(this);

    trayMenu->addAction("还原", this, &QWidget::showNormal);
    trayMenu->addSeparator();
    trayMenu->addAction("退出", this, &MiniMuze::quitMiniMuze);
    // 将托盘菜单添加到托盘图标
    trayIcon->setContextMenu(trayMenu);
    // 显示托盘
    trayIcon->show();




    // # btform  图标和文本 的 页号初始化
    ui->rec->setIconAndText(":/images/rec.png","推荐",0); // 对应第0页
    ui->music->setIconAndText(":/images/music.png","音乐馆",1);
    ui->audio->setIconAndText(":/images/radio.png","电台",2);
    ui->like->setIconAndText(":/images/like.png","我喜欢",3);
    ui->local->setIconAndText(":/images/local.png","本地下载",4);
    ui->online->setIconAndText(":/images/recent.png","最近播放",5);

    //本地下载BtForm动画默认显示
    ui->local->showAnimal(true);
    ui->stackedWidget->setCurrentIndex(4);


    // 推荐页初始化
    srand(time(NULL));
    ui->recMusicBox->initRecBoxUi(randomPiction(),1);
    ui->supplyMusicBox->initRecBoxUi(randomPiction(),2);


    // 设置我喜欢、本地音乐、最近播放页面
    ui->likePage->setCommonPageUI("我喜欢", ":/images/ilikebg.png");
    ui->localPage->setCommonPageUI("本地音乐", ":/images/localbg.png");
    ui->recentPage->setCommonPageUI("最近播放", ":/images/recentbg.png");



    // 创建音量调节窗口对象并挂到对象树
    volumeTool = new VolumeTool(this);
    connect(volumeTool,&VolumeTool::setMusicVolume,this,&MiniMuze::onMusicVolumeChange);


    // 按钮的背景图片样式去除掉之后，需要设置默认图标
    // 播放控制区按钮图标设定
    ui->play->setIcon(QIcon(":/images/play_2.png")); // 默认为暂停图标
    ui->playMode->setIcon(QIcon(":/images/single_play.png"));// 默认是列表循环


    // 创建歌词页面
    // 创建lrc歌词窗口
    lrcPage = new LrcPage(this);
    lrcPage->hide();
    // 实例化LrcWord对象
    lrcPage = new LrcPage(this);
    lrcPage->hide();

    // lrcPage添加歌词页面上移弹出效果
    lrcAnimation = new QPropertyAnimation(lrcPage, "geometry", this);
    lrcAnimation->setDuration(250);
    lrcAnimation->setStartValue(QRect(10, 10+lrcPage->height(),
                                      lrcPage->width(), lrcPage->height())); // 左上角坐标 + 右下角坐标
    lrcAnimation->setEndValue(QRect(10, 10, lrcPage->width(), lrcPage->height()));// 左上角坐标 + 右下角坐标


}

void MiniMuze::connectSlotsAndSignals()
{
    // 1. btForm 的信号链接
    connect(ui->rec,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);
    connect(ui->music,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);
    connect(ui->audio,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);
    connect(ui->like,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);
    connect(ui->local,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);
    connect(ui->online,&btForm::btclicked,this,&MiniMuze::on_btForm_Click);

    // 2. 绑定收藏按钮的信号
    connect(ui->likePage,&CommonPage::updateLikeMusic,this,&MiniMuze::onUpdateLikeMusic);
    connect(ui->localPage,&CommonPage::updateLikeMusic,this,&MiniMuze::onUpdateLikeMusic);
    connect(ui->recentPage,&CommonPage::updateLikeMusic,this,&MiniMuze::onUpdateLikeMusic);


    // =================
    // 播放器相关
    // 3. 播放按钮
    connect(ui->play,&QPushButton::clicked,this,&MiniMuze::onPlyaBtn);
    //  上一首  下一首
    connect(ui->playUp, &QPushButton::clicked, this,&MiniMuze::onPlayUpClicked);
    connect(ui->playDown, &QPushButton::clicked, this,&MiniMuze::onPlayDownClicked);
    // 4. 播放器状态发送变换
    connect(player,&QMediaPlayer::playbackStateChanged,this,&MiniMuze::onPlayStateChanged);
    // 5. 播放状态改变
    connect(ui->playMode,&QPushButton::clicked,this,&MiniMuze::onPlayModeChanged);

    // 6. 播放全部
    connect(ui->likePage,&CommonPage::playAll,this,&MiniMuze::onPlayAll);
    connect(ui->localPage,&CommonPage::playAll,this,&MiniMuze::onPlayAll);
    connect(ui->recentPage,&CommonPage::playAll,this,&MiniMuze::onPlayAll);

    // 7. 双击Item以后
    connect(ui->likePage,&CommonPage::doubleclickedItem,this,&MiniMuze::onDoubleclickedItem);
    connect(ui->localPage,&CommonPage::doubleclickedItem,this,&MiniMuze::onDoubleclickedItem);
    connect(ui->recentPage,&CommonPage::doubleclickedItem,this,&MiniMuze::onDoubleclickedItem);

    // 8.更新最近播放
    connect(player,&QMediaPlayer::sourceChanged,this,&MiniMuze::onSourceChanged);

    // 9.静音按钮改变信号
    connect(volumeTool, &VolumeTool::setSilence, this,&MiniMuze::setMusicSilence);
    // 10.音量改变信号
    connect(volumeTool, &VolumeTool::setMusicVolume, this,&MiniMuze::onMusicVolumeChange);

    // 11. 音乐总进度 改变信号
    connect(player,&QMediaPlayer::durationChanged,this,&MiniMuze::onDurationChanged);

    // 12. 音乐进度 改变信号
    connect(player,&QMediaPlayer::positionChanged,this,&MiniMuze::onPositionChanged);

    // 13. 拖动进度条 信号
    connect(ui->progressBar,&MusicSlider::setMusicSliderPosition,this,&MiniMuze::onSetMusicSliderPosition);

    // 14. 音乐播放完毕
    connect(player,&QMediaPlayer::mediaStatusChanged,this,&MiniMuze::onMediaStatusChanged);
}

// #2. 拖拽 窗口功能
void MiniMuze::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // 都是全局坐标  计算 鼠标与用户窗口左上角 的相对距离
        // Qt6 的正确写法
        pressOffset = event->globalPosition().toPoint() - this->pos();
        m_checked = true;
    }

}
// #2. 拖拽 窗口功能
void MiniMuze::mouseMoveEvent(QMouseEvent *event)
{
    // buttons 返回所有当前按下的按钮（用于移动事件）
    if(m_checked == true && event->buttons() == Qt::LeftButton)
    {
        move(event->globalPosition().toPoint() - pressOffset);
    }
}

void MiniMuze::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_checked == true && event->button() == Qt::LeftButton)
    {
        pressOffset = QPoint(0,0);
        m_checked = false;
    }
}

void MiniMuze::initPlayer()
{
    // 创建播放器
    player = new QMediaPlayer(this);
    audioOutput= new QAudioOutput(this); //音频输出，指向默认的音频输出设备

    player->setAudioOutput(audioOutput); //设置音频输出
    audioOutput->setVolume(0.2);
    player->setLoops(1); // 只播放一次
    curPage = ui->localPage;
    curIndex = -1;
    curPageType = LOCAL_PAGE;
    mode = RANDOM_TYPE;
    // test
    //player->setSource(QUrl::fromLocalFile("C:\\Users\\26588\\Desktop\\Qt\\MiniMuzeV5_2Player\\musics\\2002年的第一场雪 - 刀郎.mp3"));

}

void MiniMuze::initSql()
{
    // 1.获取 数据库链接
    dbManager = &DbManager::instance();
    // 2.打开数据库
    if(!dbManager->open("MiniMuze.db"))
    {
        qDebug()<<"数据库打开失败："<<dbManager->lastError();
        return;
    }
    qDebug()<<"SQLite连接成功，并创建 [MiniMuze.db] 数据库!!!";
    // 4. 创建数据库表
     QString sql = ("CREATE TABLE IF NOT EXISTS musicInfo(\
                     id INTEGER PRIMARY KEY AUTOINCREMENT,\
                     musicId varchar(200) UNIQUE,\
                     musicName varchar(50),\
                     musicSinger varchar(50),\
                     albumName varchar(50),\
                     duration BIGINT,\
                     musicUrl varchar(256),\
                     isLike INTEGER,\
                     isHistory INTEGER)"
     );
    if(!dbManager->execute(sql)){
        qDebug()<<"创建musicInfo表失败"<<dbManager->lastError()<<"也有坑你是表已经创建了";
        return ;
    }
    qDebug()<<"创建 [musicInfo] 表成功!!!";

}

void MiniMuze::initMusicList()
{
    // 1. 从数据库读取歌曲信息
    readFromDB();
    // 2. 更新CommonPage页面
    // 设置CommonPage的信息
    ui->likePage->setPageTYpe(MusicListType::LIKE_PAGE);
    ui->likePage->reFresh(musicList);

    ui->localPage->setPageTYpe(MusicListType::LOCAL_PAGE);
    ui->localPage->reFresh(musicList);

    ui->recentPage->setPageTYpe(MusicListType::HISTORY_PAGE);
    ui->recentPage->reFresh(musicList);

}


// 点击关闭按钮   -- 槽函数关闭主窗口
void MiniMuze::on_quit_clicked()
{
    // 点击关闭按钮时，程序不退出，隐藏掉
    // 用户可以从系统托盘位置选择显示或者关闭
    hide();
}
// 托盘位置选择退出action
void MiniMuze::quitMiniMuze()
{
    qDebug()<<"test";
    // 更新数据库
    writeToDB();
    // 断开与SQLite的链接
    // sqlite.close(); // 跟随主程序生命周期


    // 这里需要先显示 才能 退出， 即显示窗口的情况下，才能退出，【不知道为什么】
    show();
    this->close();
}

void MiniMuze::on_btForm_Click(int pageid)
{

    // 1.切换 堆叠容器 的页面
    ui->stackedWidget->setCurrentIndex(pageid);
    // 2.还原上一个 btForm 背景色
    // 2.1 首先通过 主窗口 ，就是 对象树的根节点，开始找到，找出所有类型为btForm的对象
    QList<btForm*> list = this->findChildren<btForm*>();
    for(const auto&btform : list)
    {
        if(btform->getPageId() != pageid)
        {
            btform->clearBackground();// 还原 样式表
            btform->showAnimal(false);
        }
        else
        {
            btform->showAnimal(true);
        }
    }


}


// 设置随机图片【歌曲的图片】
QJsonArray MiniMuze::randomPiction()
{
    // 推荐文本 + 推荐图片路径
    QVector<QString> vecImageName;
    vecImageName<<"001.png"<<"003.png"<<"004.png"<<"005.png"<<"006.png"
                 <<"007.png"
                 <<"008.png"<<"009.png"<<"010.png"<<"011.png"<<"012.png"
                 <<"013.png"
                 <<"014.png"<<"015.png"<<"016.png"<<"017.png"<<"018.png"
                 <<"019.png"
                 <<"020.png"<<"021.png"<<"022.png"<<"023.png"<<"024.png"
                 <<"025.png"
                 <<"026.png"<<"027.png"<<"028.png"<<"029.png"<<"030.png"
                 <<"031.png"
                 <<"032.png"<<"033.png"<<"034.png"<<"035.png"<<"036.png"
                 <<"037.png"
                 <<"038.png"<<"039.png"<<"040.png";
    std::random_shuffle(vecImageName.begin(), vecImageName.end());
    // 001.png
    // path: ":/images/rec/"+vecImageName[i];
    // text: "推荐-001"
    QJsonArray objArray;
    for(int i = 0; i < vecImageName.size(); ++i)
    {
        QJsonObject obj;
        obj.insert("path", ":/images/rec/"+vecImageName[i]);
        // arg(i, 3, 10, QCchar('0'))
        // i：要放入%1位置的数据
        // 3: 三位数
        // 10：表示十进制数
        // QChar('0')：数字不够三位，前面用字符'0'填充
        QString strText = QString("推荐-%1").arg(i, 3, 10, QChar('0'));// 数字i，3个字符，每个字符为10进制，不够位数左边用 ‘0’ 填充
        obj.insert("text", strText);
        objArray.append(obj);
    }
    return objArray;
}



void MiniMuze::playOfIndex(int index)
{
    if(index<0)return;
    if(index>=playQueue.count())return;
    player->setSource(playQueue[index]);
    player->play();
}

void MiniMuze::refreshCover(const QUrl &musicUrl)
{
    QMediaPlayer player;
    QEventLoop loop;

    // 连接信号到 loop，当元数据变化时退出循环
    QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, &loop, [&]() {
        loop.quit();
    });

    player.setSource(musicUrl);

    // 设置超时保护 , 等待2ms，如果还没加载到 音频源信息 就读取下一个
    QTimer::singleShot(2000, &loop, &QEventLoop::quit);

    loop.exec(); // 阻塞直到元数据可用或超时

    if(player.mediaStatus()==QMediaPlayer::LoadedMedia)
    {
        // 先通过文件名 获取 歌曲名称 和 歌手名称
        QString musicName;
        QString singerName;
        QString filename = musicUrl.fileName();
        int index = filename.indexOf('-'); //
        // 获取音乐名称
        if(index != -1)
        {
            musicName = filename.mid(0,index).trimmed();
        }
        else
        {
            musicName = filename.mid(0,filename.indexOf('.')).trimmed();
        }
        // 获取歌手名称
        if(index !=-1)
        {
            singerName = filename.mid(index+1,filename.indexOf('.')).trimmed();
        }
        if(musicName.isEmpty())
        {
            musicName = "歌曲未知";
        }
        if(singerName.isEmpty())
        {
            singerName = "歌手未知";
        }
        // 2. 设置歌手、歌曲名称、专辑名称
        ui->musicName->setText(musicName);
        ui->musicSinger->setText(singerName);

        // 3. 设置歌词页面
        lrcPage->setSingerName(singerName);
        lrcPage->setMusciName(musicName);

        // ✅ 元数据已就绪，安全读取
        // QVariant coverVariant = player.metaData().value(QMediaMetaData::CoverArtImage);
        QVariant coverVariant = player.metaData().value(QMediaMetaData::CoverArtImage);
        if(coverVariant.isValid())qDebug()<<"存在";
        QImage coverImage;
        if (coverVariant.isValid() && coverVariant.canConvert<QImage>()) {
            coverImage = coverVariant.value<QImage>();
            // 显示在 QLabel 上
            // 设置封面图片
            ui->musicCover->setPixmap(QPixmap::fromImage(coverImage));
            // 缩放填充到整个Label
            ui->musicCover->setScaledContents(true);
            curPage->setImageLabel(QPixmap::fromImage(coverImage));
        } else {
            // 没有封面图，显示默认占位图
            ui->musicCover->setPixmap(QPixmap(":/images/rec/003.png"));
            // 缩放填充到整个Label
            ui->musicCover->setScaledContents(true);
            curPage->setImageLabel(QPixmap(":/images/rec/003.png"));
        }


        //调试输出
        // qDebug() << "musicName:" << musicName;
        // qDebug() << "Author:" << singerName;
    }
}

void MiniMuze::writeToDB()
{
    for(auto music : musicList)
    {
        // 让music对象将自己写入数据库
        music.insertMusicToDB();
    }

}

void MiniMuze::readFromDB()
{
    QString sql("SELECT musicId,musicName,musicSinger,albumName,\
                duration,musicUrl,isLike,isHistory \
                FROM musicInfo");
    QSqlQuery query(dbManager->database());
    if(!query.exec(sql))
    {
        qDebug()<<"数据库查询失败";
        return;
    }
    while(query.next())
    {
        Music music(QUrl().fromLocalFile(query.value(5).toString()));
        music.setMusicId(query.value(0).toString());
        music.setMusicName(query.value(1).toString());
        music.setSingerName(query.value(2).toString());
        music.setAlbumName(query.value(3).toString());
        music.setDuration(query.value(4).toLongLong());
        music.setMusicUrl(query.value(5).toString());
        music.setIsLike(query.value(6).toBool());
        music.setIsHistory(query.value(7).toBool());
        musicList.push_back(music);

        musicList.insertToSet(query.value(5).toString());

    }
}



void MiniMuze::on_volume_clicked()
{
    // 先要调整窗口的显示位置，否则该窗口在主窗口的左上角
    // 1. 获取该按钮左上角的图标
    QPoint point = ui->volume->mapToGlobal(QPoint(0,0)); // 获取按键的全局坐标，按键是QWidget类，将内部坐标(0,0) 映射为 全局坐标
    // 2. 计算volume窗口 位置  ， 应该在 按键的上面，并且 要中心对齐

    QPoint volumeLeftTop = point - QPoint(volumeTool->width()/2-ui->volume->width()/2, volumeTool->height());
    // 微调窗口位置
    volumeLeftTop.setY(volumeLeftTop.y()+20);
    // volumeLeftTop.setX(volumeLeftTop.x()+15);

    // 3. 移动窗口位置
    volumeTool->move(volumeLeftTop);
    //4. 将窗口显示出来
    volumeTool->show();

}

// 添加歌曲
void MiniMuze::on_addLocal_clicked()
{
    // 1. 创建一个文件对话框
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("添加本地音乐");
    // 2. 创建一个打开格式的文件对话框
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    // 3. 设置对话框模式
    // 只能选择文件，并且一次性可以选择多个存在的文件
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    // 4. 设置对话框的MIME过滤器 ， 有两种过滤器，MIME过滤器 和  后缀过滤器 (.mp3 .text .png )
    QStringList mimeList;
    mimeList<<"application/octet-stream";  // 只要是二进制文件就可以打开
    // mimeList<<"audio/mpeg" ;// 播放类型的文件
    fileDialog.setMimeTypeFilters(mimeList);
    // 5. 设置对话框默认的打开路径,设置目录为当前工程所在目录
    QDir dir(QDir::currentPath());

    dir.cdUp();


    QString musicPath = dir.path()+"/musics/";

    fileDialog.setDirectory(musicPath);
    // 6. 显示对话框，并接收返回值
    // 模态对话框, exec内部是死循环处理
    if(fileDialog.exec() == QFileDialog::Accepted) // 用户点击了 打开按钮
    {
        // 切换到本地音乐界面，因为加载完的音乐需要在本地音乐界面显示
        ui->stackedWidget->setCurrentIndex(4);
        // 获取对话框的返回值
        QList<QUrl> urls = fileDialog.selectedUrls(); // 获取所有的文件路径
        // for(auto val : urls)
        // {
        //     qDebug()<< val.toString();
        // }
        musicList.addMusicsByUrl(urls);

        // 更新 commonpage

        ui->recentPage->reFresh(musicList);
        ui->localPage->reFresh(musicList);
        ui->likePage->reFresh(musicList);



    }
}

void MiniMuze::onUpdateLikeMusic(bool isLike, QString musicId)
{
    // 1.修改MusicList
    for(auto& music : musicList)
    {
        if(music.getMusicId() == musicId)
        {
            music.setIsLike(isLike);
        }
    }

    ui->likePage->reFresh(musicList);
    ui->localPage->reFresh(musicList);
    ui->recentPage->reFresh(musicList);

}

void MiniMuze::onPlyaBtn()
{
    //qDebug()<<"播放按钮点击";
    if(player->playbackState() == QMediaPlayer::PlayingState){
        // 如果是歌曲正在播放中，按下播放键，此时应该暂停播放
        player->pause();
    }
    else if(player->playbackState() == QMediaPlayer::PausedState)
    {
        // 如果是暂停状态，按下播放键，继续开始播放
        player->play();
    }
    else if(player->playbackState() == QMediaPlayer::StoppedState)
    {
        player->play();
    }
}

void MiniMuze::onPlayStateChanged(QMediaPlayer::PlaybackState status)
{
    //qDebug()<<"播放状态改变";
    if(player->playbackState() == QMediaPlayer::PlayingState)
    {
        // 播放状态
        ui->play->setIcon(QIcon(":/images/play_on.png"));
    }
    else
    {
        // 暂停状态
        ui->play->setIcon(QIcon(":/images/play3.png"));
    }
}

void MiniMuze::onPlayModeChanged()
{
    // 播放模式是针对播放列表的
    // 播放模式支持：循环播放、随机播放、单曲循环三种模式
    //qDebug()<<mode;
    if(mode == LOOP_TYPE)
    {
        // 列表循环
        ui->playMode->setToolTip("随机播放");
        mode = RANDOM_TYPE;
        ui->playMode->setIcon(QIcon(":/images/list_play.png"));
    }
    else if(mode == RANDOM_TYPE)
    {
        // 随机播放
        ui->playMode->setToolTip("单曲循环");
        mode = CurrentItemInLoop_TYPE;
        ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));

    }
    else if(mode == CurrentItemInLoop_TYPE)
    {
        ui->playMode->setToolTip("列表循环");
        mode = LOOP_TYPE;
        ui->playMode->setIcon(QIcon(":/images/single_play.png"));
    }
    else
    {
        qDebug()<<"播放模式错误";
    }
}

void MiniMuze::onPlayUpClicked()
{
    // todo
    // 如果是列表循环
    // 如果是单曲循环
    // 如果是随机播放
    qDebug()<<"test";

    if(playQueue.empty())return;
    // 播放下一首
    curIndex--;
    if(curIndex<0){
        curIndex = playQueue.count()-1;
    }
    player->setSource(QUrl(playQueue[curIndex]));
    player->play();
}


// 从最近播放队列里找
void MiniMuze::onPlayDownClicked()
{
    //qDebug()<<"test";
    if(playQueue.empty())return;
    // 播放上一首
    curIndex++;
    if(curIndex>=playQueue.count()){
        curIndex = 0;
    }
    player->setSource(QUrl(playQueue[curIndex]));
    player->play();
}

// 处理 音乐播放完以后， 需要播放下一首
void MiniMuze::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        if(playQueue.empty())return;
        // 播放上一首
        curIndex++;
        if(curIndex>=playQueue.count()){
            curIndex = 0;
        }
        player->setSource(QUrl(playQueue[curIndex]));
        player->play();
    }
}

void MiniMuze::onPlayAll(MusicListType pageType)
{
    //qDebug()<<"test";
    CommonPage* page = nullptr;
     switch(pageType)
     {
        case MusicListType::LIKE_PAGE:
            page = ui->likePage;
            curPageType = LIKE_PAGE;
            break;
        case MusicListType::LOCAL_PAGE:
            page = ui->localPage;
            curPageType = LOCAL_PAGE;
            break;
        case MusicListType::HISTORY_PAGE:
            page = ui->recentPage;
            curPageType = HISTORY_PAGE;
            break;
        default:
            qDebug()<<"扩展";
     }
     // 从当前页面的零号位置开始播放
     playAllOfCommonPage(page, 0);
}


// 切换播放队列，并且播放队列从index下标播放
void MiniMuze::playAllOfCommonPage(CommonPage *commonPage, int index)
{
    playQueue.clear();
    commonPage->addMusicToPlayer(musicList,playQueue);
    //qDebug()<< "Queue:"<<playQueue.count();
    curIndex = index;
    //qDebug()<<"index:"<<index;
    playOfIndex(curIndex);
}


// 双击 Item
void MiniMuze::onDoubleclickedItem(CommonPage *commonPage, int index)
{
    switch(commonPage->getMudciPageType())
    {
    case MusicListType::LIKE_PAGE:
        curPageType = LIKE_PAGE;
        break;
    case MusicListType::LOCAL_PAGE:
        curPageType = LOCAL_PAGE;
        break;
    case MusicListType::HISTORY_PAGE:
        curPageType = HISTORY_PAGE;
        break;
    default:
        qDebug()<<"扩展";
    }
    curPage = commonPage;
    // 从当前页面的零号位置开始播放
    playAllOfCommonPage(curPage, index);
}

// 处理 切换新歌曲信号
void MiniMuze::onSourceChanged(const QUrl &media)
{
    // 1. 更加最近播放QListWidget
    for(auto&music : musicList)
    {
        if(music.getMusicUrl() == media)
        {
            music.setIsHistory(true);
        }
    }
    ui->recentPage->reFresh(musicList);

    // 2. 更新歌曲的封面信息
    refreshCover(media);

    // 3. 更新歌词页面

    // 3.1 解析 lrc文件 获取到歌词信息
    // LrcPage* lrcPage;
    QString lrcPath = media.toString();
    //lrcPath=media.toString(); //"file:///C:/Users/26588/Desktop/Qt/MiniMuzeV8_Lrc_teleprompter/musics/2002年的第一场雪 - 刀郎.mp3"
    // 采用下面toLocalFile ，支持跨系统
    lrcPath=media.toLocalFile();//"C:/Users/26588/Desktop/Qt/MiniMuzeV8_Lrc_teleprompter/musics/2002年的第一场雪 - 刀郎.mp3"
    lrcPath.replace(".mp3",".lrc");
    lrcPath.replace(".flac", ".lrc");
    lrcPath.replace(".mpga", ".lrc");
    lrcPage->parseLrc(lrcPath);



}
// 设置静音
void MiniMuze::setMusicSilence(bool isMuted)
{
    audioOutput->setMuted(isMuted);
}

// 新的音乐加载进来
void MiniMuze::onDurationChanged(qint64 duration)
{
    // arg( Num 几位 10进制 补零 )
    ui->totalTime->setText(QString("%1:%2").arg(duration/1000/60, 2, 10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
    totalDuration = duration;
}

// 参数是 当前音乐播放进度
void MiniMuze::onPositionChanged(qint64 duration)
{
    // 1.arg( Num 几位 10进制 补零 )
    ui->currentTime->setText("      "+QString("%1:%2").arg(duration/1000/60, 2, 10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
    //qDebug()<<ui->currentTime->text();
    // 2.界面上的进度条也需要同步修改
    ui->progressBar->setStep((double)duration / (double)totalDuration);

    // 3. 同步lrc歌词
    lrcPage->showLrcWord(duration);
}

void MiniMuze::onSetMusicSliderPosition(double rate)
{
    // 1. 计算当前seek位置的时长
    qint64 duration = (qint64)(totalDuration * rate);
    // 2. 转换为百分制，设置当前时间
    ui->currentTime->setText("      " + QString("%1:%2").arg(duration/1000/60, 2, 10,QChar('0')).arg(duration/1000%60, 2, 10,QChar('0')));
    // 3. 设置当前播放位置
    player->setPosition(duration);
}



// 设置音量
void MiniMuze::onMusicVolumeChange(int volum)
{
   // qDebug()<<volum;
    audioOutput->setVolume(volum/100.00);
}



void MiniMuze::on_lyrics_clicked()
{
    lrcPage->show();
    lrcAnimation->start();
}


void MiniMuze::on_skin_clicked()
{
    // 换皮肤
    QMessageBox::information(this, "温馨提示", "小哥哥正在加班紧急支持中...");
}


void MiniMuze::on_max_clicked()
{
    // 10. 最大显示问题，因为有些组件采用了固定大小，如果要匹配最大化功能，就需要使用布局管理器来修正窗口大小
    showMaximized();
}


void MiniMuze::on_min_clicked()
{
    //最小化
    showMinimized();
}




#include "music.h"

#include <QStringDecoder>
Music::Music(const QUrl &url)
    : isLike(false)
    , isHistory(false)
    , musicUrl(url)
{
    musicId = QUuid::createUuid().toString();

    //qDebug()<<musicId;
    parseMediaMetaData();
}

// 解析音频文件 的 源信息 （作者名字...）
void Music::parseMediaMetaData()
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
        // 获取元数据（尝试多种可能的字段）
        QMediaMetaData meta = player.metaData();
        // 不能数据是什么编码
        // if(musicName.isEmpty())
        //     musicName  = meta.stringValue(QMediaMetaData::Title);
        // if(singerName.isEmpty())
        //     singerName = meta.stringValue(QMediaMetaData::ContributingArtist);  // 常用艺术家字段

        albumName  = meta.stringValue(QMediaMetaData::AlbumTitle);
        duration = meta.value(QMediaMetaData::Duration).toULongLong();


        if(musicName.isEmpty())
        {
            musicName = "歌曲未知";
        }
        if(singerName.isEmpty())
        {
            singerName = "歌手未知";
        }
        if(albumName.isEmpty())
        {
            albumName = "专辑名未知";
        }

        //调试输出
        // qDebug() << "Title:" << musicName;
        // qDebug() << "Author:" << singerName;
        // qDebug() << "albumName:" << albumName;
        // qDebug() << "Duration:" << duration;


    }
}


void Music::setIsLike(bool isLike)
{
    this->isLike = isLike;
}

void Music::setIsHistory(bool isHistory)
{
    this->isHistory = isHistory;
}
void Music::setMusicName(const QString &musicName)
{
    this->musicName = musicName;
}
void Music::setSingerName(const QString &singerName)
{
    this->singerName = singerName;
}
void Music::setAlbumName(const QString &albumName)
{
    this->albumName = albumName;
}
void Music::setDuration(const qint64 duration)
{
    this->duration = duration;
}
void Music::setMusicUrl(const QUrl &url)
{
    this->musicUrl = url;
}
void Music::setMusicId(const QString &musicId)
{
    this->musicId = musicId;
}
bool Music::getIsLike()
{
    return isLike;
}
bool Music::getIsHistory()
{
    return isHistory;
}

QString Music::getMusicName()
{
    return musicName;
}
QString Music::getSingerName()
{
    return singerName;
}
QString Music::getAlbumName()
{
    return albumName;
}
qint64 Music::getDuration()
{
    return duration;
}
QUrl Music::getMusicUrl()
{
    return musicUrl;
}
QString Music::getMusicId()
{
    return musicId;
}

QString Music::getLrcFilePath() const
{
    // 音频文件和LRC文件在一个文件夹下
    // .mp3 替换为 .lrc
    QString path = musicUrl.toLocalFile();
    path.replace(".mp3", ".lrc");
    path.replace(".flac", ".lrc");
    path.replace(".mpga", ".lrc");
    return path;
}

void Music::insertMusicToDB()
{
    DbManager* db = &DbManager::instance();
    QSqlQuery query(db->database());

    // 1. 检测music是否在数据库中存在
    // 当SELECT 1...查询到结果后，我们需要知道是否存在
    // SELECT EXISTS(子查询) ： 子查询中如果有记录，SELECT EXISTS返回TRUE
    // 如果子查询中没有满足条件的记录， SELECT EXISTS返回FALSE

    query.prepare("SELECT EXISTS (SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    if(!query.exec())
    {
        qDebug()<<"查询失败: "<<query.lastError().text();
        return;
    }
    if(query.next())
    {
        bool isExists = query.value(0).toBool();
        if(isExists)
        {
            // musicId的歌曲已经存在
            // 2. 存在：不需要再插入musci对象，此时只需要将isLike和isHistory属性进行更新
            query.prepare("UPDATE MusicInfo SET isLike = ?, isHistory = ? WHERE musicId = ?");
            query.addBindValue(isLike? 1 : 0);
            query.addBindValue(isHistory? 1 : 0);
            query.addBindValue(musicId);
            if(!query.exec())
            {
               qDebug()<<"更新失败: "<<query.lastError().text();
            }

            qDebug()<<"更新music信息: "<<musicName<<" "<<musicId;
        }
        else
        {
            // 3. 不存在：直接将music的属性信息插入数据库
            query.prepare("INSERT INTO MusicInfo(musicId, musicName,musicSinger, albumName, musicUrl,\
            duration, isLike, isHistory)\
            VALUES(?,?,?,?,?,?,?,?)");
            query.addBindValue(musicId);
            query.addBindValue(musicName);
            query.addBindValue(singerName);
            query.addBindValue(albumName);
            query.addBindValue(musicUrl.toLocalFile());                query.addBindValue(duration);
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory? 1 : 0);
            if(!query.exec())
            {
                qDebug()<<"插入失败: "<<query.lastError().text();
                return;
            }
            qDebug()<<"插入music信息: "<<musicName<<" "<<musicId;
        }
    }
}



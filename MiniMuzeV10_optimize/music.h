#ifndef MUSIC_H
#define MUSIC_H


#include <QUrl>
#include <QMediaPlayer>
#include <QUuid>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QMimeDatabase>
#include <QEventLoop>
#include <QTimer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include "dbmanager.h"
// class Music : public QObject
// {
//     Q_OBJECT
class Music
{

public:
    Music(const QUrl &url);


    void setIsLike(bool isLike);
    void setIsHistory(bool isHistory);
    void setMusicName(const QString& musicName);
    void setSingerName(const QString& singerName);
    void setAlbumName(const QString& albumName);
    void setDuration(const qint64 duration);
    void setMusicUrl(const QUrl& url);
    void setMusicId(const QString& musicId);
    bool getIsLike();
    bool getIsHistory();
    QString getMusicName();
    QString getSingerName();
    QString getAlbumName();
    qint64 getDuration();
    QUrl getMusicUrl();
    QString getMusicId();
    QString getLrcFilePath() const;
    // 将当前Music对象更新到数据库
    void insertMusicToDB();
private:
    void parseMediaMetaData();
private:
    bool isLike; // 标记音乐是否为我喜欢
    bool isHistory; // 标记音乐是否播放过
    // 音乐的基本信息有：歌曲名称、歌手名称、专辑名称、总时长
    QString musicName;  // 音乐名称
    QString singerName; // 歌手名字
    QString albumName; // 专辑名称
    qint64 duration; // 音乐的持续时长，即播放总的时长
    // 为了标记歌曲的唯一性，给歌曲设置id
    // 磁盘上的歌曲文件经常删除或者修改位置，导致播放时找不到文件，或者重复添加
    // 此处用musicId来维护播放列表中音乐的唯一性
    QString musicId;
    QUrl musicUrl; // 音乐在磁盘中的位置





};

#endif // MUSIC_H

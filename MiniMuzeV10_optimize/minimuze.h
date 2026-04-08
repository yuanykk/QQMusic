#ifndef MINIMUZE_H
#define MINIMUZE_H

#include "volumetool.h"
#include "testform.h"
#include "commonpage.h"
#include "dbmanager.h"

#include <QWidget>
#include <qpropertyanimation.h>
#include "MusicList.h"
#include "lrcpage.h"
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class MiniMuze;
}
QT_END_NAMESPACE


enum playModeType
{
    LOOP_TYPE,//循环播放、
    RANDOM_TYPE,//随机播放、
    CurrentItemInLoop_TYPE
    //单曲循环
};
class MiniMuze : public QWidget
{
    Q_OBJECT

public:
    MiniMuze(QWidget *parent = nullptr);
    ~MiniMuze();
    void initUI();
    void connectSlotsAndSignals();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void initPlayer();
    void initSql();
    void initMusicList();

    QJsonArray randomPiction();

    void playAllOfCommonPage(CommonPage* commonPage, int index); //

    void playOfIndex(int index);
    void refreshCover(const QUrl&media);

    // musiclist.h 中新增
    // 所有歌曲信息更新到数据库
    void writeToDB();
    // 所有歌曲信息更新到数据库
    void readFromDB();


private slots:
    void on_quit_clicked();
    void on_btForm_Click(int pageid);

    void on_volume_clicked();

    void on_addLocal_clicked(); // 添加歌曲
    void onUpdateLikeMusic(bool isLike, QString musicId);
    // ==============
    //播放器相关
    void onPlyaBtn();
    void onPlayStateChanged(QMediaPlayer::PlaybackState status); // 播放器状态改变
    void onPlayModeChanged(); // 播放模式改变
    // qqmusic.h 新增
    void onPlayUpClicked(); // 上一曲
    void onPlayDownClicked(); // 下一曲

    void onPlayAll(MusicListType pageType);

    void onDoubleclickedItem(CommonPage*page,int index);

    void onSourceChanged(const QUrl&media);

    void onMusicVolumeChange(int volum);// 设置音量

    void setMusicSilence(bool isMuted); // 设置静音

    void onDurationChanged(qint64 duration);// 处理音乐进度信号
    void onPositionChanged(qint64 duration);// 处理音乐进度信号

    void onSetMusicSliderPosition(double rate); // 处理拖动进度条信号

    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_lyrics_clicked();

    void on_skin_clicked();

    void on_max_clicked();

    void on_min_clicked();

    void quitMiniMuze();// 退出Muze

private:
    Ui::MiniMuze *ui;
    QPoint pressOffset ;
    bool m_checked = false;
    VolumeTool* volumeTool = nullptr;
    TestForm* testForm;
    MusicList musicList;

    // ==============
    //播放器相关
    QMediaPlayer* player;
    QAudioOutput *audioOutput;
    QVector<QUrl> playQueue;
    int curIndex;
    CommonPage* curPage; // 选中的页
    MusicListType curPageType; // 当前执行页的类型
    playModeType mode;
    qint64 totalDuration; //总时长，mm:ss 字符串

    LrcPage* lrcPage;
    QPropertyAnimation* lrcAnimation; // 给歌词页面添加弹出动画

    DbManager* dbManager;

};
#endif // MINIMUZE_H

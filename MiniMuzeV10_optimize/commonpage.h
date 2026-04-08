#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include "MusicList.h"
#include <QWidget>
enum MusicListType
{
    LIKE_PAGE,
    LOCAL_PAGE,
    HISTORY_PAGE
};


namespace Ui {
class CommonPage;
}

class CommonPage : public QWidget
{
    Q_OBJECT

public:
    explicit CommonPage(QWidget *parent = nullptr);
    ~CommonPage();
    void setCommonPageUI(const QString &title, const QString &image);
    void setPageTYpe(MusicListType type);
    void addMusicTomusicOfPage(MusicList& musicList);
    void reFresh(MusicList& musicList);
    // ==============
    //播放器相关
    void addMusicToPlayer(MusicList &musicList, QVector<QUrl>& playList);
    MusicListType getMudciPageType();
    void setImageLabel(const QPixmap& pixMap);

signals:
    void updateLikeMusic(bool islike,QString pageId);
    void playAll(MusicListType pageType);
    void doubleclickedItem(CommonPage*page,int index);


private:
    Ui::CommonPage *ui;
    MusicListType musciPageType;
    QVector<QString> musicOfPage; // 一堆Musci  ID
};

#endif // COMMONPAGE_H

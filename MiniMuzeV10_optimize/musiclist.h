#ifndef MUSICLIST_H
#define MUSICLIST_H

#include "music.h"
#include <QMouseEvent>
#include <QSet>
typedef QVector<Music>::Iterator Iterator;
typedef QVector<Music>::const_iterator Const_Iterator;
class MusicList
{
public:
    MusicList();
    void addMusicsByUrl(const QList<QUrl>& urlList);
    void push_back(Music& music);
    Iterator begin();
    Iterator end();
    Const_Iterator begin()const;
    Const_Iterator end()const;
    Iterator findMusicById(const QString& pageId);
    bool musicListContain(Music& music);

    void mousePressEvent(QMouseEvent *event); // 重写鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event); // 重写鼠标滚动事件
    void mouseReleaseEvent(QMouseEvent *event); // 重写鼠标释放事件
    void moveSilder(); // 修改outLine的宽度为currentPos
    void insertToSet(const QString&&url);
private:
    QVector<Music> musicList;
    QSet<QString> musicPaths;
    int currentPos; // 滑动条当前位置 px为单位 当前最大值是800px
    int maxWidth;
};

#endif // MUSICLIST_H

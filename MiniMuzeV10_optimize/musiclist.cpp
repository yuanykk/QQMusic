#include "musiclist.h"



MusicList::MusicList() {}

void MusicList::addMusicsByUrl(const QList<QUrl> &urlList)
{
    for(auto musicUrl : urlList)
    {
        // 1.检查歌曲是否重复加载
        QString musicPath = musicUrl.toLocalFile();
        // 检测歌曲是否存在，如果再才能添加
        if(musicPaths.contains(musicPath))
            continue;
        // 歌曲还没有加载过，将其解析并添加到歌曲列表
        musicPaths.insert(musicPath);

        // 由于添加进来的文件不一定是歌曲文件，因此需要再次筛选出音乐文件
        QMimeDatabase db;
        QMimeType mime = db.mimeTypeForFile(musicUrl.toLocalFile());
        if(mime.name() != "audio/mpeg" && mime.name() != "audio/flac" && mime.name()!="audio/wav")
        {
            continue;
        }
        Music music(musicUrl);
        musicList.push_back(music);
    }
}

void MusicList::push_back(Music &music)
{
    musicList.push_back(music);
}

Iterator MusicList::begin()
{
    return musicList.begin();
}

Iterator MusicList::end()
{
    return musicList.end();
}

Const_Iterator MusicList::begin() const
{
    return musicList.cbegin();
}

Const_Iterator MusicList::end() const
{
    return musicList.cend();
}

Iterator MusicList::findMusicById(const QString &pageId)
{
    Iterator it = begin();
    for(;it!=end();it++)
    {
        if(it->getMusicId() == pageId)
        {
            return it;
        }
    }
    return it;
}

bool MusicList::musicListContain(Music &music)
{
    QString url = music.getMusicUrl().toString();
    for(auto val : musicList)
    {
        if(val.getMusicUrl().toString() == url)
            return true;
    }
    return false;
}

void MusicList::insertToSet(const QString &&url)
{
    musicPaths.insert(url);
}



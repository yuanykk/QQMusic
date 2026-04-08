#ifndef LRCPAGE_H
#define LRCPAGE_H

#include <QPropertyAnimation>
#include <QWidget>

namespace Ui {
class LrcPage;
}

struct LyricLine
{
    qint64 time; // 时间
    QString text; // 歌词内容
    LyricLine(qint64 qtime, QString qtext)
        : time(qtime)
        , text(qtext)
    {}
};

class LrcPage : public QWidget
{
    Q_OBJECT

public:
    explicit LrcPage(QWidget *parent = nullptr);
    ~LrcPage();
    bool parseLrc(const QString& lrcPath);
    int getLineLrcWordIndex(qint64 pos);
    QString getLineLrcWord(qint64 index);
    void showLrcWord(int time);
    void setMusciName(const QString& name);
    void setSingerName(const QString& name);
private:
    Ui::LrcPage *ui;
    QPropertyAnimation* lrcAnimation; // 给歌词页面添加隐藏动画
    // LrcPage类中添加成员变量
    QVector<LyricLine> lrcLines; // 按照时间的先后次序保存每行歌词
};

#endif // LRCPAGE_H

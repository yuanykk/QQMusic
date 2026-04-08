#include "lrcpage.h"
#include "ui_lrcpage.h"

#include <QFile>

LrcPage::LrcPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LrcPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->hideBtn, &QPushButton::clicked, this, [=]{
        lrcAnimation->start();
    });


    ui->hideBtn->setIcon(QIcon(":/images/xiala.png"));

    lrcAnimation = new QPropertyAnimation(this, "geometry", this);
    lrcAnimation->setDuration(250);
    lrcAnimation->setStartValue(QRect(10, 10, width(), height())); // 左上角坐标+右下角坐标
    lrcAnimation->setEndValue(QRect(10, 10+height(), width(), height()));

    // 动画结束时，将窗口隐藏
    connect(lrcAnimation, &QPropertyAnimation::finished, this, [=]{
        hide();
    });

}

LrcPage::~LrcPage()
{
    delete ui;
}

bool LrcPage::parseLrc(const QString &lrcPath)
{
    lrcLines.clear();
    // 打开歌词文件
    QFile lrcFile(lrcPath);
    if(!lrcFile.open(QFile::ReadOnly))
    {
        //qDebug()<<"打开文件:"<<lrcPath;
        return false;
    }
    while(!lrcFile.atEnd())
    {
        QString lrcWord = lrcFile.readLine(1024);
        // [00:17.94]那些失眠的人啊 你们还好吗
        // [0:58.600.00]你像一只飞来飞去的蝴蝶
        int left = lrcWord.indexOf('[');
        int right = lrcWord.indexOf(']');
        // 解析时间
        qint64 lineTime = 0;
        int start = 0;
        int end = 0;
        QString time = lrcWord.mid(left, right-left+1);
        // 解析分钟
        start = 1;
        end = time.indexOf(':');
        lineTime += lrcWord.mid(start, end-start).toInt()*60*1000;
        // 解析秒
        start = end + 1;
        end = time.indexOf('.', start);
        lineTime += lrcWord.mid(start, end-start).toInt()*1000;
        // 解析毫秒
        start = end+1;
        end = time.indexOf('.', start);
        lineTime += lrcWord.mid(start, end-start).toInt();
        // 解析歌词
        QString word = lrcWord.mid(right+1).trimmed();//trimmed() 左右去除空格
        lrcLines.push_back(LyricLine(lineTime, word));
    }
    // 测试验证
    // for(auto word : lrcLines)
    // {
    //     qDebug()<<word.time<<" "<<word.text;
    // }
    return true;
}

int LrcPage::getLineLrcWordIndex(qint64 pos)
{
    // 如果歌词是空的，返回-1
    if(lrcLines.isEmpty())
    {
        return -1;
    }
    if(lrcLines[0].time > pos)
    {
        return 0;
    }
    // 通过时间比较，获取下标
    for(int i = 1; i < lrcLines.size(); ++i)
    {
        if(pos > lrcLines[i-1].time && pos <= lrcLines[i].time)
        {
            return i-1;
        }
    }
    // 如果没有找到，返回最后一行
    return lrcLines.size()-1;

}

QString LrcPage::getLineLrcWord(qint64 index)
{
    if(index < 0 || index >= lrcLines.size())
    {
        return "";
    }
    return lrcLines[index].text;
}

void LrcPage::showLrcWord(int time)
{
    // 先要获取歌词--根据歌词的时间进行获取
    int index = getLineLrcWordIndex(time);
    if(-1 == index)
    {
        ui->line1->setText("");
        ui->line2->setText("");
        ui->line3->setText("");
        ui->lineCenter->setText("当前歌曲无歌词");
        ui->line4->setText("");
        ui->line5->setText("");
        ui->line6->setText("");
    }else
    {
        ui->line1->setText(getLineLrcWord(index-3));
        ui->line2->setText(getLineLrcWord(index-2));
        ui->line3->setText(getLineLrcWord(index-1));
        ui->lineCenter->setText(getLineLrcWord(index));
        ui->line4->setText(getLineLrcWord(index+1));
        ui->line5->setText(getLineLrcWord(index+2));
        ui->line6->setText(getLineLrcWord(index+3));
    }

}

void LrcPage::setMusciName(const QString &name)
{
    ui->musicName->setText(name);
}

void LrcPage::setSingerName(const QString &name)
{
    ui->musicSinger->setText(name);
}

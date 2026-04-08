/********************************************************************************
** Form generated from reading UI file 'qminimuze.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMINIMUZE_H
#define UI_QMINIMUZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMiniMuze
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *background;
    QVBoxLayout *verticalLayout;
    QWidget *head;
    QHBoxLayout *horizontalLayout_2;
    QWidget *headleft;
    QVBoxLayout *verticalLayout_2;
    QLabel *logo;
    QWidget *headright;
    QHBoxLayout *horizontalLayout_3;
    QWidget *searchBox;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QWidget *settingBox;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *skin;
    QPushButton *min;
    QPushButton *max;
    QPushButton *quit;
    QWidget *body;
    QHBoxLayout *horizontalLayout_6;
    QWidget *bodyleft;
    QVBoxLayout *verticalLayout_3;
    QWidget *leftBox;
    QVBoxLayout *verticalLayout_4;
    QWidget *onlineMusic;
    QVBoxLayout *verticalLayout_5;
    QLabel *onlineMusics;
    QWidget *rec;
    QWidget *audio;
    QWidget *music;
    QWidget *myMusic;
    QVBoxLayout *verticalLayout_6;
    QLabel *myMusictext;
    QWidget *like;
    QWidget *local;
    QWidget *online;
    QSpacerItem *verticalSpacer;
    QWidget *bodyright;
    QVBoxLayout *verticalLayout_7;
    QStackedWidget *stackedWidget;
    QWidget *recPage;
    QLabel *label;
    QWidget *musicPage;
    QLabel *label_2;
    QWidget *radioPage;
    QLabel *label_3;
    QWidget *likePage;
    QLabel *label_4;
    QWidget *localPage;
    QLabel *label_5;
    QWidget *recentPage;
    QLabel *label_6;
    QWidget *progressBar;
    QWidget *controBox;
    QHBoxLayout *horizontalLayout_7;
    QWidget *play1_;
    QGridLayout *gridLayout;
    QLabel *musicName;
    QLabel *musicSinger;
    QLabel *musicCover;
    QWidget *play2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *playMode;
    QPushButton *playUp;
    QPushButton *play;
    QPushButton *playDown;
    QPushButton *volume;
    QPushButton *addLocal;
    QWidget *play3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelNull;
    QLabel *currentTime;
    QLabel *line;
    QLabel *totalTime;
    QPushButton *lyrics;

    void setupUi(QWidget *QMiniMuze)
    {
        if (QMiniMuze->objectName().isEmpty())
            QMiniMuze->setObjectName("QMiniMuze");
        QMiniMuze->resize(1040, 700);
        horizontalLayout = new QHBoxLayout(QMiniMuze);
        horizontalLayout->setObjectName("horizontalLayout");
        background = new QWidget(QMiniMuze);
        background->setObjectName("background");
        background->setStyleSheet(QString::fromUtf8(" background-color:gray;"));
        verticalLayout = new QVBoxLayout(background);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        head = new QWidget(background);
        head->setObjectName("head");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(head->sizePolicy().hasHeightForWidth());
        head->setSizePolicy(sizePolicy);
        head->setMinimumSize(QSize(0, 80));
        head->setMaximumSize(QSize(16777215, 80));
        head->setStyleSheet(QString::fromUtf8(" background-color:blue\n"
";"));
        horizontalLayout_2 = new QHBoxLayout(head);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        headleft = new QWidget(head);
        headleft->setObjectName("headleft");
        headleft->setMinimumSize(QSize(200, 0));
        headleft->setMaximumSize(QSize(200, 16777215));
        headleft->setStyleSheet(QString::fromUtf8("background:rgb(255, 170, 255)"));
        verticalLayout_2 = new QVBoxLayout(headleft);
        verticalLayout_2->setObjectName("verticalLayout_2");
        logo = new QLabel(headleft);
        logo->setObjectName("logo");

        verticalLayout_2->addWidget(logo);


        horizontalLayout_2->addWidget(headleft);

        headright = new QWidget(head);
        headright->setObjectName("headright");
        headright->setStyleSheet(QString::fromUtf8("background:rgb(255, 170, 0)"));
        horizontalLayout_3 = new QHBoxLayout(headright);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        searchBox = new QWidget(headright);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(300, 0));
        searchBox->setMaximumSize(QSize(300, 16777215));
        searchBox->setStyleSheet(QString::fromUtf8("background:rgb(255, 85, 0)"));
        horizontalLayout_4 = new QHBoxLayout(searchBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lineEdit = new QLineEdit(searchBox);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_4->addWidget(lineEdit);


        horizontalLayout_3->addWidget(searchBox);

        settingBox = new QWidget(headright);
        settingBox->setObjectName("settingBox");
        settingBox->setStyleSheet(QString::fromUtf8("background:rgb(170, 0, 255)"));
        horizontalLayout_5 = new QHBoxLayout(settingBox);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(345, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        skin = new QPushButton(settingBox);
        skin->setObjectName("skin");
        skin->setMinimumSize(QSize(30, 30));
        skin->setMaximumSize(QSize(30, 30));

        horizontalLayout_5->addWidget(skin);

        min = new QPushButton(settingBox);
        min->setObjectName("min");
        min->setMinimumSize(QSize(30, 30));
        min->setMaximumSize(QSize(30, 30));

        horizontalLayout_5->addWidget(min);

        max = new QPushButton(settingBox);
        max->setObjectName("max");
        max->setMinimumSize(QSize(30, 30));
        max->setMaximumSize(QSize(30, 30));

        horizontalLayout_5->addWidget(max);

        quit = new QPushButton(settingBox);
        quit->setObjectName("quit");
        quit->setMinimumSize(QSize(30, 30));
        quit->setMaximumSize(QSize(30, 30));

        horizontalLayout_5->addWidget(quit);


        horizontalLayout_3->addWidget(settingBox);


        horizontalLayout_2->addWidget(headright);


        verticalLayout->addWidget(head);

        body = new QWidget(background);
        body->setObjectName("body");
        body->setStyleSheet(QString::fromUtf8(" background-color:green;"));
        horizontalLayout_6 = new QHBoxLayout(body);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        bodyleft = new QWidget(body);
        bodyleft->setObjectName("bodyleft");
        bodyleft->setMinimumSize(QSize(200, 0));
        bodyleft->setMaximumSize(QSize(200, 16777215));
        bodyleft->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 0, 255)"));
        verticalLayout_3 = new QVBoxLayout(bodyleft);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        leftBox = new QWidget(bodyleft);
        leftBox->setObjectName("leftBox");
        leftBox->setMinimumSize(QSize(0, 400));
        leftBox->setMaximumSize(QSize(16777215, 400));
        leftBox->setStyleSheet(QString::fromUtf8("background:rgb(0, 255, 127)"));
        verticalLayout_4 = new QVBoxLayout(leftBox);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        onlineMusic = new QWidget(leftBox);
        onlineMusic->setObjectName("onlineMusic");
        onlineMusic->setStyleSheet(QString::fromUtf8("background:#f0f0f0"));
        verticalLayout_5 = new QVBoxLayout(onlineMusic);
        verticalLayout_5->setObjectName("verticalLayout_5");
        onlineMusics = new QLabel(onlineMusic);
        onlineMusics->setObjectName("onlineMusics");

        verticalLayout_5->addWidget(onlineMusics);

        rec = new QWidget(onlineMusic);
        rec->setObjectName("rec");
        rec->setStyleSheet(QString::fromUtf8("background:rgb(0, 255, 0)"));

        verticalLayout_5->addWidget(rec);

        audio = new QWidget(onlineMusic);
        audio->setObjectName("audio");
        audio->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 0)"));

        verticalLayout_5->addWidget(audio);

        music = new QWidget(onlineMusic);
        music->setObjectName("music");
        music->setStyleSheet(QString::fromUtf8("background:rgb(170, 255, 255)"));

        verticalLayout_5->addWidget(music);


        verticalLayout_4->addWidget(onlineMusic);

        myMusic = new QWidget(leftBox);
        myMusic->setObjectName("myMusic");
        myMusic->setStyleSheet(QString::fromUtf8("background:#f5f5f5"));
        verticalLayout_6 = new QVBoxLayout(myMusic);
        verticalLayout_6->setObjectName("verticalLayout_6");
        myMusictext = new QLabel(myMusic);
        myMusictext->setObjectName("myMusictext");

        verticalLayout_6->addWidget(myMusictext);

        like = new QWidget(myMusic);
        like->setObjectName("like");
        like->setStyleSheet(QString::fromUtf8("background:rgb(170, 170, 0)"));

        verticalLayout_6->addWidget(like);

        local = new QWidget(myMusic);
        local->setObjectName("local");
        local->setStyleSheet(QString::fromUtf8("background:rgb(170, 170, 255)"));

        verticalLayout_6->addWidget(local);

        online = new QWidget(myMusic);
        online->setObjectName("online");
        online->setStyleSheet(QString::fromUtf8("background:rgb(255, 170, 127)"));

        verticalLayout_6->addWidget(online);


        verticalLayout_4->addWidget(myMusic);


        verticalLayout_3->addWidget(leftBox);

        verticalSpacer = new QSpacerItem(20, 195, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_6->addWidget(bodyleft);

        bodyright = new QWidget(body);
        bodyright->setObjectName("bodyright");
        bodyright->setStyleSheet(QString::fromUtf8("background:rgb(255, 170, 127)"));
        verticalLayout_7 = new QVBoxLayout(bodyright);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(bodyright);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255)"));
        recPage = new QWidget();
        recPage->setObjectName("recPage");
        label = new QLabel(recPage);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 250, 69, 19));
        stackedWidget->addWidget(recPage);
        musicPage = new QWidget();
        musicPage->setObjectName("musicPage");
        label_2 = new QLabel(musicPage);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(450, 180, 69, 19));
        stackedWidget->addWidget(musicPage);
        radioPage = new QWidget();
        radioPage->setObjectName("radioPage");
        label_3 = new QLabel(radioPage);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(630, 220, 69, 19));
        stackedWidget->addWidget(radioPage);
        likePage = new QWidget();
        likePage->setObjectName("likePage");
        label_4 = new QLabel(likePage);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(430, 220, 69, 19));
        stackedWidget->addWidget(likePage);
        localPage = new QWidget();
        localPage->setObjectName("localPage");
        label_5 = new QLabel(localPage);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(590, 230, 69, 19));
        stackedWidget->addWidget(localPage);
        recentPage = new QWidget();
        recentPage->setObjectName("recentPage");
        label_6 = new QLabel(recentPage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(380, 200, 69, 19));
        stackedWidget->addWidget(recentPage);

        verticalLayout_7->addWidget(stackedWidget);

        progressBar = new QWidget(bodyright);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setMaximumSize(QSize(16777215, 30));
        progressBar->setStyleSheet(QString::fromUtf8("background:rgb(0, 170, 0)"));

        verticalLayout_7->addWidget(progressBar);

        controBox = new QWidget(bodyright);
        controBox->setObjectName("controBox");
        controBox->setMinimumSize(QSize(0, 60));
        controBox->setMaximumSize(QSize(16777215, 60));
        controBox->setStyleSheet(QString::fromUtf8("background:rgb(0, 170, 255)"));
        horizontalLayout_7 = new QHBoxLayout(controBox);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        play1_ = new QWidget(controBox);
        play1_->setObjectName("play1_");
        play1_->setStyleSheet(QString::fromUtf8("background:#FFFAFA;"));
        gridLayout = new QGridLayout(play1_);
        gridLayout->setObjectName("gridLayout");
        musicName = new QLabel(play1_);
        musicName->setObjectName("musicName");

        gridLayout->addWidget(musicName, 0, 1, 1, 1);

        musicSinger = new QLabel(play1_);
        musicSinger->setObjectName("musicSinger");

        gridLayout->addWidget(musicSinger, 1, 1, 1, 1);

        musicCover = new QLabel(play1_);
        musicCover->setObjectName("musicCover");

        gridLayout->addWidget(musicCover, 0, 0, 2, 1);


        horizontalLayout_7->addWidget(play1_);

        play2 = new QWidget(controBox);
        play2->setObjectName("play2");
        play2->setStyleSheet(QString::fromUtf8("background:#F8F8FF;"));
        horizontalLayout_8 = new QHBoxLayout(play2);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        playMode = new QPushButton(play2);
        playMode->setObjectName("playMode");
        playMode->setMinimumSize(QSize(30, 30));
        playMode->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(playMode);

        playUp = new QPushButton(play2);
        playUp->setObjectName("playUp");
        playUp->setMinimumSize(QSize(30, 30));
        playUp->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(playUp);

        play = new QPushButton(play2);
        play->setObjectName("play");
        play->setMinimumSize(QSize(30, 30));
        play->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(play);

        playDown = new QPushButton(play2);
        playDown->setObjectName("playDown");
        playDown->setMinimumSize(QSize(30, 30));
        playDown->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(playDown);

        volume = new QPushButton(play2);
        volume->setObjectName("volume");
        volume->setMinimumSize(QSize(30, 30));
        volume->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(volume);

        addLocal = new QPushButton(play2);
        addLocal->setObjectName("addLocal");
        addLocal->setMinimumSize(QSize(30, 30));
        addLocal->setMaximumSize(QSize(30, 30));

        horizontalLayout_8->addWidget(addLocal);


        horizontalLayout_7->addWidget(play2);

        play3 = new QWidget(controBox);
        play3->setObjectName("play3");
        play3->setStyleSheet(QString::fromUtf8("background:#FFFAF0;"));
        horizontalLayout_9 = new QHBoxLayout(play3);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        labelNull = new QLabel(play3);
        labelNull->setObjectName("labelNull");

        horizontalLayout_9->addWidget(labelNull);

        currentTime = new QLabel(play3);
        currentTime->setObjectName("currentTime");

        horizontalLayout_9->addWidget(currentTime);

        line = new QLabel(play3);
        line->setObjectName("line");
        line->setMinimumSize(QSize(30, 0));
        line->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_9->addWidget(line);

        totalTime = new QLabel(play3);
        totalTime->setObjectName("totalTime");

        horizontalLayout_9->addWidget(totalTime);

        lyrics = new QPushButton(play3);
        lyrics->setObjectName("lyrics");
        lyrics->setMinimumSize(QSize(30, 30));
        lyrics->setMaximumSize(QSize(30, 30));

        horizontalLayout_9->addWidget(lyrics);


        horizontalLayout_7->addWidget(play3);


        verticalLayout_7->addWidget(controBox);


        horizontalLayout_6->addWidget(bodyright);


        verticalLayout->addWidget(body);


        horizontalLayout->addWidget(background);


        retranslateUi(QMiniMuze);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QMiniMuze);
    } // setupUi

    void retranslateUi(QWidget *QMiniMuze)
    {
        QMiniMuze->setWindowTitle(QCoreApplication::translate("QMiniMuze", "QMiniMuze", nullptr));
        logo->setText(QCoreApplication::translate("QMiniMuze", "TextLabel", nullptr));
        lineEdit->setText(QCoreApplication::translate("QMiniMuze", "sadf ", nullptr));
        skin->setText(QString());
        min->setText(QString());
        max->setText(QString());
        quit->setText(QString());
        onlineMusics->setText(QCoreApplication::translate("QMiniMuze", "\345\234\250\347\272\277\351\237\263\344\271\220", nullptr));
        myMusictext->setText(QCoreApplication::translate("QMiniMuze", "\346\210\221\347\232\204\351\237\263\344\271\220", nullptr));
        label->setText(QCoreApplication::translate("QMiniMuze", "Page1", nullptr));
        label_2->setText(QCoreApplication::translate("QMiniMuze", "Page2", nullptr));
        label_3->setText(QCoreApplication::translate("QMiniMuze", "Page3", nullptr));
        label_4->setText(QCoreApplication::translate("QMiniMuze", "Page4", nullptr));
        label_5->setText(QCoreApplication::translate("QMiniMuze", "Page5", nullptr));
        label_6->setText(QCoreApplication::translate("QMiniMuze", "Page6", nullptr));
        musicName->setText(QCoreApplication::translate("QMiniMuze", "\346\255\214\345\220\215", nullptr));
        musicSinger->setText(QCoreApplication::translate("QMiniMuze", "\346\255\214\346\211\213", nullptr));
        musicCover->setText(QCoreApplication::translate("QMiniMuze", "\345\233\276\347\211\207", nullptr));
        playMode->setText(QCoreApplication::translate("QMiniMuze", "\346\250\241\345\274\217", nullptr));
        playUp->setText(QCoreApplication::translate("QMiniMuze", "<", nullptr));
        play->setText(QCoreApplication::translate("QMiniMuze", "o", nullptr));
        playDown->setText(QCoreApplication::translate("QMiniMuze", ">", nullptr));
        volume->setText(QCoreApplication::translate("QMiniMuze", "v", nullptr));
        addLocal->setText(QCoreApplication::translate("QMiniMuze", "L", nullptr));
        labelNull->setText(QCoreApplication::translate("QMiniMuze", "\345\215\240\344\275\215\347\254\246", nullptr));
        currentTime->setText(QCoreApplication::translate("QMiniMuze", "      00:00", nullptr));
        line->setText(QCoreApplication::translate("QMiniMuze", "   /", nullptr));
        totalTime->setText(QCoreApplication::translate("QMiniMuze", "00:00", nullptr));
        lyrics->setText(QCoreApplication::translate("QMiniMuze", "\350\257\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMiniMuze: public Ui_QMiniMuze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMINIMUZE_H

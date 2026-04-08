QT       += core gui
QT += multimedia
QT += multimediawidgets
QT += sql
DEFINES += QT_NO_DEBUG_OUTPUT
DEFINES += QT_NO_WARNING_OUTPUT  # 可选，同时禁用 qWarning()

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    btform.cpp \
    commonpage.cpp \
    dbmanager.cpp \
    listitembox.cpp \
    lrcpage.cpp \
    main.cpp \
    minimuze.cpp \
    music.cpp \
    musiclist.cpp \
    musicslider.cpp \
    recbox.cpp \
    recitembox.cpp \
    testform.cpp \
    volumetool.cpp

HEADERS += \
    btform.h \
    commonpage.h \
    dbmanager.h \
    listitembox.h \
    lrcpage.h \
    minimuze.h \
    music.h \
    musiclist.h \
    musicslider.h \
    recbox.h \
    recitembox.h \
    testform.h \
    volumetool.h

FORMS += \
    btform.ui \
    commonpage.ui \
    listitembox.ui \
    lrcpage.ui \
    minimuze.ui \
    musicslider.ui \
    recbox.ui \
    recitembox.ui \
    testform.ui \
    volumetool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

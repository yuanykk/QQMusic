#include "minimuze.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 创建共享内存
    // 向内核申请共享内存，这个内存由内核管理，应用层拿到的是句柄
    QSharedMemory sharedMem("MiniMuze");
    // 如果共享内存已经被占用，说明已经有实例在运行
    if (sharedMem.attach()) {
        QMessageBox::information(nullptr, "QQMusic", "QQMusic已经在运行...");
        return 0;
    }
    sharedMem.create(1);

    MiniMuze w;
    w.show();
    return a.exec();
}

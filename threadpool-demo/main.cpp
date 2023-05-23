#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //不支持函数类型时，需要手动注册（可能qt版本太低才会出现此问题）
//    qRegisterMetaType<QVector<int>>("QVector<int>");
    MainWindow w;
    w.show();

    return a.exec();
}

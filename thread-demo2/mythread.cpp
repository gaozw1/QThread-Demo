#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QTime>
#include <QThread>

/*
 * https://subingwen.cn/qt/thread/
1. 创建一个新的类，让这个类从 QObject 派生
2. 在这个类中添加一个公共的成员函数，函数体就是我们要子线程中执行的业务逻辑
3. 在主线程中创建一个 QThread 对象，这就是子线程的对象
4. 在主线程中创建工作的类对象（千万不要指定给创建的对象指定父对象）
5. 将 MyWork 对象移动到创建的子线程对象中，需要调用 QObject 类提供的 moveToThread() 方法
6. 启动子线程，调用 start(), 这时候线程启动了，但是移动到线程中的对象并没有工作
7. 调用 MyWork 类对象的工作函数，让这个函数开始执行，这时候是在移动到的那个子线程中运行的

使用这种多线程方式，假设有多个不相关的业务流程需要被处理，那么就可以创建多个类似于 MyWork 的类，将业务流程放多类的公共成员函数中，
然后将这个业务类的实例对象移动到对应的子线程中 moveToThread() 就可以了，这样可以让编写的程序更加灵活，可读性更强，更易于维护。

*/
Generate::Generate(QObject *parent) : QObject(parent)
{

}


void Generate::working(int num)
{
    qInfo() << "生成随机数的线程地址：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    //随机数种子
    qsrand(QTime::currentTime().msec());
    for (int i=0; i<num; ++i) {
        list.push_back(qrand() % 10000);
    }
    int milsec = time.elapsed();
    qInfo() << "生成" << num << "个随机数总共用时：" << milsec << "毫秒";
    emit sendArray(list);

}

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}


void BubbleSort::working(QVector<int> list)
{
    qInfo() << "冒泡排序的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    int temp;
    for (int i = 0; i<list.size(); ++i) {
        for (int j = 0; j<list.size() - i - 1; ++j) {
            if(list[j] > list[j+1]){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qInfo() << "冒泡排序总共用时：" << milsec << "毫秒";
    emit finish(list);
}


QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}


void QuickSort::working(QVector<int> list)
{
    qInfo() << "快速排序的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(list,0,list.size()-1);
    int milsec = time.elapsed();
    qInfo() << "快速排序总共用时：" << milsec << "毫秒";
    emit finish(list);
}

void QuickSort::quickSort(QVector<int> &list_, int leftIndex, int rightIndex)
{
    if(leftIndex >= rightIndex){
        return;
    }
    int pivot = list_[leftIndex];
    int pivotIndex = leftIndex;
    for (int i = leftIndex; i<=rightIndex; i++) {
        if(list_[i] < pivot){
            pivotIndex ++;
            int temp = list_[pivotIndex];
            list_[pivotIndex] = list_[i];
            list_[i] = temp;
        }
    }
    list_[leftIndex] = list_[pivotIndex];
    list_[pivotIndex] = pivot;

    quickSort(list_,leftIndex,pivotIndex-1);
    quickSort(list_,pivotIndex + 1,rightIndex);
}

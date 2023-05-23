#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QTime>
#include <QThread>

/*
 * https://subingwen.cn/qt/threadpool/
1. 创建一个类，让其继承 QT 中的 QObject，QRunnable
2. 重写父类的 run () 方法，在该函数内部编写子线程要处理的具体的业务流程
3. 将任务类直接扔到线程池中并启动

在需要频繁使用线程时，用到线程池
*/
Generate::Generate(QObject *parent) : QObject(parent), QRunnable ()
{
    setAutoDelete(true);
}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qInfo() << "生成随机数的线程地址：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    //随机数种子
    qsrand(QTime::currentTime().msec());
    for (int i=0; i<m_num; ++i) {
        list.push_back(qrand() % 10000);
    }
    int milsec = time.elapsed();
    qInfo() << "生成" << m_num << "个随机数总共用时：" << milsec << "毫秒";
    emit sendArray(list);

}

BubbleSort::BubbleSort(QObject *parent) : QObject(parent), QRunnable ()
{
    setAutoDelete(true);

}


void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qInfo() << "冒泡排序的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    int temp;
    for (int i = 0; i<m_list.size(); ++i) {
        for (int j = 0; j<m_list.size() - i - 1; ++j) {
            if(m_list[j] > m_list[j+1]){
                temp = m_list[j];
                m_list[j] = m_list[j+1];
                m_list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qInfo() << "冒泡排序总共用时：" << milsec << "毫秒";
    emit finish(m_list);
}


QuickSort::QuickSort(QObject *parent) : QObject(parent), QRunnable ()
{
    setAutoDelete(true);

}

void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void QuickSort::run()
{
    qInfo() << "快速排序的线程地址：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(m_list,0,m_list.size()-1);
    int milsec = time.elapsed();
    qInfo() << "快速排序总共用时：" << milsec << "毫秒";
    emit finish(m_list);
}

void QuickSort::quickSort(QVector<int> &list, int leftIndex, int rightIndex)
{
    if(leftIndex >= rightIndex){
        return;
    }
    int pivot = list[leftIndex];
    int pivotIndex = leftIndex;
    for (int i = leftIndex; i<=rightIndex; i++) {
        if(list[i] < pivot){
            pivotIndex ++;
            int temp = list[pivotIndex];
            list[pivotIndex] = list[i];
            list[i] = temp;
        }
    }
    list[leftIndex] = list[pivotIndex];
    list[pivotIndex] = pivot;

    quickSort(list,leftIndex,pivotIndex-1);
    quickSort(list,pivotIndex + 1,rightIndex);
}

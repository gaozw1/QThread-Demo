#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QRunnable>
#include <QObject>
#include <QVector>

class Generate : public QObject, public QRunnable
{

    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void recvNum(int num);
    void run() override;

signals:
    void sendArray(QVector<int>);
private:
    int m_num;

};

class BubbleSort : public QObject, public QRunnable
{

    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void recvArray(QVector<int> list);
    void run() override;

signals:
    void finish(QVector<int>);
private:
    QVector<int> m_list;

};

class QuickSort : public QObject, public QRunnable
{

    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void recvArray(QVector<int> list);
    void run() override;

private:
    void quickSort(QVector<int> &list, int leftIndex, int rightIndex);

signals:
    void finish(QVector<int>);
private:
    QVector<int> m_list;

};

#endif // MYTHREAD_H

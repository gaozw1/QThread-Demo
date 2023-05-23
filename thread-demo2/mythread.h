#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QVector>

class Generate : public QObject
{

    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void working(int num);

signals:
    void sendArray(QVector<int>);


};

class BubbleSort : public QObject
{

    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);

signals:
    void finish(QVector<int>);

};

class QuickSort : public QObject
{

    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> list);

private:
    void quickSort(QVector<int> &list, int leftIndex, int rightIndex);

signals:
    void finish(QVector<int>);
private:
    QVector<int> m_list;

};

#endif // MYTHREAD_H

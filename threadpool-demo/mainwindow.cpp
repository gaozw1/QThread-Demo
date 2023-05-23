#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1. 创建任务类对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    //2. 启动子线程
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        QThreadPool::globalInstance()->start(gen);
    });
    connect(this,&MainWindow::starting,gen, &Generate::recvNum);
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvArray);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvArray);


    connect(gen,&Generate::sendArray,this,[=](QVector<int> list){
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
                ui->randList->clear();
        for (int i=0; i<list.size(); ++i) {
            ui->randList->addItem(QString::number(list.at(i)));//QString::number将数字转成字符串
        }

    });
    connect(bubble,&BubbleSort::finish,this,[=](QVector<int> list){
        ui->bubbleList->clear();
        for (int i=0; i<list.size(); ++i) {
            ui->bubbleList->addItem(QString::number(list.at(i)));//QString::number将数字转成字符串
        }

    });
    connect(quick,&QuickSort::finish,this,[=](QVector<int> list){
         ui->quickList->clear();
         for (int i=0; i<list.size(); ++i) {
             ui->quickList->addItem(QString::number(list.at(i)));//QString::number将数字转成字符串
         }

    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

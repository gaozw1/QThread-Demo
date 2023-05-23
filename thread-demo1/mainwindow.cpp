#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1. new sub-thread object
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    //2. when click start button,start sub-thread
    connect(ui->start,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        gen->start();
    });
    connect(this,&MainWindow::starting,gen, &Generate::recvNum);
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvArray);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvArray);


    connect(gen,&Generate::sendArray,this,[=](QVector<int> list){
        bubble->start();
        quick->start();
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

    connect(this,&MainWindow::destroy,this,[=]{
        gen->quit();
        gen->wait();
        gen->deleteLater();

        bubble->quit();
        bubble->wait();
        bubble->deleteLater();

        quick->quit();
        quick->wait();
        quick->deleteLater();

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

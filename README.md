# QThread-Demo

Qt Creator 4.8.2

Based on Qt 5.11.3(GCC 8.3.0, 64bit)


本项目给出两种Qt多线程的使用和一种Qt线程池的使用demo。主要参考护互联网上大佬的讲解，其中快速排序部分没做参考

参考：

- Qt中多线程-线程池的使用-C/C++/qt

https://www.bilibili.com/video/BV1iN411f7dY/?share_source=copy_web&vd_source=29edf58914de85c9019dbcacb358197c

- Qt 中多线程的使用

https://subingwen.cn/qt/thread/

- Qt 中线程池的使用

https://subingwen.cn/qt/threadpool/

## thread-demo1

1. 创建一个线程类的子类，让其继承 QT 中的线程类 QThread
2. 重写父类的 run () 方法，在该函数内部编写子线程要处理的具体的业务流程
3. 在主线程中创建子线程对象
4. 启动子线程，调用 start () 方法

这种在程序中添加子线程的方式是非常简单的，但是也有弊端，

假设要在一个子线程中处理多个任务，所有的处理逻辑都需要写到run()函数中，这样该函数中的处理逻辑就会变得非常混乱，不太容易维护。

## thread-demo2

1. 创建一个新的类，让这个类从 QObject 派生
2. 在这个类中添加一个公共的成员函数，函数体就是我们要子线程中执行的业务逻辑
3. 在主线程中创建一个 QThread 对象，这就是子线程的对象
4. 在主线程中创建工作的类对象（千万不要指定给创建的对象指定父对象）
5. 将 MyWork 对象移动到创建的子线程对象中，需要调用 QObject 类提供的 moveToThread() 方法
6. 启动子线程，调用 start(), 这时候线程启动了，但是移动到线程中的对象并没有工作
7. 调用 MyWork 类对象的工作函数，让这个函数开始执行，这时候是在移动到的那个子线程中运行的

使用这种多线程方式，假设有多个不相关的业务流程需要被处理，那么就可以创建多个类似于 MyWork 的类，将业务流程放多类的公共成员函数中，

然后将这个业务类的实例对象移动到对应的子线程中 moveToThread() 就可以了，这样可以让编写的程序更加灵活，可读性更强，更易于维护。

可与thread-demo1对比差异

## threadpool-demo:

1. 创建一个类，让其继承 QT 中的 QObject，QRunnable
2. 重写父类的 run () 方法，在该函数内部编写子线程要处理的具体的业务流程
3. 将任务类直接扔到线程池中并启动

在需要频繁使用线程等情况下，用到线程池。

可与thread-demo1对比差异

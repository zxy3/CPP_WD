/// 面向对象线程类封装
#include <iostream>
#include <memory>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Noncopyable
class Noncopyable
{
protected:
    // 构造函数
    Noncopyable() {}
    // 析构函数
    ~Noncopyable() {}
    // ---------------成员函数----------------
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

// class Noncopyable;
// 线程类
class Thread
    : public Noncopyable
{
public:
    // 构造函数
    Thread()
        : _pthid(0), _isRunning(false)
    {
        cout << "Thread()" << endl;
    }
    // 析构函数
    virtual ~Thread();
    // --------------成员函数------------------

    // 开始线程
    void start();
    // 回收线程
    void join();

private:
    // run是对外抽象出来的接口，由子线程运行，不能直接被线程对象调用
    // 因此被设置为纯虚函数
    // 纯虚函数，使用多态的机制
    virtual void run() = 0; //待执行的任务
    static void *threadfunc(void *arg);

private:
    pthread_t _pthid;
    // 设置描述当前线程运行的状态
    bool _isRunning;
};

// ----------------------------函数实现------------------------------
// 开始线程
void Thread::start()
{
    // 3，线程方法，4线程地址
    pthread_create(&_pthid, nullptr, threadfunc, this);
    // 将开关设置为true
    _isRunning = true;
}
// 线程函数执行体，参数和返回值必须要void*,需要消除
void *Thread::threadfunc(void *arg)
{
    // 强转为线程指针，才能拿到线程对象
    Thread *pthread = static_cast<Thread *>(arg);
    // 运行run，真正要执行的方法体
    if (pthread)
        // 抽象出来真正要做的任务
        // 派生类的指针，指向基类的方法，再从虚表找到派生类的方法
        pthread->run();
    // 运行完毕后设置为空
    return nullptr;
}
// 回收线程
void Thread::join()
{
    if (_isRunning)
    {
        // 回收线程，关闭开关
        cout << ">>>>"
             << "join : " << _pthid << endl;
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}
// 析构函数
Thread::~Thread()
{
    if (_isRunning)
    {
        // 将线程交给系统去回收
        pthread_detach(_pthid);
    }
}
// ----------------------------------test-----------------------------
// Thread 派生类
class MyThread
    : public Thread
{
    // 覆盖run
    void run()
    {
        ::srand(::clock());

        int cnt = 20;
        while (cnt--)
        {
            int number = ::rand() % 100;
            // pthread_self 获取线程id
            cout << "----> sub Thread:  " << pthread_self()
                 << ": number = " << number << "    cnt --> " << cnt << endl;
            ::sleep(1);
        }
    }
};

int main(void)
{
    // main函数是主线程
    unique_ptr<Thread> thread(new MyThread());
    // 产生一个子线程
    thread->start();
    // 等待回收子线程
    thread->join();

    MyThread thread1;
    // MyThread thread2 = thread1;

    return 0;
}

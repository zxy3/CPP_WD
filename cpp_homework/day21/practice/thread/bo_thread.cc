///基于对象线程类封装：没有继承，没有虚函数，直接实现
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
    // 定义了protected方法的类--抽象类
protected:
    Noncopyable() {}
    ~Noncopyable() {}
    // 成员函数
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

//Thread
class Thread
    : Noncopyable //Noncopyable 保证线程不可被复制
{
public:
    // 代表的就是func
    using ThreadCallback = function<void()>;
    // cb 是一个回调函数
    // 构造函数 将cb用右值引用的方式传递进来
    Thread(ThreadCallback &&cb)
        : _pthid(0), _isRunning(false), _cb(std::move(cb))
    {
    }
    // 成员函数
    void start();
    void join();
    // 析构函数
    ~Thread();

private:
    // 否则含有一个隐含的this指针，设置为静态不会多出一个参数
    // 跟OO相同
    static void *threadfunc(void *arg);

private:
    pthread_t _pthid;
    bool _isRunning;
    // 不用虚函数调子类方法时用回调函数
    ThreadCallback _cb;
};

// --------------------成员函数----------------------------------
void Thread::start()
{
    pthread_create(&_pthid, nullptr, threadfunc, this);
    _isRunning = true;
}

void *Thread::threadfunc(void *arg)
{
    Thread *pthread = static_cast<Thread *>(arg);
    if (pthread)
        // 派生类 函数执行体实际上要调用的方法
        pthread->_cb();

    return nullptr;
}
// 与oo相同
void Thread::join()
{
    if (_isRunning)
    {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

// 与oo相同
Thread::~Thread()
{
    if (_isRunning)
    {
        pthread_detach(_pthid);
    }
}
// -------------------------test-----------------------------
class Mytask
{
public:
    void run()
    {
        // 由时钟频率，产生随机数
        ::srand(::clock());

        int cnt = 20;
        while (cnt--)
        {
            int number = ::rand() % 100;
            // pthread_self
            cout << "sub Thread " << pthread_self()
                 << ": number = " << number << endl;
            // 休眠1秒
            ::sleep(1);
        }
    }
};

void task_process(int)
{
    // 获取随机数
    ::srand(::clock());

    int cnt = 20;
    while (cnt--)
    {
        int number = ::rand() % 100;
        cout << "sub Thread --> " << pthread_self()
             << " : number = " << number << "    cnt---> " << cnt << endl;
        ::sleep(1);
    }
}

int main(void)
{
    unique_ptr<Thread> thread(new Thread(
        // 绑定成员函数,Mytask()对象,或者用传递指针的方式也可以
        // std::bind(&Mytask::run, Mytask())
        // 直接传递对象
        bind(task_process, 1)));

    thread->start();
    thread->join();
    return 0;
}

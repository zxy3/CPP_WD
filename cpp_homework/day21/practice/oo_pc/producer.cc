// 生产者-消费者模型  生产者

#include <iostream>
#include <memory>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// --------------------------thread----------------------------
class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

class Thread
    : Noncopyable
{
public:
    Thread()
        : _pthid(0), _isRunning(false)
    {
    }

    virtual ~Thread();

    void start();
    void join();

    static void *threadFunc(void *);

private:
    virtual void run() = 0;

private:
    pthread_t _pthid;
    bool _isRunning;
};
// -------------------------produce------------------------------
class TaskQueue;
class Condition;
class Producer
    : public Thread
{
public:
    Producer(TaskQueue &taskque);

private:
    void run() override;
    TaskQueue &_taskQue;
};
using ElemType = int;

// MutexLock
class MutexLock
    : Noncopyable
{
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();

    pthread_mutex_t *getMutexPtr() { return &_mutex; }

private:
    pthread_mutex_t _mutex;
};

// MutexLockGuard RAII技术的体现
class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
        : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};
// Condition
class Condition
    : Noncopyable
{
public:
    Condition(MutexLock &mutex);

    ~Condition();

    void wait();
    void notify();
    void notifyall();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};
// TaskQueue
// 采用组合的设计模式，将queue相关的放到一起，尽量不使用全局对象
class TaskQueue
{
    // 复习：互斥锁和条件变量的使用
public:
    TaskQueue(size_t size);
    // 查看当前状态
    bool empty() const;
    bool full() const;
    // 生产者执行
    void push(ElemType elem);
    // 消费者执行
    ElemType pop();

private:
    size_t _queSize;
    // 任务队列 生产者：队列是否为满，消费者：队列是够为空
    queue<int> _que;
    MutexLock _mutex;
    // 目的：阻塞当前线程，另外一个线程唤醒线程时候，再继续运行
    // 生产者等待条件变量
    Condition _notFull;
    // 消费者等待条件变量
    Condition _notEmpty;
};
// -------------------------Consumer------------------------------
// Consumer
class TaskQueue;
class Consumer
    : public Thread
{
public:
    Consumer(TaskQueue &taskque);

private:
    void run() override;
    TaskQueue &_taskQue;
};
Consumer::Consumer(TaskQueue &taskque)
    : _taskQue(taskque)
{
}
// ----------- Consumer成员函数实现 -------------
void Consumer::run()
{
    int cnt = 20;
    while (cnt--)
    {
        int number = _taskQue.pop();
        cout << ">> consumer thread " << pthread_self()
             << " consume a number = " << number << endl;
        ::sleep(1);
    }
}
// ----------------------produce 成员函数实现 -----------------------
// ----------------Thread
Thread::~Thread()
{
    if (_isRunning)
    {
        pthread_detach(_pthid);
    }
}

void Thread::start()
{
    pthread_create(&_pthid, nullptr, threadFunc, this);
    _isRunning = true;
}

void Thread::join()
{
    if (_isRunning)
    {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

void *Thread::threadFunc(void *arg)
{
    Thread *pthread = static_cast<Thread *>(arg);
    if (pthread)
        pthread->run(); //执行任务
    return nullptr;
}
//------------ condition
Condition::Condition(MutexLock &mutex)
    : _mutex(mutex)
{
    if (pthread_cond_init(&_cond, nullptr))
    {
        perror("pthread_cond_init");
    }
}

Condition::~Condition()
{
    if (pthread_cond_destroy(&_cond))
    {
        perror("pthread_cond_destroy");
    }
}

void Condition::wait()
{
    if (pthread_cond_wait(&_cond, _mutex.getMutexPtr()))
    {
        perror("pthread_cond_wait");
    }
}

void Condition::notify()
{
    if (pthread_cond_signal(&_cond))
    {
        perror("pthread_cond_signal");
    }
}

void Condition::notifyall()
{
    if (pthread_cond_broadcast(&_cond))
    {
        perror("pthread_cond_broadcast");
    }
}

// ----------------- MutexLock
MutexLock::MutexLock()
{
    if (pthread_mutex_init(&_mutex, nullptr))
    {
        perror(">> pthread_mutex_init");
    }
}

MutexLock::~MutexLock()
{
    if (pthread_mutex_destroy(&_mutex))
    {
        perror(">> pthread_mutex_destroy");
    }
}

void MutexLock::lock()
{
    // 加锁
    if (pthread_mutex_lock(&_mutex))
    {
        perror(">> pthread_mutex_lock");
    }
}

void MutexLock::unlock()
{
    // 解锁
    if (pthread_mutex_unlock(&_mutex))
    {
        perror(">> pthread_mutex_unlock");
    }
}
// ----------------------- producer
// 跟taskque形成关联关系(彼此独立)
// 使用引用 TaskQueue &taskque
Producer::Producer(TaskQueue &taskque)
    : _taskQue(taskque)
{
}

void Producer::run()
{
    int cnt = 20;
    ::srand(::clock());
    while (cnt--)
    {
        int number = ::rand() % 100;
        _taskQue.push(number);

        cout << ">> producer thread " << pthread_self()
             << " produc a number = " << number << endl;
        ::sleep(1);
    }
}
// ---------------- TaskQueue

TaskQueue::TaskQueue(size_t size)
    : _queSize(size), _mutex(), _notFull(_mutex), _notEmpty(_mutex)
{
}

bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//运行在生产者线程
void TaskQueue::push(ElemType elem)
{
    // 互斥锁
    MutexLockGuard autolock(_mutex);
    while (full())
    { //使用while 是为了防止虚假(异常)唤醒
        _notFull.wait();
    }
    // 队尾添加元素
    _que.push(elem);
    // 通知notemptty条件变量，然后再判断条件变量
    _notEmpty.notify();
}

//运行在消费者线程
ElemType TaskQueue::pop()
{
    // 面试；
    MutexLockGuard autolock(_mutex);
    // 为了防止多个线程同时被唤醒--虚假唤醒--用while进行判断，不用if判断
    // 如果没有使用while循环，被唤醒的时候条件变量还是被加锁的
    // 另外n-1个线程就算是full是true也不会去判断
    while (empty())
    {
        _notEmpty.wait();
    }
    // 获取对头元素
    ElemType elem = _que.front();
    // 对头元素出队
    _que.pop();
    // 通知notfull条件变量，然后再判断条件变量
    // 核心：push 和 pop 方法的切换
    _notFull.notify();

    return elem;
}

// test
int main(void)
{
    TaskQueue taskque(10);

    unique_ptr<Thread> producer(new Producer(taskque));
    unique_ptr<Thread> consumer(new Consumer(taskque));

    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}
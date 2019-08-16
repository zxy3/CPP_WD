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
#include <functional>
using namespace std;

// --------------------------thread bo写法----------------------------
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
    using ThreadCallback = std::function<void()>;
    Thread(ThreadCallback &&cb)
        : _pthid(0), _isRunning(false), _cb(std::move(cb))
    {
    }

    ~Thread(); //bo写法，不用虚函数

    void start();
    void join();

    static void *threadFunc(void *);

private:
    pthread_t _pthid;
    bool _isRunning;
    // 基于对象，不用虚函数，用回调函数
    ThreadCallback _cb;
};
// ------------------------- produce ------------------------------
class TaskQueue;
class Condition;

// -------------- producer bo写法
class Producer
{
public:
    // 生产数据
    void produce(TaskQueue &taskque)
    {
        ::srand(::clock());
        int cnt = 20;

        while (cnt--)
        {
            auto number = ::rand() % 100;
            taskque.push(number);

            cout << ">> producer thread " << pthread_self()
                 << " produc a number = " << number << endl;
            ::sleep(1);
        }
    }
};
// ---------------------MutexLock 与oo相同
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

// --------------------MutexLockGuard
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
// -------------------Condition 与oo相同
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
// -------------------------TaskQueue
using ElemType = int;
class TaskQueue
{
public:
    TaskQueue(size_t size);

    bool empty() const;
    bool full() const;
    void push(ElemType elem);
    ElemType pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};
// -------------------------Consumer------------------------------
// Consumer
class TaskQueue;
class Consumer
{
public:
    // bo写法
    // 消费数据
    void consume(TaskQueue &taskque)
    {
        int cnt = 20;
        while (cnt--)
        {
            int number = taskque.pop();
            cout << ">> consumer thread " << pthread_self()
                 << " consume a number = " << number << endl;
            ::sleep(1);
        }
    }
};

// ----------------------produce 成员函数实现 -----------------------
// ----------------Thread
Thread::~Thread()
{
    if (_isRunning)
    {
        pthread_detach(_pthid);
    }
    cout << "~Thread()" << endl;
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
        pthread->_cb(); //执行任务，bo回调函数写法
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
    if (pthread_mutex_lock(&_mutex))
    {
        perror(">> pthread_mutex_lock");
    }
}

void MutexLock::unlock()
{
    if (pthread_mutex_unlock(&_mutex))
    {
        perror(">> pthread_mutex_unlock");
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
    MutexLockGuard autolock(_mutex);
    while (full())
    { //使用while 是为了防止虚假(异常)唤醒
        _notFull.wait();
    }

    _que.push(elem);

    _notEmpty.notify();
}

//运行在消费者线程
ElemType TaskQueue::pop()
{
    MutexLockGuard autolock(_mutex);
    // 让每个线程在wait前被唤醒，解决一直被阻塞的情况
    while (empty())
    {
        _notEmpty.wait();
    }

    ElemType elem = _que.front();
    _que.pop();

    _notFull.notify();

    return elem;
}
// test
int main(void)
{
    TaskQueue taskque(10);
    // Producer()用来创建一个临时对象，也可以创建指针
    // std::ref引用包装器
    unique_ptr<Thread> producer(new Thread(
        std::bind(&Producer::produce, Producer(), std::ref(taskque))));

    unique_ptr<Thread> consumer(new Thread(
        std::bind(&Consumer::consume, Consumer(), std::ref(taskque))));

    producer->start();
    consumer->start();
    producer->join();
    consumer->join();

    return 0;
}
// 需要自己写，花时间感受，先想清楚，再敲代码
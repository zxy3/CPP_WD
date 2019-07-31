///Auto-destructing3 pthread_once + atexit

#include <stdlib.h>
#include <pthread.h>

#include <iostream>
using namespace std;

class AutoDestruct
{
public:
    // 静态成员初始化--全局静态区
    static AutoDestruct *getInstance()
    {
        // 依赖于pthread_once接口进行初始化
        pthread_once(&_once, init);

        cout << _pAutoDes << endl;
        return _pAutoDes;
    }
    static void init()
    {
        _pAutoDes = new AutoDestruct();
        // 匿名空间写法
        ::atexit(destory);
    }
    // 销毁
    static void destory()
    {
        if (_pAutoDes)
        {
            cout << "destory()" << endl;
            delete _pAutoDes;
        }
    }
    // 成员函数
private:
    // 单例模式--构造函数私有化
    AutoDestruct()
    {
        cout << "AutoDestruct()" << endl;
    }
    // 单例模式--析构函数私有化
    ~AutoDestruct()
    {
        cout << "~AutoDestruct()" << endl;
    }
    // 单例模式的静态成员
private:
    static AutoDestruct *_pAutoDes;
    // 携带一个pthread_once类成员,接口需要
    static pthread_once_t _once;
};
// 静态成员的初始化--恶汉模式（编译时就创建）
AutoDestruct *AutoDestruct::_pAutoDes = getInstance();
// PTHREAD_ONCE_INIT ?
pthread_once_t AutoDestruct::_once = PTHREAD_ONCE_INIT;

// 测试代码
int main(void)
{
    AutoDestruct *p1 = AutoDestruct::getInstance();
    AutoDestruct *p2 = AutoDestruct::getInstance();
    AutoDestruct *p3 = AutoDestruct::getInstance();
    cout << "p1 = " << p1 << endl
         << "p2 = " << p2 << endl
         << "p3 = " << p3 << endl;

    return 0;
}
#include <iostream>
using namespace std;

// 模板类
template <class T>
class Singleton
{
    // 垃圾回收类
    class AutoRelease
    {
    public:
        // 构造函数
        AutoRelease() { cout << "AutoRelease()" << endl; }
        // 析构函数
        ~AutoRelease()
        {
            if (_pInstance)
                delete _pInstance;

            cout << "~AutoRelease()" << endl;
        }
    };

public:
    // 模板类构造函数
    template <class... Args>
    static T *getInstance(Args... args)
    {
        if (_pInstance == nullptr)
        {
            (void)_auto;
            _pInstance = new T(args...);
        }
        return _pInstance;
    }

private:
    // 单例模式：私有化构造函数和析构函数
    Singleton() { cout << "Singleton()" << endl; }
    ~Singleton() { cout << "~Singleton()" << endl; }

private:
    static T *_pInstance;
    static AutoRelease _auto;
};
// 静态成员，类外初始化
template <class T>
T *Singleton<T>::_pInstance = nullptr;
// 嵌套类内部成员，类外初始化固定写法
template <class T>
class Singleton<T>::AutoRelease Singleton<T>::_auto;
// 普通类
class Point
{
public:
    Point(int ix, int iy)
        : _ix(ix), _iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }

    ~Point() { cout << "~Point()" << endl; }

private:
    int _ix;
    int _iy;
};

int main(void)
{
    Point *pt = Singleton<Point>::getInstance(1, 2);
    Point *pt2 = Singleton<Point>::getInstance(1, 2);

    cout << "pt= " << pt << endl;
    cout << "pt2= " << pt2 << endl;

    return 0;
}

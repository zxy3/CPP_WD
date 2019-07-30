///Auto-destructing2 静态成员函数 + atexit
///放弃垃圾回收类
#include <iostream>
using namespace std;

class AutoDestruct
{
public:
    // 静态成员初始化--全局静态区
    static AutoDestruct *getInstance()
    {
        if (nullptr == _pAutoDes)
            // 注册一个atexit函数，达到自动回收的效果
            ::atexit(destory);
        {
            _pAutoDes = new AutoDestruct();
        }
        cout << _pAutoDes << endl;
        return _pAutoDes;
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
    // 携带一个内部类成员
    // static GarbageCollection _gar;
};
// 静态成员的初始化--恶汉模式（编译时就创建）
AutoDestruct *AutoDestruct::_pAutoDes = getInstance();
// AutoDestruct::GarbageCollection AutoDestruct::_gar;

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
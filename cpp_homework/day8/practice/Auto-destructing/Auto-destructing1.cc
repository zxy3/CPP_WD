///Auto-destructing 嵌套类+静态对象
#include <iostream>
using namespace std;

class AutoDestruct
{
    // 回收垃圾类
    class GarbageCollection
    {
    public:
        // 构造函数
        GarbageCollection()
        {
            cout << " GarbageCollection()" << endl;
        }
        // 析构函数--销毁外部类的成员
        ~GarbageCollection()
        {
            cout << "~GarbageCollection() 垃圾自动回收" << endl;
            // 销毁外部类的成员
            if (_pAutoDes)
            {
                delete _pAutoDes;
            }
        }
        // 成员函数
    private:
        // 无私有成员，内部类自动拥有所有外部类的成员
    };

public:
    // 静态成员初始化--全局静态区
    static AutoDestruct *getInstance()
    {
        if (nullptr == _pAutoDes)
        {
            _pAutoDes = new AutoDestruct();
        }
        return _pAutoDes;
    }
    // 销毁
    static void destory()
    {
        if (_pAutoDes)
        {
            cout << "垃圾类销毁" << endl;
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
    static GarbageCollection _gar;
};
// 静态成员的初始化
AutoDestruct *AutoDestruct::_pAutoDes = nullptr;
AutoDestruct::GarbageCollection AutoDestruct::_gar;

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
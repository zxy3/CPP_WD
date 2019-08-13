#include <bits/stdc++.h>
using namespace std;
// 23种设计模式-->单例设计模式：一个类智能创建一个对象(2min写完)
// 1、单例模式替换全局变量
// 2、配置文件中存储的都是程序的输入信息
// 3、词典库，网页库需要全局唯一
class Singleton
{
private:
    // 私有化构造函数
    static Singleton *_pSingleton;
    Singleton()
    {
        cout << "Singleton()" << endl;
    }
    // 析构函数
    ~Singleton()
    {
        cout << "销毁" << endl;
    }

public:
    // 静态构造函数
    static Singleton *getSingleton()
    {
        if (nullptr == _pSingleton)
        {
            _pSingleton = new Singleton();
        }
        return _pSingleton;
    }

    static void destroy()
    {
        if (_pSingleton)
        {
            delete _pSingleton;
        }
    }
};
// 静态成员变量在类外部初始化
Singleton *Singleton ::_pSingleton = nullptr;
int main(void)
{
    // Singleton *p = new Singleton();
    Singleton *p1 = Singleton::getSingleton();
    Singleton *p2 = Singleton::getSingleton();
    Singleton *p3 = Singleton::getSingleton();
    cout << "p1 = " << p1 << endl
         << "p2 = " << p2 << endl
         << "p3 = " << p3 << endl;

    //delete p1;//error
    Singleton::destroy();

    return 0;
}
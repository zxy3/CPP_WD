#include <bits/stdc++.h>
using namespace std;

template <typename T>
class mySingleton
{
public:
    // 嵌套模板类
    
    static T *getInstance()
    {
        // if (NULL == _pInstance)
        // {
        //     _pInstance = new T;
        //     // 注册销毁函数
        //     atexit(Destory);
        // }
        atexit(Destory);
        return m_pInstance;
    }

private:
    // 构造|析构函数私有化
    mySingleton() = default;
    ~mySingleton()
    {
        cout << "_pInstance" << endl;
    }
    // 销毁
    static void Destory()
    {
        if (_pInstance)
        {
            delete _pInstance;
        }
    }

private:
    static T *_pInstance;
}
// 静态成员初始化
template <class T>
T *mySingleton<T>::_pInstance = new T;

// test
int main(void)
{
    Computer *p1 = mySingleton<Computer>::getInstance();
    // Computer *p2 = Singleton<Computer>::getInstance("Xiaomi", 6666);

    // Point　*p3 = Singleton<Point>::getInstance(1, 2);
    // Point　*p4 = Singleton<Point>::getInstance(1, 2);

    return 0;
}

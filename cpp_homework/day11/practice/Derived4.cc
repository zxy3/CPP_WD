///含有虚函数的类，其析构函数都要是虚函数
#include <string.h>
#include <iostream>
using namespace std;

class base
{
private:
    // 定义一个指针，后续开辟空间
    char *_pbase = nullptr;

public:
    // 默认构造函数
    base() = default;
    // 堆初始化，构造函数
    base(const char *base)
        : _pbase(new char[strlen(base) + 1]())
    {
        cout << "base --> base(const char* base)" << endl;
        strcpy(_pbase, base);
    }
    virtual ~base()
    {
        if (_pbase)
        {
            delete[] _pbase;
            cout << "base --> ~base()" << endl;
        }
    }
    // 成员函数-虚函数
    virtual void display() const
    {
        cout << " _pbase " << _pbase << endl;
    }
};

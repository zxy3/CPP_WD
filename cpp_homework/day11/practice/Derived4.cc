///含有虚函数的类，其析构函数都要是虚函数
#include <string.h>
#include <iostream>
using namespace std;

class base
{
private:
    // 定义一个指针，后续开辟空间
    char *_pbase;

public:
    // 默认构造函数
    // base() = default;
    // 堆初始化，构造函数
    base(const char *base1)
        : _pbase(new char[strlen(base1) + 1]())
    {
        cout << "base --> base(const char* base)" << endl;
        strcpy(_pbase, base1);
    }
    // 具有虚函数的类，析构函数也要写成虚函数
    virtual ~base()
    {
        if (_pbase)
        {
            delete[] _pbase;
        }
        cout << "base --> ~base()" << endl;
    }
    // 成员函数-虚函数
    virtual void display() const
    {
        cout << " _pbase " << _pbase << endl;
    }
};

// 派生类
class Derived
    : public base
{
private:
    /* data */
    char *_pderived;

public:
    // Derived(/* args */) = default;
    // 变量名不可与基类类名相同，否则会报错
    Derived(const char *base1, const char *derived)
        : base(base1),
          _pderived(new char[strlen(derived) + 1]())
    {
        strcpy(_pderived, derived);
        cout << "派生类  --> Derived(const char* base,const char * derived)" << endl;
    }
    ~Derived()
    {
        if (_pderived)
        {
            delete[] _pderived;
        }
        cout << "派生类 --> ~derived()" << endl;
    }
    void display() const
    {
        cout << "_pderived = " << _pderived << endl;
    }
};

int main(void)
{
    base *bas = new Derived("基类", "派生类");
    // base ba("基类");
    // 此时指针指向基类对象，调用就是基类的方法
    // ba.display();
    // 基类指向派生类的对象，调用的就是派生类的方法
    bas->display();
    // 开辟空间后需要手动析构，析构顺序与构造顺序相反，先析构派生类再析构自己
    delete bas;
    // 对象的手动析构
    // ba.~base();
    return 0;
}
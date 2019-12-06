///验证虚函数表的存在
#include <iostream>
using namespace std;

class base
{
private:
    /* data */
    long _base = 0;

public:
    base(/* args */) = default;
    base(long base)
        : _base(base)
    {
        cout << "基类 --> base()" << endl;
    }
    // 基類所有方法都是虛函數
    
    virtual void fun1()
    {
        
        cout << "base --> fun1()-->虛表1號位置" << endl;
    }
    virtual void fun2()
    {
        cout << "base --> fun2() --> 虚表的2号位置" << endl;
    }
    virtual void fun3()
    {
        cout << "base --> fun3() --> 虚表的3号位置" << endl;
    }
    virtual ~base()
    {
        cout << "base --> ~base()" << endl;
    }
};

// 派生類
class derived
    : public base
{
public:
    derived(long base1, long derived)
        : base(base1), _derived(derived)
    {
        cout << "derived --> derived(long base,long derived)" << endl;
    }

private:
    long _derived = 0;

protected:
};
// main
int main(void)
{
    // 基類對象
    base ba(11);
    // 16
    cout << "sizeof (base) --> " << sizeof(base) << endl;
    // 虛表位置
    long *p = (long *)&ba;
    cout << "base --> located --> " << p << endl;
    cout << "base --> located --> " << p[0] << endl;

    // 定義函數指針
    // 先起個名字
    typedef void (*function)(void);
    long *p2 = (long *)p[0];
    // 虚表的1号位置
    function f = (function)p2[0];
    f();
    // 虚表的2号位置
    f = (function)p2[1];
    f();
    // 虚表的3号位置
    f = (function)p2[2];
    f();

    return 0;
}
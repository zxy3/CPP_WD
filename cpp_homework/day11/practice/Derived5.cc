///抽象类
#include <iostream>
using namespace std;

class base
{
public:
    virtual void display() const
    {
        cout << "_base" << _base << endl;
    }

protected:
    // 构造函数被放在了protected区域---抽象类
    base() = default;
    base(long base)
        : _base(base)
    {
        cout << "基类 ---> base()" << endl;
    }

private:
    long _base = 0;
};
// 派生类
class derived
    : public base
{
public:
    derived(long base1, long derived)
        : base(base1),
          _derived(derived)
    {
        cout << "派生类 --> derived()" << endl;
    }
    // 派生类 -- 虚函数
    virtual void display() const
    {
        cout << "派生类 --> display()--> _derived =  " << _derived << endl;
    }

private:
    long _derived = 0;

protected:
};

int main(void){
    derived de(1,2);
    // 基类指针指向派生类
    base *ba = &de;
    // 此时应当指向派生类的打印方法
    ba->display();
}
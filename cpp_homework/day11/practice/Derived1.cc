///继承的调用
#include <iostream>
using namespace std;

class base
{
    // private:
protected:
    /* data */
    int _base;

public:
    base(/* args */) = default;
    base(int base)
        : _base(base)
    {
        cout << "基类 --> base()  "
             << _base << endl;
    }
    // ~base();
    // 设置一个虚函数
    virtual void print()
    {
        cout << "基类 ---> virtual void print()" << endl;
    }
    // 调用自己的虚函数
    void test1()
    {
        // 直接用类名调用
        base::print();
    }
    // 调用派生类的函数（多态的体现）
    void test2()
    {
        // 基类调this是基类，派生类调this是派生类
        this->print();
    }
};
// 派生类
class child
    : public base
{
private:
    /* data */
    int _child = 0;

public:
    child(/* args */) = default;
    child(int base1, int child)
        : base(base1),
          _child(child)
    {
        cout << "派生类 ---> child(intn base1,int shild)" << endl;
    }
    // ~child();
    // 派生类的打印函数
    void print()
    {
        cout << "派生类 ---> print()  " << _child << endl;
    }
};
// 测试类
int main(void)
{
    // 派生类调自己的方法
    child ch(10, 20);
    ch.print();
    // 派生类调基类的方法
    ch.test2();
    // 定义基类对象，调用派生类的函数
    base bs(1);
    bs.test1();
    bs.test2();
    return 0;
}

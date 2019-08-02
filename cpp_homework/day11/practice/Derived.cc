///多继承
///解决类的二义性问题

#include <iostream>
using namespace std;

class A
{
private:
public:
    void print()
    {
        cout << "这是case A" << endl;
    }
};
class B
{
private:
public:
    void print()
    {
        cout << "这是case B" << endl;
    }
};
class C
{
private:
public:
    void print()
    {
        cout << "这是case C" << endl;
    }
};
// class D多继承ABC类
class D
    : public A,
      public B,
      public C
{
public:
    D() : A(),
          B(),
          C(),
          _ix(1),
          _iy(2)
    {
        cout << "这里是D的构造函数" << endl;
    }

private:
    int _ix;
    int _iy;

public:
    // ~D();
};
//测试

int main(void)
{
    D d;
    // 使用类作用域指定要调用基类的函数
    d.A::print();
    d.B::print();
    d.C::print();
    return 0;
}

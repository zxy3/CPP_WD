///改变字节对齐方式,默认8字节对齐，修改为4字节对齐
#include <iostream>
using namespace std;

// 修改为4字节对齐方式
#pragma pack(push)
#pragma pack(4)

class base
{
private:
    /* data */
public:
    base(/* args */);
    // ~base();
    virtual void print() const
    {
        cout << "基类———>打印函数" << endl;
    }
};

class child
    : public base
{
private:
    /* data */
public:
    child(/* args */);
    ~child();
    virtual void print()
    {
        cout << "派生类——>打印函数" << endl;
    }

    int _a;            //4字节
    double _d;         //8字节
    char _c;           //1字节
    short _s;          //10
    int &_i;           //指针8个字节
    static double _do; //8个字节
};
#pragma pack(pop)

// test
int main(void)
{
    cout << sizeof(base) << endl;
    cout << sizeof(child) << endl;

    return 0;
}

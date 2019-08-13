///weak_ptr
#include <iostream>
#include <memory>
using namespace std;

class point
{
private:
    int _ix = 0;
    int _iy = 0;

public:
    //构造函数1
    point() = default;
    //构造函数2
    point(int ix, int iy)
        : _ix(ix),
          _iy(iy)
    {
        cout << "point(int ix, int iy)" << endl;
    }
    //析构函数
    ~point()
    {
        cout << "~point()" << endl;
    }
    //-------------------成员函数-------------------------
    void print(void)
    {
        cout << "ix = " << _ix << " iy = " << _iy << endl;
    }
    // 友元
    friend std::ostream &operator<<(std::ostream &os, const point &rhs);
};

// 类外实现友元函数
std::ostream &operator<<(std::ostream &os, const point &rhs)
{
    os << "ix = " << rhs._ix
       << " iy = " << rhs._iy;
    return os;
}
// test
int main(void)
{
    // weak和share ptr配套使用,weak_ptr不增加引用计数的一种指针
    weak_ptr<point> wp;
    {
        shared_ptr<point> sp(new point(1, 2));
        // 交给wp托管
        wp = sp;
        cout << "wp 引用计数 -----> " << wp.use_count() << endl;
        cout << "sp 引用计数 -----> " << sp.use_count() << endl;
        // 0 表明托管的对象，还在，没有过期
        cout << "wp expired -----> " << wp.expired() << endl;
        // 权限提升接口
        shared_ptr<point> sp2 = wp.lock();
        cout << "sp2 引用计数 -----> " << sp2.use_count() << endl;
        if (sp2)
        { // 提升成功
            cout << "*sp2 ---------> " << *sp2 << endl;
        }
        else
        { //提升失败
            cout << "wp托管的对象已经被销毁了!" << endl;
        }
    }
    // 1 此时wp托管的对象生命周期已经结束,权限不能被提升
    cout << "wp's expired = " << wp.expired() << endl;
    shared_ptr<point> sp2 = wp.lock();
    if (sp2)
    { // 提升成功
        cout << "*sp2 = " << *sp2 << endl;
    }
    else
    { //提升失败
        cout << "wp托管的对象已经被销毁了!" << endl;
    }
    return 0;
}
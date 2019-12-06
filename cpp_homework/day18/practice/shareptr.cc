///智能指针
#include <iostream>
#include <memory>
using namespace std;

// class
class point
{
private:
    int _ix = 0;
    int _iy = 0;

public:
    // 构造函数
    point() = default;
    point(int ix, int iy)
        : _ix(ix),
          _iy(iy)
    {
        cout << "point(int ix,int iy)" << endl;
    }
    // 析构函数
    ~point()
    {
        // 没有开辟空间，打印一句话就可以了
        cout << " ~point()" << endl;
    }
    // -------------成员函数-----------------
    // 打印函数
    void print() const
    {
        cout << "ix = " << _ix << " iy = " << _iy << endl;
    }
    // friend 重载流运算符
    friend std::ostream &operator<<(std::ostream &os, const point &rhs);
};

// 友元函数，类外实现
std::ostream &operator<<(std::ostream &os, const point &rhs)
{
    os << "ix = " << rhs._ix << " iy = " << rhs._iy;
    return os;
}
// test
void test0(void)
{
    point *pt = new point(1, 2);
    // 悬垂指针
    shared_ptr<point> sp(pt);
    shared_ptr<point> sp2(sp);
    // （1,2）对象上所指的所有指针数,不包含this指针
    cout << "---> sp（1,2）对象上所指的指针数" << sp.use_count() << endl;
    cout << "---> sp2（1,2）对象上所指的指针数" << sp2.use_count() << endl;
    // 所指向对象,是同一个对象
    cout << "*sp -----------> " << *sp << endl
         << "*sp2-----------> " << *sp2 << endl;

    // 生命周期,括号结束就完了
    {
        cout << "---------------------------------------" << endl;
        shared_ptr<point> sp3(new point(11, 12));
        cout << "*sp3 -------> " << *sp3 << endl;
        cout << "*sp2 -------> " << *sp2 << endl;
        sp3 = sp2;
        // 此时相当于有3个指针，指向（1,2）对象
        cout << "执行赋值操作之后: " << endl;
        cout << "*sp3 = " << *sp3 << endl;
        // 此时的引用计数应该是3，不论用那个指针获取，都是一样的
        cout << "sp 引用计数 ---------> " << sp.use_count() << endl;
        cout << "sp2 引用计数 ---------> " << sp2.use_count() << endl;
        cout << "sp3 引用计数 ----------> " << sp3.use_count() << endl;
    }
    // sp3生命周期结束,指针消失
    cout << "-----------------------------------" << endl;
    cout << "sp 引用计数 ---------> " << sp.use_count() << endl;
    cout << "sp2 引用计数 ----------> " << sp2.use_count() << endl;
}
// main
int main(void)
{
    test0();
    return 0;
}
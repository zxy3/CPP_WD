///unique
#include <iostream>
#include <memory>
#include <vector>
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
// test0
int test0(void)
{
    // 先创建一个新对象
    point *pt = new point(1, 2);
    unique_ptr<point> ap(pt);
    cout << "ap ------> " << *ap << endl;
    // 此时unique_ptr所指与pt所指是同一个位置
    cout << "ap.get() ------> " << ap.get() << endl;
    cout << "pt = " << pt << endl;

    // unique_ptr同类之间，不能进行复制或者赋值,但是可以移动,移动也只能是同类之间
    unique_ptr<point> ap2(move(ap));
    // 此时ap已经是空的了，move不是复制，对象依然只有1个
    cout << "*ap2 = " << *ap2 << endl;
    cout << "ap2.get() = " << ap2.get() << endl;
    // cout << "*ap = " << *ap << endl;
    // cout << "ap.get() = " << ap.get() << endl;
    // 利用右值初始化对象
    cout << "-------------------------------------" << endl;
    unique_ptr<point> ap3(new point(3, 4));
    point *pt2 = new point(66, 66);
    // reset接口，不同类之间的那种,reset之后原来的指针不变
    ap3.reset(pt2);
    cout << "*pt2 --------> " << *pt2 << endl;
    cout << "*ap3 --------> " << *ap3 << endl;
    cout << "ap3.get() = " << ap3.get() << endl;
    return 0;
}
// test2
unique_ptr<point> getpoint()
{
    // 提升,类似share_ptr
    unique_ptr<point> up(new point(22, 23));
    cout << "*up --------> " << *up << endl;
    return up;
}
int test1()
{
    unique_ptr<point> up = getpoint();
    // 起别名
    using pointptr = unique_ptr<point>;
    vector<pointptr> points;
    points.push_back(std::move(up));
    cout << "*points[0] --------> " << *points[0] << endl;

    // emplace_back接口，往集合里追加临时对象
    points.emplace_back(new point(11, 12));
    // points.push_back(new point(21, 12));这种方法不行
    cout << "*points[1] = " << *points[1] << endl;

    return 0;
}
// main
int main(void)
{
    test0();
    return 0;
}
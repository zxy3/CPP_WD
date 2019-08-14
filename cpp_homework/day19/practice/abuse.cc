#include <iostream>
#include <memory>
using namespace std;

class Point
    : public std::enable_shared_from_this<Point>
{
public:
    // 构造函数
    Point(int ix = 0, int iy = 0)
        : _ix(ix),
          _iy(iy)
    {
        // cout << "Point(int,int)" << endl;
    }
    // 成员函数
    void print() const
    {
        cout << "ix  " << _ix << "  iy  " << _iy << endl;
    }

    //Point * addPoint(Point * pt)
    // 返回一个指针
    shared_ptr<Point> addPoint(Point *pt)
    { //在成员函数内部获取本对象的shared_ptr智能指针
        _ix += pt->_ix;
        _iy += pt->_iy;

        //return shared_ptr<Point>(this);
        return shared_from_this();
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

private:
    int _ix;
    int _iy;
};
// 一个unique_ptr"拥有“他所指向的对象。与shared_ptr不同，
// 某个时刻只能有一个unique_ptr指向一个给定的对象。
// 当unique_ptr被销毁时，它所指向的对象也被销毁。
// uniptr_ptr表达的是一种独占的思想。
// 用uniptr_ptr管理对象的生命周期

// test0
void test0()
{
    //误用: 把一个原生裸指针交给不同的智能指针进行托管
    Point *pt = new Point(1, 2);
    unique_ptr<Point> up1(pt);
    cout << "up1 ----> " << up1.get() << endl;
    cout << "pt -----> ";
    pt->print();
    cout << "up1 ----> ";
    up1->print();

    // 此时不能再使用另外一个指针指向创建的对象
    // unique_ptr<Point> up2(pt);
}
// test1
void test1()
{
    Point *pt = new Point(1, 2);
    shared_ptr<Point> up1(pt);
    shared_ptr<Point> up2(pt);  //此时不会增加引用计数(悬垂指针)
    shared_ptr<Point> up2(up1); //此时会增加引用计数
    cout << "shared_ptr up1 引用计数 ----> " << up1.use_count() << endl;
    cout << "shared_ptr up2 引用计数 ----> " << up2.use_count() << endl;
}

// main
int main(void)
{
    // test0();
    test1();
    return 0;
}
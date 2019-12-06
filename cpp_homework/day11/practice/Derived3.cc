///开闭原则
#include <math.h>
#include <iostream>
using namespace std;

// 除了接口什么都不用给
class base
{
public:
    virtual void display() const = 0;
    virtual double area() const = 0;
};
// 类外实现,用指针调用,指针指向对应的对象
void print(base *ba)
{
    ba->display();
    cout << "的面积是:" << ba->area() << endl;
}
// 派生类
class Rectangle
    : public base
{
public:
    Rectangle(double da, double da1)
        : _do(da),
          _dou(da1)
    {
        cout << "Rectangle" << endl;
    }
    double area() const
    {
        cout << _do * _dou;
    }
    void display() const
    {
        cout << "Rectangle --> print()";
    }

private:
    double _do;
    double _dou;
};

class circle
    : public base
{
private:
    /* data */
    double _radius;

public:
    circle(double radius) : _radius(radius)
    {
        cout << "circle" << endl;
    }
    // ~circle();
    // 重写基类的接口
    void display() const
    {
        cout << "Rectangle --> print()";
    }
    // 重写基类的接口
    double area() const
    {
        return 3.1415 * _radius * _radius;
    }
};

class cube
    : public base
{
public:
    cube(double a)
        : _a(a)
    {
        cout << "cube" << endl;
    }
    // 重写接口
    void display() const
    {
        cout << "cube --> print()";
    }
    double area() const
    {
        return 6 * _a * _a;
    }

private:
    double _a;
};
// test
int main(void)
{
    Rectangle re(1, 2);
    circle ci(2);
    cube cu(3);
    print(&re);
    print(&ci);
    print(&cu);
    return 0;
}
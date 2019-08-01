///protected继承  
///可以访问protected的成员
#include <iostream>
using namespace std;

// 基类
class Point
{
public:
    // 构造函数
    Point(int a = 0, int b = 0)
        : _a(a), _b(b)
    {
        cout << "基类构造函数 Point(int a = 0, int b = 0)"
             << _a << " " << _b << endl;
    }
    // 析构函数
    ~Point()
    {
        cout << "此为基类的析构函数" << endl;
    }
    void display()
    {
        // 打印基类的成员
        cout << "基类: " << _a << " " << _b << endl;
    }

protected:
    int _a;
    // int _b;
    int geta()
    {
        cout << "基类的保护方法: get()" << _a << endl;
        return _a;
    }

private:
    // 放到私有区域就不能再访问被访问了
    // int _a;
    int _b;
};

//派生类
class Point1
    : protected Point
{
public:
    // 派生类的构造函数
    Point1(int a = 0, int b = 0, int c = 0)
        // 依赖基类完成构造函数
        : Point(a, b),
          _c(c)
    {
        cout << "派生类的构造函数Point1(int a = 0, int b = 0, int c = 0)"
             << _a << " " << _b << " " << _c << endl;
    }
    // 派生类的析构函数
    ~Point1()
    {
        cout << "此为派生类的析构函数" << endl;
    }
    void display()
    {
        cout << "此为派生类的public: " << _a
             << " " << _b << " " << _c << endl;
    }

protected:
    int getC()
    {
        cout << "派生类的保护方法: " << _c << endl;
    }

private:
    // int _a;  基类有定义过，父类就不能再定义相同的成员了
    // int _b;  基类有定义过，父类就不能再定义了
    int _c;
};

//测试1
void test0()
{
    Point1 p1(1, 2, 3);
    p1.display();
}
// main
int main()
{
    test0();
    return 0;
}
#include <iostream>
using std::cout;
using std::endl;
using namespace std;
#define PI 3.14

// Circle
class Circle
{
private:
    /* 半径 */
    double _radius = 0;

public:
    // 构造函数
    Circle() = default;
    Circle(double radius)
        : _radius(radius)
    {
        cout << "Circle(double radius)" << endl;
    }
    // 析构函数
    ~Circle()
    {
        cout << "~Circle()" << endl;
    }
    //获取圆的面积
    double getArea()
    {
        return PI * _radius * _radius;
    }
    //获取圆的周长
    double getPerimeter()
    {
        return 2 * PI * _radius;
    }
    //将圆的半径、周长、面积输出到屏幕
    void show()
    {
        cout << "半径: " << _radius << " "
             << "周长" << getPerimeter() << " "
             << "面积" << getArea() << endl;
    }
};
#if 0
// 测试Circle
void test0(){
    Circle circle(2);
    circle.show();
}
#endif
class Cylinder
    : public Circle
{
private:
    /* 圆柱体高 */
    double _high = 0;

public:
    Cylinder() = default;
    Cylinder(double radius, double high)
        : Circle(radius),
          _high(high)
    {
        cout << "Cylinder(double radius,double high)" << endl;
    }
    ~Cylinder()
    {
        cout << "~Cylinder()" << endl;
    }
    //获取圆柱体的体积
    double getVolume()
    {
        return getArea() * _high;
    }
    //将圆柱体的体积输出到屏幕
    void showVolume()
    {
        cout << "圆柱体体积是: "
             << getVolume() << endl;
    }
};
#if 1
void test1()
{
    Cylinder cl(2, 4);
    cl.show();
    cl.showVolume();
}
#endif
int main(void)
{
    // test0();
    test1();
    return 0;
}
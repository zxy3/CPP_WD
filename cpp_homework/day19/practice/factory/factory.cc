/// 静态工厂模式
#include <math.h>
#include <iostream>
using namespace std;

// 开闭原则
class figure
{
public:
    // ---------------基类成员函数-----------------
    // 虚函数，相当于就是一个接口
    virtual void display() const
    {
        cout << "基类 --------> irtual void display() const" << endl;
    };
    // 虚函数，相当于就是一个接口
    virtual double area() const
    {
        cout << "基类 --------> virtual double area() const" << endl;
    };

private:
protected:
};
// ------------------普通函数----------------------
// 打印面积
void display(figure *fig)
{
    fig->display();
    cout << " 的面积是: " << fig->area() << endl;
}
// -----------------派生类------------------------
class rectangle
    : public figure
{
private:
    double _len = 0;
    double _wid = 0;

public:
    // 构造函数
    rectangle() = default;
    rectangle(int len, int wid)
        : _len(len), _wid(wid)
    {
        cout << "len = " << _len << " wid = " << _wid << endl;
    }
    // 析构函数
    ~rectangle()
    {
        cout << " ~rectangle()" << endl;
    }
    // -----------------成员函数-----------------
    // 打印形状
    void display() const
    {
        cout << "rectangel";
    }
    // 计算面积
    double area() const
    {
        return _len * _wid;
    }

protected:
};
// 其他类----以此类推

// 工厂模式---工厂类
class factory
{
private:
    // 工厂类是没有自己的成员的，工厂属于一个调度中心
public:
    // 不用写构造函数和析构函数，工厂类中用的都是其他类的成员和其他类的成员函数
    // 构造函数
    factory();
    // 析构函数
    ~factory();
    //-----------------------成员函数-----------------------
    // 计算矩形面积
    static rectangle createrectangle()
    {
        // 工厂生产出来的东西都是一样的
        rectangle rec(3, 4);
        return rec;
    }
    // 计算
};

int main(void)
{
    rectangle rec = factory::createrectangle();

    display(&rec);
}
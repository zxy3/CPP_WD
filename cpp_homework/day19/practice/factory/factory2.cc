/// 动态工厂模式
#include <math.h>
#include <iostream>
#include <memory>
using namespace std;

// 开闭原则
class figure //提供统一接口
{
public:
    // 析构函数
    virtual ~figure()
    {
        cout << "~figure()" << endl;
    }
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
    rectangle(double len, double wid)
        : _len(len), _wid(wid)
    {
        cout << "len = " << _len << " wid = " << _wid << endl;
    }
    // 析构函数
    // ~rectangle()
    // {
    //     cout << " ~rectangle()" << endl;
    // }
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

// 工厂模式
// 适用背景：针对复杂对象，批量创建对象
// 抽象工厂：一个工厂生产多种系列的产品

class factory
{
private:
public:
    // 工厂提供生产接口，生产工作交给车间来完成（虚函数+开闭原则）
    // 构造函数
    factory() = default;
    // 析构函数
    virtual ~factory()
    {
        cout << "~factory()" << endl;
    }
    // 成员函数
    virtual figure *create()
    {
        cout << "virtual figure *create()" << endl;
    };

protected:
};

// --------------- 派生类 ------------------
// 各个产品的车间
class rectanglefactory
    : public factory
{
public:
    figure *create()
    {
        return new rectangle(3, 4);
    }

private:
protected:
};
// 其他图形的车间，一次类推

// test
int main(void)
{
    unique_ptr<factory> rec(new rectanglefactory());
    unique_ptr<figure> rect(rec->create());
    // 打印面积
    cout << "rect.get() -------> " << rect.get() << endl;
    display(rect.get());

    return 0;
}
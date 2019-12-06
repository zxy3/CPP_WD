///开闭原则
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class Shape
{
public:
    // 虚函数，就是一个接口
    virtual void Draw() = 0;
};

class Circle
    : public Shape
{
public:
    void Draw()
    {
        cout << "class Circle" << endl;
    }
};

class Square
    : public Shape
{
public:
    void Draw()
    {
        cout << "class Square" << endl;
    }
};

class Client
{
public:
    void DrawAllShapes(List<shared_ptr<Shape>> shapes)
    {
        for (auto &shape : shapes)
        {
            shape.Draw();
        }
    }
};

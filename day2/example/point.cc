#include <iostream>
using namespace std;
class point
{
private:
    int yPos; //先定义
    int xPos; //后定义
public:
    point(int x) 
    :xPos(x), yPos(xPos) //初始化表取决于成员声明的顺序
    {
    }
    void print()
    {
        cout << "xPos: " << xPos << ", yPos: " << yPos << endl;
    }
};

// #include "point.h"
int main()
{
    point pt1(3); //调用有参构造函数声明变量pt1
    pt1.print();
    return 0;
}

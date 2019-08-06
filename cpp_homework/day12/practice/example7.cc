///函数模版的隐式实例化
#include <iostream>
using namespace std;
// 函数模板的声明
template <class T>
T Max(T x, T y);
// test
int main()
{
    int intX = 1, intY = 2;
    double dblX = 3.9, dblY = 2.9;
    //实参为int型，生成int型模板函数，并对第二个参数进行检查
    cout << Max(intX, intY) << endl;
    cout << Max<int>(intX, intY) << endl;
    //实参为double型，生成double型模板函数，并对第二个参数进行检查
    cout << Max(dblX, dblY) << endl;
    //或者cout << Max<double>(dblX, dblY) << endl;

    return 0;
}

template <class T>
T Max(T x, T y) //函数模版的实现
{
    return (x > y ? x : y);
}

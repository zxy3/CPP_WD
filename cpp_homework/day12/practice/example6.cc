#include <iostream>
#include <string>
using namespace std;
// 模板函数参数列表跟函数参数列表是不同的
template <class T1, class T2, int number>
double fun(T1 a, T2 c, int b)
{
    cout << "a ------" << a << endl;
    cout << "b-----------" << b << endl;
    cout << "c---------" << c << endl;
    cout << "number-----------" << number << endl;
    return a * (number + b) * c;
    //函数体，其中number可以作为一个int型常量来使用
}

int main(void)
{
    // 传参的时候需要模板参数和函数参数同时传进去
    cout << fun<double, double, 3>(3.0,4.0,5) << endl;
    return 0;
}
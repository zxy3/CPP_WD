#include <iostream>
#include <string>
using namespace std;
// 模板函数的重载
// 类型参数
#if 0
template <class T>
T Func(T t)
{
    return t;
}
// 类型参数
template <class T>
int Func(int i, T t)
{
    return i * t;
}

//函数模板和普通函数的重载
template <class T>
T Max(T x, T y);

int Max(int x, int y)
{
    return x > y ? x : y;
}

int main(void)
{
    int intX = 1, intY = 2;
    double dblX = 3.0, dblY = 2.9;
    //调用Max(int,int)
    cout << Max(intX, intY) << endl;
    //显示实例化为double型，生成double型模板函数
    //显示实例化，根据传入的参数不同来判断
     cout << Max<double>(dblX, dblY) << endl;
    //隐式实例化char型，生成char型模板函数
    cout << Max('A', '8') << endl;
    return 0;
}

template <class T>
T Max(T x, T y)
{
    return x > y ? x : y;
}
#endif

#if 0
//函数模板和函数模板的重载
#include <iostream>
// 模板函数的声明
template <class T>
T Max(T x, T y);
// 模板函数的重载
template <class T>
T Max(T x, T y, T z)
{
    return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

int main()
{
    int intX = 1, intY = 2, intZ = 3;
    double dblX = 3.0, dblY = 2.9;
    //隐式实例化
    //调用实例化的Max(int,int)
    cout << Max<int>(intX, intY) << endl;
    //调用实例化的Max(int,int,int)
    cout << Max<int>(intX, intY, intZ) << endl;
    //显示实例化
    //显示实例化为double型，生成double型模板函数
    cout << Max<double>(dblX, dblY) << endl;
    //隐式实例化char型，生成char型模板函数
    cout << Max('A', '8') << endl;
    return 0;
}
// 模板函数的实现
template <class T>
T Max(T x, T y)
{
    // 参数类型由系统判断，传进来什么类型，系统就初始化成什么类型
    return x > y ? x : y;
}
#endif
#if 1
//普通函数模板和数组的重载
#include <iostream>
using namespace std;
// 模板函数
template <typename T>
T MAX(T a, T b)
{
    return a > b ? a : b;
}
// 模板函数的重载
// n个数中找到最大值
template <typename T>
T MAX(T a[], int n)
{
    T max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (max < a[i])
        {
            max = a[i];
        }
    }
    return max;
}

int main()
{
    // 每调用一次，实例化一次
    // 隐式实例化成Int类型
    cout << MAX(3, 4) << endl;
    // 显式实例化成int类型
    cout << MAX<int>(3, 4) << endl;
    // 求数组长度：sizeof(a) / sizeof(a[0])
    int a[] = {2, 9, 7, 3, 8, 5};
    // 隐式实例化成int类型的，因为数组是int类型的
    cout << MAX(a, sizeof(a) / sizeof(a[0])) << endl;
    // 显式实例化成int类型的
    cout << MAX<int>(a, sizeof(a) / sizeof(a[0])) << endl;
    return 0;
}
#endif
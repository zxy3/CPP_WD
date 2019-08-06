///模板的概念
//求最大值
#include <iostream>
using namespace std;
//宏定义
#if 0
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main()
{
    cout << MAX(3, 4) << endl;
    cout << MAX(3.4, 2.9) << endl;
    return 0;
}
#endif

//重载函数
#if 0
#include <iostream>
using namespace std;

int MAX(int a, int b)
{
    return a > b ? a : b;
}

double MAX(double a, double b)
{
    return a > b ? a : b;
}

int main()
{
    cout << MAX(3, 4) << endl;
    cout << MAX(3.4, 2.9) << endl;
    return 0;
}
#endif

//模板
#include <iostream>
using namespace std;

template <typename T>
T MAX(T a, T b)
{
    return a > b ? a : b;
}
// 此时不需要考虑a和b具体的值是什么
int main()
{
    cout << MAX(3, 4) << endl;
    cout << MAX(3.4, 2.9) << endl;

    cout << MAX("SD", "12") << endl;
    cout << MAX("ASD", "123") << endl;
    return 0;
}

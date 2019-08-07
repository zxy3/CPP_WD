//嵌套模版函数的模版类
#include <iostream>
using namespace std;

//普通类模版
template <class T1, class T2>
class Convert
{
public:
    T2 f(T1 data)
    {
        return T2(data);
    }
};

//嵌套了模版函数的类模版
template <class T1>
class Test
{
public:
    // 模板成员函数必须在模板类里面--模板成员函数的定义
    template <class T2>
    T1 f(T2 b) //模板成员函数定义
    {
        return T1(b);
    }
};

//template<class T1>
//template<class T2>
//T1 Test<T1>::f(T2 b)			//模板成员函数的实现
//{
//        return T1(b);			//将b由T2类型强制转换成T1类型
//}

int main()
{
    //普通模版类的使用
    Convert<char, int> c1;
    cout << c1.f('A') << endl;

    Convert<float, int> c2;
    cout << c2.f(9.85f) << endl;

    Convert<int, short> c3;
    cout << hex << showbase << c3.f(0x7fffffff) << endl
         << dec;
    //通过上述3个例子，发现有些不太人性化, 必须指明第一个模版参数
    //其实这个参数就是函数f的参数，没必要指定。
    //这可以使用嵌套模版函数的模版类来解决。见Test类的实现。

    //嵌套模版类的使用
    Test<int> t;
    cout << t.f(3.14f) << endl;

    // getchar(); linux里面可以不用这句话
    return 0;
}

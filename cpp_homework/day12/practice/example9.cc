///函数优先级
#include <iostream>
#include <string>
using namespace std;

// 普通函数
int Max(int i1, int i2)
{
    cout << "Normal Max ------> " << endl;
    return i1 > i2 ? i1 : i2;
}
// 模板函数
template <class T>
T Max(T t1, T t2)
{
    cout << "Template Max,sizeof(t1) -------> " << sizeof(t1) << endl;
    return t1 > t2 ? t1 : t2;
}
int main(int argc, char *argv[])
{
    int i1 = 1, i2 = 9;
    char c1 = 'a', c2 = 'b';
    //调用普通函数int Max(int i1,int i2)
    int iRet = Max(i1, i2);
    //调用模板实例化生成的char Max(char a,char b)
    char cRet = Max(i1, i2);
    // 执行普通函数，并没有取到值
    cout << "char -------> " << cRet << endl;
    //模板参数和返回值可以分开转换
    // 隐式转换
    //调用模板实例化生成的char Max(char a,char b)，最后将返回值隐式转换成int型
    int iRet2 = Max(c1, c2);
    // 显式转换
    //调用模板实例化生成的char Max(char a,char b)，
    int cRet2 = Max<char>(i1, i2);
    return 0;
}

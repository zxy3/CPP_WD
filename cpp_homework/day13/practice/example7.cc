///A模板做为B模板的参数
#include <iostream>
using namespace std;

template <class T, int num> //类型参数表
class Stack                 //Stack类定义
{
private:
    T sz[num]; //存储空间，用数组表示
public:
    int ReturnNum(); //判断栈是否为空
};

//参数列表不要求字字相同，但形式要相同
template <class T1, int num1>
int Stack<T1, num1>::ReturnNum()
{
    return num1; //返回数组大小
}

//函数模板，其类型参数表中包含一个类模板
template <template <class Type, int NUM> class TypeClass, class T1, int N>
void display()
{
    TypeClass<T1, N> ob;            //类模板的隐式实例化,创建对象ob,ba<类型>隐去
    cout << ob.ReturnNum() << endl; //调用ob的public成员函数
}

int main()
{
    display<Stack, int, 8>(); //函数模板的隐式实例化，并调用
    system("pause");
    return 0;
}

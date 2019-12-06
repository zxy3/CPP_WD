///重载函数的比较
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int add(int x, int y) //定义两个int类型相加的函数
{
    return x + y;
}

double add(double x, double y) //重载两个double类型相加的函数
{
    return x + y;
}

char *add(char *px, char *py) //重载两个字符数组相加的函数
{
    return strcat(px, py); //调用库函数strcat
}

int main()
{
    cout << add(1, 2) << endl; //调用add(const int,const int)

    cout << add(3.0, 4.0) << endl; //调用add(const double,const double)

    char x[10] = "Hello "; //创建字符数组，注意要留够大小
    char y[] = "C++";
    cout << add(x, y) << endl; //调用add(char*,char*)

    return 0;
}

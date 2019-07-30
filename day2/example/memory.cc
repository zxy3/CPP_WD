#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
// 栈
// |
// 堆
// |
// 全局静态区
// |
// 文字常量
// |
// 程序代码


// 全局/静态区
int a = 0;
char *p1; //即使没有显式进行初始化, 系统也会清零

int test0(void)
{
    int b;
    char s[] = "hello,world";
    char *p2; //栈上, 不会清零，野指针

    const char *p3 = "hello,world"; //文字常量区,只读,不能进行修改
    //*p3 = 'X';//error

    static int c = 0; //不在栈上，位于全局静态区
    ++c;
    p1 = new char[10];
    strcpy(p1, "hello,world");

    printf("全局变量&a = %p\n", &a);
    printf("栈&b = %p\n", &b);
    printf("数字常量&c = %p\n", &c);
    printf("数字常量c = %d\n", c);

    printf("全局变量&p1 = %p\n", &p1);
    printf("全局变量p1 = %p\n", p1);
    printf("栈&p2 = %p\n", &p2);
    printf("p2 = %p\n", p2);
    printf("栈s = %p\n", s);
    printf("文字常量区&p3 = %p\n", &p3);
    printf("文字常量区p3 = %p\n", p3);


    printf("程序代码&test0 = %p\n", test0);
    printf("程序代码&test0 = %p\n", &test0);

    return 0;
}

int main(void)
{
    test0();
    cout << endl;
    // test0();
    // cout << endl;
    // test0();
    return 0;
}

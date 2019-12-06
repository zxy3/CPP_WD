//判断是大端模式还是小端模式

#include <iostream>
#include <string>
#include <stdio.h>
union test {
    int a;
    char b;
};

int main(void)
{
    union test t1;
    t1.a = 1;
    if (t1.b == 1)
    {
        printf("小端模式\n");
    }
    else
    {
        printf("大端模式\n");
    }
    return 0;
}
#include <stdio.h>

//C++语言支持函数重载
//实现原理: 名字改编(name mangling)
//具体的操作步骤: 当函数名称相同时，会根据函数参数的类型，个数，顺序进行改编
int add(int x, int y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}

float add(float x, float y)
{
    return x + y;
}

int add(int x, float y)
{
    return x + y;
}

int add(float x, int y)
{
    return x + y;
}

int main(void)
{
    int a = 3, b = 4;
    float c = 1.2,d = 2.3;
    printf("add(a, b) = %d\n", add(a, b));
    printf("add(a, c) = %d\n", add(a, c));
    printf("add(c, a) = %d\n", add(c, a));
    printf("add(c, d) = %f\n", add(c, d));
    return 0;
}

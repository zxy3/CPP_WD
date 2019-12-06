#include <stdio.h>

//C++语言支持函数重载
//实现原理: 名字改编(name mangling)
//具体的操作步骤: 当函数名称相同时，会根据函数参数的类型，个数，顺序进行改编

//进行名字改编: 用C++的方式进行调用
//
//不进行名字改编: 用C的方式进行调用

//C++为了兼容C
//实现了C和C++的混合编程
#ifdef __cplusplus
extern "C"
{
#endif
    int add(int x, int y)
    {
        return x + y;
    }

#ifdef __cplusplus
} //end of extern "C"
#endif

int add(int x, int y, int z)
{
    return x + y + z;
}

#if 0
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

#endif
// 编码使用gcc
int main(void)
{
    int a = 3, b = 4, c = 5;
    printf("add(a, b, c) = %d\n", add(a, b, c));
    return 0;
}

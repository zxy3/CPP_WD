#include <stdio.h> //C头文件要放在C++头文件的上面
// 再去系统路径进行查找
#include <iostream> //C++的头文件不带.h的后缀，大部分头文件都是用模板实现的

using namespace std; //命名空间

//int wd_module_display();

int main(int argc, char **argv)
{
    printf("hello,world!\n");
    cout << "hello,world!" << endl; //cout是一个对象运算符重载
    //operator<<(operator<<(cout, "hello,world"), endl);
    return 0;
}

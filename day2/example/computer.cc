#include <iostream>
#include <cstring>
using namespace std;

class computer
{
private:
    char brand[20];
    float price;

public:
    //在类定义的同时实现了3个成员函数
    void print()
    {
        cout << "品牌：" << brand << endl;
        cout << "价格：" << price << endl;
    }

    void SetBrand(char *sz)
    {
        strcpy(brand, sz); //字符串复制
    }

    void SetPrice(float pr)
    {
        price = pr;
    }
};

// #include "example802.h" //包含了computer类的定义
int main()
{
    computer com1;       //声明创建一个类对象
    com1.SetPrice(5000); //调用public成员函数SetPrice设置price
    char *p = (char *)"Lenovo";
    com1.SetBrand(p); //调用public成员函数SetBrand设置Brand
    com1.print();     //调用print()函数输出信息
    return 0;
}

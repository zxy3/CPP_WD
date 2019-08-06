///模板的定义
#include <iostream>
#include <string>
using namespace std;

template <typename T>
T add(const T &a, const T &b)
{
    return a + b;
}

int main()
{
    cout << add(10, 20) << endl;   //调用add(const int,const int)
    cout << add(1.0, 2.0) << endl; //调用add(const double,const double)
    string x("Hello,"), y("world");
    cout << add(x, y) << endl; //调用add(string,string)

    return 0;
}





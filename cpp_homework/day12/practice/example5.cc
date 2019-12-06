#include <iostream>
#include <string>
using namespace std;
//带非类型参数,必须是整形才可以
template <typename T, int data>
T fun(T a)
{
    cout << "a --------------" << a << endl;
    cout << "data --------------" << data << endl;
    return a + data;
}

int main(void)
{
    cout << fun<int, 4>(3) << endl;
    cout << fun<double, 3>(3) << endl;
    // cout << fun<string, "world">("world") << endl;
    string a = "hello,";
    string b = "world";
    int index = 123;
    cout << a + b << endl;
}

#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

// string类
class String
{
private:
    char *_pstr;

public:
    // 构造函数3个
    String()
        : _pstr(new char[1]())
    {
        cout << "string()" << endl;
    }
    // 字符指针创建对象
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1])
    {
        // 开辟空间,深拷贝
        strcpy(_pstr, pstr);
        cout << "string(const char *)" << endl;
    }
    // 通过对象创建
    String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        // 开辟空间，深拷贝
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String &rhs)" << endl;
    }
    // 重载赋值运算符函数
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &rhs)" << endl;
        if (this != &rhs)
        {
            delete[] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }
    ~String()
    {
        cout << " ~String()" << endl;
        if (_pstr)
        {
            delete[] _pstr;
        }
    }
    // 友元重载
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
};

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    os << rhs._pstr;
    return os;
}

// String str("hello,world");
// 移动构造函数
String getString()
{
    String str("getString()");
    cout << "str = " << endl;
    return str;
}
// test0
int test0(void)
{
    vector<String> strs;
    strs.push_back("123");
    cout << strs[0] << endl;

    String s1 = "hello";
    s1 = String("world");

    String s2 = "shenzhen";
    cout << "S2 = " << s2 << endl;
    // 将左值转换为右值
    s1 = std::move(s2);
    cout << s1 << "   " << s2 << endl;
    cout << "---------------" << endl;

    s1 = move(s1);

    return 0;
}

void test1()
{
    getString();
}

// 右值引用是一个右值
String &&func()
{
    String str("hello");
    return move(str);
}
// test2
void test2()
{
    int num1 = 1;
    int num2 = 2;
    cout << "num1 = " << num1 << endl
         << "num2 = " << num2 << endl;

    //  move强制转换
    num2 = move(num1);
    cout << "num1 = " << num1 << endl
         << "num2 = " << num2 << endl;
}

// test
int main(void)
{
    test2();
    return 0;
}
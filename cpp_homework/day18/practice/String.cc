///String
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class String
{
public:
    // 构造函数1
    String() = default;
    // 构造函数2
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
        // cout << "String(const char* pstr)" << endl;
    }
    // 构造函数3
    String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
        // cout << "String(const String &rhs)" << endl;
    }
#if 1
    // 移动构造函数--用右值创建对象(传过来的就是一个指针)
    String(String &&rhs)
        : _pstr(rhs._pstr)
    {
        rhs._pstr = nullptr;
        cout << "--------------String(String && rhs)" << endl;
    }
#endif
    //析构函数
    ~String()
    {
        if (_pstr)
        {
            delete[] _pstr;
            // cout << "~String()" << endl;
        }
    }
    //-----------------成员函数---------------------
    // 移动赋值函数
    String &operator=(String &&rhs)
    {
        // cout << "String &operator=(String &&rhs)" << endl;
        if (this != &rhs)
        {
            delete[] _pstr;
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }
    // 下标运算符函数
    char &operator[](int idx)
    {
        if (idx >= 0 || idx < strlen(_pstr))
        {
            return _pstr[idx];
        }
        else
        {
            cout << "下标越界！" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    // print
    void print(void) const
    {
        if (_pstr)
        {
            cout << _pstr << endl;
        }
    }
    // size
    int size(void) const
    {
        return strlen(_pstr);
    }
    // friend
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);

private:
    char *_pstr = nullptr;

protected:
};
// 友元函数外部实现
std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    os << rhs._pstr;
    return os;
}
// test
int test0(void)
{
    vector<String> vec;
    // 临时对象：右值
    vec.push_back("hello,word!");
    vec.push_back("123");
    // 左值
    String str = "456";
    vec[0].print();
    vec[1].print();
    vec.push_back(str);
    vec[2].print();
    return 0;
}
// test1
int test1(void)
{
    // 左值
    String s1 = "左值s1";
    cout << "---左值 s1---> " << s1 << endl;
    String s2("左值s2");
    //把S1移动到S2,此时S1是空.括号中是待移动对象
    s2 = std::move(s1);
    cout << "--- s2 ---> " << s2 << endl;
    // cout << "--- s1 --->" << s1 << endl;
    // move 可以看做是临时S2移动到一个临时对象中
    vector<String> vec;
    vec.push_back(std::move(s2));
    cout << "--- vec.push_back(std::move(s2)) ---> ";
    vec[0].print();
}
// test2
//s是局部对象,马上就要被销毁 ,类中定义了具有移动语义函数,
//函数返回值是对象,此时return会调用移动构造函数, 不会调用复制构造函数
String getString()
{
    String s("临时对象");
    return s;
}
// test2
int test2(void)
{
    // 此时拿到了销毁前的临时对象
    cout << "移动语义构造函数 ---> " << getString() << endl;
    return 0;
}
// main
int main(void)
{
    // test0();
    // test1();
    test2();
    return 0;
}
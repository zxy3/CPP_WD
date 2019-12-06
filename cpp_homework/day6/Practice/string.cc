#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String
{
public:
    // 无传参构造函数
    String() = default;
    // 构造函数
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
    }
    String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }
    // 析构函数
    ~String()
    {
        if (_pstr)
        {
            delete[] _pstr;
        }
        cout << "~String()" << endl;
    }
    // 打印字符串
    void print()
    {
        cout << _pstr << endl;
    }
    // srting类的其他运算符的重载--成员函数
    String &operator=(const String &str)
    {
        // _pstr = new char[strlen(str._pstr) + 1]();
        // strcpy(_pstr, str._pstr);
        *this = str;
        return *this;
    }
    String &operator=(const char *str)
    {
        *this = (String)str;
        return *this;
    }
    String &operator+=(const String &str)
    {
        _pstr = new char[str.size() + str.size() + 1]();
        strcpy(_pstr, str._pstr);
        strcat(_pstr, str._pstr);
        return *this;
    }
    String &operator+=(const char *str)
    {
        _pstr = new char[strlen(str) * 2 + 1]();
        strcpy(_pstr, str);
        strcat(_pstr, str);
        return *this;
    }
    char &operator[](std::size_t index)
    {
        return _pstr[index];
    }
    const char &operator[](std::size_t index) const
    {
        return _pstr[index];
    }
    std::size_t size() const
    {
        return strlen(_pstr);
    }
    const char *c_str() const
    {
        return _pstr;
    }
    // srting类的其他运算符的重载--友元函数声明
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

    char *getString() const
    {
        cout << _pstr << endl;
        return _pstr;
    }

private:
    char *_pstr;
};
//友元函数
bool operator==(const String &lhs, const String &rhs)
{
    return !strcmp(lhs._pstr, rhs._pstr);
}
bool operator!=(const String &lhs, const String &rhs)
{
    return strcmp(lhs._pstr, rhs._pstr);
}
bool operator<(const String &lhs, const String &rhs)
{
    return (lhs.size() < rhs.size()) ? 1 : 0;
}
bool operator>(const String &lhs, const String &rhs)
{
    return (lhs.size() > rhs.size()) ? 1 : 0;
}
bool operator<=(const String &lhs, const String &rhs)
{
    return (lhs.size() <= rhs.size()) ? 1 : 0;
}
bool operator>=(const String &lhs, const String &rhs)
{
    return (lhs.size() >= rhs.size()) ? 1 : 0;
}
// srting类的其他运算符的重载--普通函数（数据成员是public）
String operator+(const String &lhs, const String &rhs)
{
    char *p = new char[lhs.size() + rhs.size() + 1]();
    strcpy(p, lhs.c_str());
    p = strcat(p, rhs.c_str());
    return p;
}
String operator+(const String &lhs, const char *rhs)
{
    String tmp = (String)rhs;
    tmp = lhs + tmp;
    return tmp;
}
String operator+(const char *lhs, const String &rhs)
{
    String tmp = (String)lhs;
    tmp = rhs + tmp;
    return tmp;
}
int main(void)
{
    // 初始化几个字符串
    String str1 = "hello xiongda";
    String str1_1 = "hello";
    String str2 = "world";
    String str2_1 = "woooo";
    String str2_2 = "world";
    const char *str3_1 = "hanmeimei";
    const char *str3_2 = "xiongda";
    //[]
    cout << "[]: " << str1.c_str() << " ——> "
         << " str1[0] ——> " << str1[0] << endl;
    //+
    // String str4 = str1 + str2;
    cout << "+: " << (str1 + str2).c_str() << endl;
    // cout << "+: " << str4.c_str() << endl;
    //+=
    // str1 += str2_2;
    // cout << "+= " << str1.c_str() << endl;
    // str2 += str3_1;
    // cout << "+= " << str2.c_str() << endl;
    //==
    cout<< "==: ";
    str1 == str1_1 ? cout << str1.c_str() << " 与 " << str1_1.c_str() << " 相等 " << endl : cout << str1.c_str() << " 与 " << str1_1.c_str() << " 不等 " << endl;
    str2 == str1_1 ? cout << str2.c_str() << " 与 " << str1_1.c_str() << " 相等 " << endl : cout << str2.c_str() << " 与 " << str1_1.c_str() << " 不等 " << endl;
    str2 == str2_2 ? cout << str2.c_str() << " 与 " << str2_1.c_str() << " 相等 " << endl : cout << str2.c_str() << " 与 " << str2_1.c_str() << " 不等 " << endl;
    cout << endl;
    //!=
    cout<< "!=: ";
    str1 != str1_1 ? cout << str1.c_str() << " 与 " << str1_1.c_str() << " 不等 " << endl : cout << str1.c_str() << " 与 " << str1_1.c_str() << " 相等 " << endl;
    str2 != str1_1 ? cout << str2.c_str() << " 与 " << str1_1.c_str() << " 不等 " << endl : cout << str2.c_str() << " 与 " << str1_1.c_str() << " 相等 " << endl;
    str2 != str2_2 ? cout << str2.c_str() << " 与 " << str2_1.c_str() << " 不等 " << endl : cout << str2.c_str() << " 与 " << str2_1.c_str() << " 相等 " << endl;
    cout << endl;
    //>
    cout<< ">: ";
    str1 > str1_1 ? cout << str1.c_str() << " > " << str1_1.c_str() << endl : cout << str1.c_str() << " < " << str1_1.c_str() << endl;
    str2 > str1_1 ? cout << str2.c_str() << " > " << str1_1.c_str() << endl : cout << str2.c_str() << " < " << str1_1.c_str() << endl;
    str2 > str2_1 ? cout << str2.c_str() << " > " << str2_1.c_str() << endl : cout << str2.c_str() << " < " << str2_1.c_str() << endl;
    cout << endl;
    //<
    cout<< "<: ";
    str1 < str1_1 ? cout << str1.c_str() << " < " << str1_1.c_str() << endl : cout << str1.c_str() << " > " << str1_1.c_str() << endl;
    str2 < str1_1 ? cout << str2.c_str() << " < " << str1_1.c_str() << endl : cout << str2.c_str() << " > " << str1_1.c_str() << endl;
    str2 < str2_1 ? cout << str2.c_str() << " < " << str2_1.c_str() << endl : cout << str2.c_str() << " > " << str2_1.c_str() << endl;
    cout << endl;
    //>=
    cout<< ">=: ";
    str1 >= str1_1 ? cout << str1.c_str() << " >= " << str1_1.c_str() << endl : cout << str1.c_str() << " < " << str1_1.c_str() << endl;
    str2 >= str1_1 ? cout << str2.c_str() << " >= " << str1_1.c_str() << endl : cout << str2.c_str() << " < " << str1_1.c_str() << endl;
    str2_2 >= str2_1 ? cout << str2.c_str() << " >= " << str2_1.c_str() << endl : cout << str2.c_str() << " < " << str2_1.c_str() << endl;
    cout << endl;
    //<=
    cout<< "<=: ";
    str1 <= str1_1 ? cout << str1.c_str() << " <= " << str1_1.c_str() << endl : cout << str1.c_str() << " > " << str1_1.c_str() << endl;
    str2 <= str1_1 ? cout << str2.c_str() << " <= " << str1_1.c_str() << endl : cout << str2.c_str() << " > " << str1_1.c_str() << endl;
    str2_2 <= str2_1 ? cout << str2.c_str() << " <= " << str2_1.c_str() << endl : cout << str2.c_str() << " > " << str2_1.c_str() << endl;
    cout << endl;

    return 0;
}
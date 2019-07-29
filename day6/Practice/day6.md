Day7_张晓云（插件没安装好，排版暂时有问题）
0.	什么是友元？友元的存在形式有？友元有何特点？
友元函数：
	私有成员对于类外部的所有程序部分而言都是隐藏的，访问它们需要调用一个公共成员函数，但有时也可能会需要创建该规则的一项例外。
友元函数是一个不属于类成员的函数，但它可以访问该类的私有成员。换句话说，友元函数被视为好像是该类的一个成员。友元函数可以是常规的独立函数，也可以是其他类的成员。实际上，整个类都可以声明为另一个类的友元。
为了使一个函数或类成为另一个类的友元，必须由授予它访问权限的类来声明。类保留了它们的朋友的 "名单"，只有名字出现在列表中的外部函数或类才被授予访问权限。通过将关键字 friend 放置在函数的原型之前，即可将函数声明为友元。
友元函数的一般格式如下：
friend <return type><function name> (<parameter type list>);
以上：http://c.biancheng.net/view/1489.html
友元函数的特点：
因为友元函数没有this指针，则参数要有三种情况： 1、要访问非static成员时，需要对象做参数；2、要访问static成员或全局变量时，则不需要对象做参数；3、如果做参数的对象是全局对象，则不需要对象做参数.可以直接调用友元函数，不需要通过对象或指针
以上：https://www.runoob.com/cplusplus/cpp-friend-functions.html
友元的存在形式：
友元提供了一种 普通函数或者类成员函数 访问另一个类中的私有或保护成员 的机制。也就是说有两种形式的友元：
（1）友元函数：普通函数对一个访问某个类中的私有或保护成员。
（2）友元类：类A中的成员函数访问类B中的私有或保护成员。
以上：https://blog.csdn.net/weixin_42672977/article/details/90381374

1. 运算符重载的原则是什么？有哪些规则？
运算符重载的规则如下：
1、C++中的运算符除了少数几个之外，全部可以重载，而且只能重载C++中已经有的运算符。
2、重载之后运算符的优先级和结合性都不会改变 
3、运算符重载是针对新类型数据的实际需要，对原有运算符进行适当的改造，一般来讲，重载的功能应当与原有功能相类似，不能改变原运算符的操作对象个数，同时至少要有一个操作对象是自定义类型。
4、  运算符的重载形式有两种，重载为类的成员函数和重载为类的友元函数。
•	运算符重载为类的成员函数的一般语法形式为： 
函数类型  operator 运算符（形参表）
{
    		 函数体
}
•	运算符重载为类的友元函数，可以在类中声明友元函数的原型，在类外实现，也可以在类体中实现
以上：https://www.cnblogs.com/haoyuanyuan/p/3323154.html
2. 不能重载的运算符有哪几个？
不能重载的运算符只有5个（带点的都不行），它们是：
①类属关系运算符“.”
②成员指针运算符“.*”
③作用域分辨符“::”
④sizeof运算符和三木运算符“?:”
前面两个运算符保证了C++中访问成员功能的含义不被改变。作用域分辨符和sizeof运算符的操作数是类型。
以上：同上
3. 运算符重载的形式有哪几种？
运算符重载的方式分为下面3种：
①采用普通函数的重载形式：
普通函数形式重载运算符，要求待操作的属性必须是public类型的。
②采用友元函数的重载形式: 
用成员函数重载双目运算符时，左操作数无须用参数输入，而是通过隐含的this指针传入，这种做法的效率比较高
此外，操作符还可重载为友元函数形式，这将没有隐含的参数this指针。对双目运算符，友元函数有2个参数，对单目运算符，友元函数有一个参数。
重载为友元函数的运算符重载函数的声明格式为：
friend 返回类型operator 运算符 (参数表);
③采用成员函数的重载形式: 
成员函数形式的运算符声明和实现与成员函数类似，首先应当在类定义中声明该运算符，声明的具体形式为：
返回类型  operator 运算符（参数列表）;
既可以在类定义的同时定义运算符函数使其成为inline型，也可以在类定义之外定义运算符函数，但要使用作用域限定符“::”，类外定义的基本格式为：
返回类型  类名::operator 运算符（参数列表）
{
…
}           

4. 自增运算符的前置形式和后置形式有什么区别?返回值类型分别是什么？
前置形式：直接将类成员+1，然后返回引用，属于直接修改类中的成员。
后置形式：后置，使用了复制，所以先用tmp，再增加1，最后返回的是一个函数对象。
5. 实现String类的其它运算符的重载
①	

class String {
public:
	String();
	String(const char *);
	String(const String&);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);

	String &operator+=(const String &);
	String &operator+=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;

	std::size_t size() const;
	const char* c_str() const;

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);

private:
	char * _pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
```






源码：
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

 
 

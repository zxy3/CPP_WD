///写时复制
#include <string.h>
#include <iostream>
using namespace std;
class StringCow
{
public:
    // 构造函数1
    StringCow()
        // 开辟空间 计算方法？
        : _pstr(new char[1 + 4]() + 4)
    {
        cout << "无参构造函数StringCow()" << endl;
    }
    // 构造函数2
    StringCow(const char *pstr)
        // 开辟空间
        : _pstr(new char[1 + 4]() + 4)
    {
        cout << "const char * 构造函数 pstr_ StringCow()" << endl;
    }
    // 构造函数3
    StringCow(const StringCow &rhs)
        // 浅拷贝
        : _pstr(rhs._pstr)
    {
        cout << "StringCow对象构造函数 StringCow()" << endl;
        increaseRefcount();
    }
    // 析构函数
    ~StringCow()
    {
        release();
    }
    // 成员函数
    // 重载=
    StringCow &operator=(const StringCow &rhs)
    {
        cout << "StringCow & operator=(const StringCow &)" << endl;
        if (this != &rhs)
        {
            release();
            _pstr = rhs._pstr;
            increaseRefcount();
        }
        return *this;
    }
    // 返回只读的字符串
    const char *c_str() const
    {
        return _pstr;
    }
    // 返回字符串长度
    int size() const
    {
        return strlen(_pstr);
    }
    // 返回位置
    int refcount() const
    {
        return *(int *)(_pstr - 4);
    }
    // 重载下标运算符
    char &operator[](int idx);

#if 1
    // 只读的下标访问运算符
    const char &operator[](int idx) const
    {
        cout << "const char & operator[](int idx) const" << endl;
        return _pstr[idx];
    }
#endif

    // 友元重载<<
    friend std::ostream &operator<<(std::ostream &os, const StringCow &rhs);

private:
    void initRefcount()
    {
        *(int *)(_pstr - 4) = 1;
    }
    void increaseRefcount()
    {
        ++*(int *)(_pstr - 4);
    }

    void decreaseRefcount()
    {
        --*(int *)(_pstr - 4);
    }

    void release()
    {
        decreaseRefcount();
        if (0 == refcount())
        {
            delete[](_pstr - 4);
            cout << ">> delete heap data!" << endl;
        }
    }

private:
    // 对象成员
    char *_pstr;
};

std::ostream &operator<<(std::ostream &os, const StringCow &rhs)
{
    os << rhs._pstr;
    return os;
}

//只要字符串的引用计数大于1， 就会进行深拷贝
//
//问题：下标访问运算符无法区分出接下来的操作是读操作还是写操作
//
char &StringCow::operator[](int idx)
{
    if (idx >= 0 && idx < size())
    {
        if (refcount() > 1)
        {
            decreaseRefcount();

            char *ptmp = new char[size() + 5]() + 4;
            strcpy(ptmp, _pstr);
            _pstr = ptmp;
            initRefcount();
        }
        return _pstr[idx];
    }
    else
    {
        static char nullchar = '\0';
        return nullchar;
    }
}

void func(const StringCow &str)
{
    cout << str[0] << endl;
}

// 测试代码
int main(void)
{

    StringCow s1 = "hello,world";
    StringCow s2 = s1;
    StringCow s3 = "shenzhen";
    cout << "s3 = " << s3 << endl;
    s3 = s1;

    cout << "执行赋值操作之后:" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    cout << "\n 修改共享字符串的内容之后:" << endl;
    s3[0] = 'X';
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    cout << "\n 执行读操作之后:" << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    printf("s3's address is %p\n", s3.c_str());
    cout << "s1's refcount = " << s1.refcount() << endl;
    cout << "s2's refcount = " << s2.refcount() << endl;
    cout << "s3's refcount = " << s3.refcount() << endl;

    return 0;
}
#include <iostream>
#include <string.h>
using namespace std;
class CowString
{ //23种设计模式之代理理模式
    class charProxy;

public:
    CowString() : _pstr(new char[2])
    {
        cout << "CowString()" << endl;
        initRefcount();
    }
    CowString(const char *);
    CowString(const CowString &);
    CowString &operator=(const CowString &);
    ~CowString()
    {
        cout << "~CowString()" << endl;
        decreaseRefcount();
        if (0 == useCount())
        {
            delete[] _pstr;
        }
    }
    const char *c_str() const
    {
        return _pstr;
    }
    int useCount()
    {
        return _pstr[strlen(_pstr) + 1];
    }

    //区分写操作，这⾥里里要返回⼀一个临时对象就不不能是⼀一个引⽤用了了
    charProxy operator[](int index);

private:
    char *_pstr;
    void initRefcount()
    {
        _pstr[strlen(_pstr) + 1] = 1;
    }
    void increaseRefcount()
    {
        ++_pstr[strlen(_pstr) + 1];
    }
    void decreaseRefcount()
    {
        --_pstr[strlen(_pstr) + 1];
    }
    class charProxy
    {
    public:
        //这些函数⼀一定要是公有
        charProxy(CowString &str, int index) : _str(str), _index(index)
        {
            cout << "charProxy(CowString&,int)" << endl;
        }
        //嵌套类⾥里里⾯面，也不不能返回对象引⽤用;因为嵌套类对象都是临时的
        char &operator=(char ch);
        operator char()
        { 
            //类型转换函数，由Charproxy转向char
            cout << "operator char()" << endl;
            return _str._pstr[_index];
        }

    private:
        CowString &_str;
        int _index;
    };
    friend ostream &operator<<(ostream &, const CowString &);
    friend istream &operator>>(istream &, CowString &);
};
#if 0
//operator[]()不不能区分读操作还是写操作
char & CowString::operator[](int idx)const //不不能区分读写操作，废弃
{
cout<<"operator [](int)const"<<endl;
return _pstr[idx];
}
#endif
CowString::CowString(const char *tmp)
{
    cout << "CowString(const char*)" << endl;
    _pstr = new char[strlen(tmp) + 2];
    strcpy(_pstr, tmp);
    initRefcount(); //引⽤用计数设置为1
}
CowString::CowString(const CowString &lhs)
{
    cout << "CowString(const CowString&)" << endl;
    _pstr = lhs._pstr;
    increaseRefcount();
}
CowString &CowString::operator=(const CowString &lhs)
{
    cout << "CowString& operator=(const CowString&)" << endl;
    decreaseRefcount();
    if (0 == useCount())
    {
        delete[] _pstr;
    }
    _pstr = lhs._pstr; // 浅拷⻉
    increaseRefcount();
    return *this;
}
ostream &operator<<(ostream &os, const CowString &rhs)
{
    cout << "ostream& operator<<(ostream& os,const CowString&)" << endl;
    os << rhs._pstr << endl;
    return os;
}
istream &operator>>(istream &is, CowString &s)
{
    cout << "istream& operator>>(istream&,CowString&)" << endl;
    is >> s._pstr;
    return is;
}
CowString::charProxy CowString::operator[](int index)
{
    cout << "charProxy operator[](int)" << endl;
    return charProxy(*this, index); //返回临时嵌套类对象
}
char &CowString::charProxy::operator=(char ch)
{
    cout << "char& operator=(char)" << endl;
    if (_index >= 0 && _index < strlen(_str._pstr))
    {
        if (1 == _str.useCount()) //当对象没有共享内存时
        {
            _str._pstr[_index] = ch; //修改
            return _str._pstr[_index];
        }
        else
        {
            _str.decreaseRefcount(); //有共享内存
            char *_strtmp = new char[strlen(_str._pstr) + 2];
            strcpy(_strtmp, _str._pstr);
            _str = _strtmp;    //这⾥里里调⽤用了了构造函数和赋值构造函数,操作完之后调⽤用析构函数
            _str[_index] = ch; //这⾥里里再次调动[]重载函数,进⾏行行修改
            _str.initRefcount();
            return _str._pstr[_index];
        }
    }
}
int main()
{
    CowString s1("hello,world");
    CowString s2(s1);
    cout << "读操作： " << s1[1] << endl;
    cout << s1.useCount() << endl;
    cout << "--------------------------" << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    cout << "写操作： " << endl;
    s1[1] = 'm';
    cout << "--------------------------" << endl;
    cout << s1[1] << endl;
    cout << s1.useCount() << endl;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("s1's address is %p\n", s1.c_str());
    printf("s2's address is %p\n", s2.c_str());
    return 0;
}
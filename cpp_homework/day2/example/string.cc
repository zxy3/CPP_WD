#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
    // 无传参构造函数
    String() = default;
    // 构造函数重载
    String(const char *pstr)
        : _pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);
        cout << "String(const char *pstr)" << endl;
    }
    String(const String &rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const char *pstr)" << endl;
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
    #if 0
    String & operator=(const String & rhs)
	{
		_pstr = rhs._pstr;
		cout << "String & operator=(const String & rhs)" << endl;
		return *this;
	}
    #endif
    // 赋值函数
    String & operator=(const String & rhs)
	{
		if(this != &rhs) {//自复制
			cout << "String & operator=(const String & rhs)" << endl;
			delete [] _pstr;//回收左操作申请的空间

			//再进行深拷贝
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
			_pstr = rhs._pstr;
		}
		return *this;
	}

private:
    char *_pstr = (char *)"default";
};

int main(void)
{
    String str1;
    str1.print();

    String str2 = "Hello,world";
    str2.print();

    String str3("wangdao");
    str3.print();

    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();

    return 0;
}

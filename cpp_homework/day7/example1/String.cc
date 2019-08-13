 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-24 09:40:00
 ///
 

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class String
{
public:
	String()
	: _pstr(nullptr)
	{
		cout << "String()" << endl;
	}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
		cout << "String(const char * pstr)" << endl;
	}

	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(constb String &)" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String&)" << endl;
		if(this != & rhs) {
			delete [] _pstr;

			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	char & operator[](int idx)
	{
		if(idx >= 0 || idx < strlen(_pstr)) {
			return _pstr[idx];
		} else {
			cout << " idx 越界!" << endl;
			static char nullchar = '\0';
			return nullchar;
		}
	}

	void print() const
	{
		if(_pstr)
			cout << _pstr << endl;
	}

	~String()
	{
		if(_pstr)
			delete [] _pstr;
		cout << "~String()" << endl;
	}

	int	size()const 
	{	return strlen(_pstr);}

private:
	char * _pstr;
};
 
int main(void)
{
	String s1;
	s1.print();

	String s2 = "hello";
	cout << "s2 = ";
	s2.print();

	String s3 = s2;
	cout << "s3 = ";
	s3.print();

	String s4 = "world";
	s4 = s2;
	cout << "s4 = ";
	s4.print();

#if 0
	cout << "1111" << endl;
	int * p = nullptr;

	cout << "p = " << p << endl;
	cout << "222" << endl;
#endif

	cout << "下标访问运算符" << endl;
	for(int idx = 0; idx != s4.size(); ++idx) 
	{
		cout << s4[idx] << endl;
	}

	return 0;
}

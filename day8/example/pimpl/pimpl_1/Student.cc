#include "Student.h"
#include <iostream>
using std::cout;
using std::endl;

class Student::StudentImpl //StudentImpl共享Student类的所有成员
{
	class Subject //内部类Subject只为Student进行服务,完成Student类的初始化
	{
	public:Subject
		(int chinese = 0, int math = 0, int english = 0)
			: _chinese(chinese), _math(math), _english(english)
		{
			cout << "1|Subject(int,int,int)" << endl;
		}

		void print() const
		{
			cout << "chinese --> " << _chinese << endl;
			cout << "math --> " << _math << endl;
			cout << "english --> " << _english << endl;
		}

		~Subject() { cout << "~Subject()" << endl; }

	private:
		// 暂且认为成绩都是整数
		int _chinese;
		int _math;
		int _english;
	};
	// StudentImpl类初始化，随便写
public:
	// 构造函数
	StudentImpl(int ch, int ma, int en)
		: _sub1(ch, ma, en)
	{
		cout << "2|StudentImpl(int,int,int,int)" << endl;
	}
	// 析构函数
	~StudentImpl() { cout << "~StudentImpl()" << endl; }
	// 成员函数
	void printMessage() const;

private:
	Subject _sub1;
	Subject _sub2;
};

// Student.h
Student::Student(int x1, int y1, int x2)
	: _pimpl(new StudentImpl(x1, y1, x2))
{
	cout << "Student(...)" << endl;
}

Student::~Student()
{
	if (_pimpl)
		delete _pimpl;
	cout << "~Student()" << endl;
}

void Student::printMessage() const
{
	_pimpl->printMessage();
}

void Student::StudentImpl::printMessage() const
{
	_sub1.print();
}

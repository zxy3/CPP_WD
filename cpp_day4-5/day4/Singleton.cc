#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
using std::cout;
using std::endl;


//要求: 定义一个类，只能由该类创建唯一的一个对象
//1. 该对象不能是栈（全局）对象
//2. 只能将该对象放在堆上
//应用场景:
//1. 可以用单例模式替换掉全局变量
//2. 配置文件中的存储都是程序的输入信息
//3. 词典库，网页库

class Singleton
{
public:
	static Singleton * getInstance() //创建堆空间对象
	{
		//只有第一个创建时候可以被创建，之后再创建都只返回这个指针
		if(nullptr == _pInstance) { 
			_pInstance = new Singleton();
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
			delete _pInstance;
	}
	void warn(const char * msg);
	void error(const char * msg);
	void debug(const char * msg);
	void info(const char * msg);

private:
	Singleton() {	cout << "Singleton()" << endl;	} //构造函数私有化
	~Singleton(){	cout << "~Singleton()" << endl;	} //析构函数私有化

private:
	//Point _pt;
	//Computer _pc;

	static Singleton * _pInstance;
};

Singleton * Singleton::_pInstance = nullptr;
 
int main(void)
{

	//Singleton * p1 = new Singleton();
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();
	Singleton * p3 = Singleton::getInstance();
	cout << "p1 = " << p1 << endl
		 << "p2 = " << p2 << endl
		 << "p3 = " << p3 << endl;

	//delete p1;//error
	Singleton::destroy();

	return 0;
}

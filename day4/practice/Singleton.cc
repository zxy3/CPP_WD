#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;


class LogSingleton
{
public:
	static LogSingleton *getInstance() //创建堆空间对象
	{
		//只有第一个创建时候可以被创建，之后再创建都只返回这个指针
		if (nullptr == _logsingleton)
		{
			_logsingleton = new LogSingleton();
		}
		return _logsingleton;
	}

	static void destroy()
	{
		if (_logsingleton)
			delete _logsingleton;
	}

	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);

private:
	LogSingleton()
		: root(Category::getRoot().getInstance("zxy"))
	{
		cout << "LogSingleton()" << endl;
		PatternLayout *ptnLayout = new PatternLayout();
		ptnLayout->setConversionPattern("[time:%d]: [%p] [NDC:%u] [by:%c] %x: [message %m]%n");
		OstreamAppender *ostreamAppender = new OstreamAppender("ostreamAppender", &cout);
		ostreamAppender->setLayout(ptnLayout);
		// 回卷文件
		RollingFileAppender *rollingFileAppender = new RollingFileAppender("rollingfileAppender",
																		   "r123.log",
																		   2 * 1024,
																		   5);
		// 输出到回卷文件中
		rollingFileAppender->setLayout(ptnLayout);
		// 成员初始化
		root.setAppender(ostreamAppender);
		root.addAppender(rollingFileAppender);
		root.setPriority(Priority::DEBUG);
	}													   //构造函数私有化
	~LogSingleton() { cout << "~LogSingleton()" << endl; } //析构函数私有化

private:
	Category &root;
	static LogSingleton *_logsingleton;
};
//类外初始化
LogSingleton *LogSingleton::_logsingleton = nullptr;

inline void LogSingleton::warn(const char *msg)
{
	root.warn(msg);
}
inline void LogSingleton::error(const char *msg)
{
	root.error(msg);
}
inline void LogSingleton::debug(const char *msg)
{
	root.debug(msg);
}
inline void LogSingleton::info(const char *msg)
{
	root.info(msg);
}

int main(void)
{
	LogSingleton *p = LogSingleton::getInstance();
	cout << "p1 = " << p << endl;
	int cnt = 50;
	while (cnt--)
	{
		p->warn("warn");
		p->debug("debug");
		p->error("error");
		p->info("info");
	}

	Category::shutdown(); //回收资源
	LogSingleton::destroy();
	return 0;
}

#ifndef __MYLOG_H__
#define __MYLOG_H__
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <iostream>
#include <string>
#include <sstream>
using std ::cout;
using std ::endl;
using namespace std;
enum definePriority
{
    ALERT,
    CRIT,
    ERROR,
    WARN,
    INFO,
    DEBUG
};
class mylog
{
public:
    static mylog *getInstance();
    static void destroy();
    void Priority(definePriority priority);
    template <typename... Args>
    void alert(Args... args);
    template <typename... Args>
    void crit(Args... args);
    template <typename... Args>
    void error(Args... args);
    template <typename... Args>
    void warn(Args... args);
    template <typename... Args>
    void info(Args... args);
    template <typename... Args>
    void debug(Args... args);

private:
    mylog(); //单例
    ~mylog();

private:
    static mylog *_plog;
    log4cpp::Category &mycategory;
};
mylog *mylog::_plog = nullptr; //初始化静态成员
mylog::mylog()
    : mycategory(log4cpp::Category::getRoot().getInstance("mycategory"))
{
    log4cpp::PatternLayout *ptnLayout1 = new log4cpp::PatternLayout();
    ptnLayout1->setConversionPattern("%d %c [%p] %m%n");
    log4cpp::PatternLayout *ptnLayout2 = new log4cpp::PatternLayout();
    ptnLayout2->setConversionPattern("%d %c [%p] %m%n");
    log4cpp::OstreamAppender *ostreamAppender = new log4cpp ::OstreamAppender("ostreamAppender", &cout);
    ostreamAppender->setLayout(ptnLayout1);
    log4cpp::RollingFileAppender *rollingFileAppender = new log4cpp::RollingFileAppender("rollingFileAppender", "rolling.log", 1024,
                                                                                         8);
    rollingFileAppender->setLayout(ptnLayout2);
    mycategory.setPriority(log4cpp::Priority::DEBUG);
    mycategory.addAppender(ostreamAppender);
    mycategory.addAppender(rollingFileAppender);
    mycategory.info("mylog()构造函数");
}
inline mylog::~mylog()
{
    mycategory.info("~mylog()析构函数");
    mycategory.shutdown();
}
inline mylog *mylog::getInstance() //调用构造函数
{
    if (_plog == nullptr)
    {
        _plog = new mylog();
    }
    return _plog;
}
inline void
mylog::destroy() //调用析构函数
{
    _plog->mycategory.info("destroy()");
    if (_plog)
        delete _plog;
}
inline void
mylog::Priority(definePriority priority) //修改权限
{
    switch (priority)
    {
    case ALERT:
        mycategory.setPriority(log4cpp::Priority::ALERT);
        break;
    case CRIT:
        mycategory.setPriority(log4cpp::Priority::CRIT);
        break;
    case ERROR:
        mycategory.setPriority(log4cpp::Priority::ERROR);
        break;
    case WARN:
        mycategory.setPriority(log4cpp::Priority::WARN);
        break;
    case INFO:
        mycategory.setPriority(log4cpp::Priority::INFO);
        break;
    default:
        mycategory.setPriority(log4cpp::Priority::DEBUG);
        break;
    }
}
//响应记录日志
template <typename... Args>
inline void mylog::alert(Args... args)
{
    mycategory.alert(args...);
}
template <typename... Args>
inline void
mylog::crit(Args... args)
{
    mycategory.crit(args...);
}
template <typename... Args>
inline void
mylog::error(Args... args)
{
    mycategory.error(args...);
}
template <typename... Args>
inline void
mylog::warn(Args... args)
{
    mycategory.warn(args...);
}
template <typename... Args>
inline void
mylog::info(Args... args)
{
    mycategory.info(args...);
}
template <typename... Args>
inline void
mylog::debug(Args... args)
{
    mycategory.debug(args...);
}
//行号转字符串
inline string getLineNumber(int lineNumber)
{
    ostringstream oss;
    oss << lineNumber;
    return oss.str();
}

#define makeMsg(msg) string(msg).append("
[fileName:").append(__FILE__)\
.append("
funcName:").append(__FUNCTION__)\
.append("
lineNumber:").append(getLineNumber(__LINE__))\
.append("]").c_str()

mylog *log = mylog::getInstance(); //创建对象

#define Logpriority(priority) log->Priority(priority)
#define LogDestroy() mylog::destroy()

template <typename... Args>
void LogAlert(string msg, Args... args)
{
    log->alert(makeMsg(msg), args...);
}
template <typename... Args>
void LogCrit(string msg, Args... args)
{
    log->crit(makeMsg(msg), args...);
}
template <typename... Args>
void LogError(string msg, Args... args)
{
    log->error(makeMsg(msg), args...);
}
template <typename... Args>
void LogWarn(string msg, Args... args)
{
    log->warn(makeMsg(msg), args...);
}
template <typename... Args>
void LogInfo(string msg, Args... args)
{
    log->info(makeMsg(msg), args...);
}
template <typename... Args>
void LogDebug(string msg, Args... args)
{
    log->debug(makeMsg(msg), args...);
}
#endif

int main(void)
{
    cout << "hello,world" << endl;
    int number = 100;
    const char *pstr = "hello, log4cpp";
    LogInfo("this is an info message. number = %d, str = %s ", number,
            pstr);
    LogError("Message");
    LogWarn("Message");
    LogDebug("Message");
    Logpriority(ERROR);
    LogError("Message");
    LogWarn("Message");
    LogDebug("Message");
    Logpriority(DEBUG);
    LogDestroy();
    return 0;
}

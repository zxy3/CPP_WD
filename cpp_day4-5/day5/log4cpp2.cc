///
/// @file    log4cpp2.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-06-22 11:06:42
///

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
// 输出到终端和文件
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

#include <iostream>
using std::cout;
using std::endl;

using namespace log4cpp;

int main(void)
{
	// 布局
	PatternLayout *ptnLayout = new PatternLayout();
	// 设置具体的格式
	ptnLayout->setConversionPattern("%d [%p] %m%n"); //时间 优先级 消息本身 换行
	// 日志输出的对象
	OstreamAppender *ostreamAppender = new OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(ptnLayout);

	// 输出到文件
	// 也可以另外起个名字
	Category &root = Category::getRoot(); //.getInstance("asd");
	root.setAppender(ostreamAppender);
	// 设置优先级别
	root.setPriority(Priority::DEBUG); //日志记录器的级别
	// 添加目的地
	root.alert("alert message"); //一条日志的级别
	root.crit("crit message");
	root.debug("debug message");
	root.error("error message");
	root.emerg("emerg message");
	root.info("info message");
	root.fatal("fatal message");
	root.warn("warn message");

	// 假定最多1g的空间写日志--设置日志的空间
	// 一次操作1g的空间会比较麻烦--将1g空间切割成若干文件
	// 将1G空间全部写完后需要循环滚动--将最早写的文件清空--回卷文件

	Category::shutdown(); //回收资源

	return 0;
}
// 相对顺序不可以改变 llog4cpp依赖于lpthread
// g++ log4cpp2.cc -llog4cpp -lpthread
#pragma once

#include "Thread.h"

// 头文件中只提供接口
namespace wd
{
// 为了防止循环引用，使用线程池的引用
class Threadpool;

class WorkerThread
	: public Thread
{
public:
	WorkerThread(Threadpool &threadpool);
	~WorkerThread();
	// 只需要一个run方法就可以了
	void run();

private:
	// 需要一个线程池的引用，引用的初始化，只能在初始化表达式中进行
	Threadpool &_threadpool;
};

} //end of namespace wd

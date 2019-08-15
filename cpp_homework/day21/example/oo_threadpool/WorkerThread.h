///
/// @file    WorkerThread.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 15:19:07
///

//  头文件中，只提供接口
#pragma once

#include "Thread.h"

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
	// 需要一个线程池的引用
	Threadpool &_threadpool;
};

} //end of namespace wd

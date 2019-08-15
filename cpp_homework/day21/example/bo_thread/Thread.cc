///
/// @file    Thread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 09:43:12
///

#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

void Thread::start()
{
	// 创建线程 id 属性 返回值为void*，参数也是void*的函数，真正的函数执行体，一般是空指针
	pthread_create(&_pthid, nullptr, threadfunc, this);
	// 开关设置为开，表示可以执行后面的任务了
	_isRunning = true;
}
// 函数执行体的实现，参数void* 返回值void*，run方法就要写到这里运行
void *Thread::threadfunc(void *arg)
{
	// 将arg转成thread的指针
	Thread *pthread = static_cast<Thread *>(arg);
	// 在执行具体的任务
	if (pthread)
	{
		// 调用派生类的方法
		pthread->_cb();
	}

	return nullptr;
}

void Thread::join()
{
	// 等待子线程执行结束，然后回收
	if (_isRunning)
		pthread_join(_pthid, nullptr);
}

Thread::~Thread()
{
	if (_isRunning)
		pthread_detach(_pthid);
}

} //end of namespace wd

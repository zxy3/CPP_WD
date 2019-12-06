///
/// @file    Thread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 09:43:12
///

#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;
// 基于BO的直接实现就可以了，不用继承。
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
		// 回调函数
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
	// 如果发现当前的线程存在，将线程的执行，交给系统
	if (_isRunning)
	{
		cout << "Thread::~Thread()" << endl;
	}
	// 相当于将线程释放给系统，由系统再去回收
	// 可以放打印信息,看到析构函数的一个执行
	// pthread_detach(_pthid);
}

} //end of namespace wd

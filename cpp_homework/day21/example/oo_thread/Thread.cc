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
// 相同
void Thread::start()
{
	pthread_create(&_pthid, nullptr, threadfunc, this);	
	_isRunning = true;
}

void * Thread::threadfunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
	// 派生类 函数执行体实际上要调用的方法
		pthread->run();	

	return nullptr;
}
// 相同
void Thread::join()
{
	if(_isRunning) {
		pthread_join(_pthid, nullptr);
		_isRunning = false;
	}
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);
	}
}

}//end of namespace wd

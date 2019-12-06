#pragma once

#include "Noncopyable.h"

#include <pthread.h>
//  面向对象的思想---->执行函数
namespace wd
{

class Thread
: Noncopyable
{
public:
	Thread()
	: _pthid(0)
	, _isRunning(false)
	{}

	void start();
	void join();

	virtual ~Thread();

private:
	virtual void run()=0;//待执行的任务
	static void * threadfunc(void * arg);

private:
	pthread_t _pthid;
	bool _isRunning;
};

}//end of namespace wd

#pragma once
// 保证头文件只被编译一次
#include "MutexLock.h"

#include <iostream>
using namespace std;

namespace wd
{

class Condition
{
public:
	// 注册一个条件变量
	Condition(MutexLock &mutex)
		: _mutex(mutex)
	{
		// 初始化一个条件变量。当参数cattr为空指针时，
		// 函数创建的是一个缺省的条件变量。
		// 否则条件变量的属性将由cattr中的属性值来决定。
		if (pthread_cond_init(&_cond, nullptr))
		{
			perror(">> pthread_cond_init");
		}
	}
	//
	~Condition()
	{
		if (pthread_cond_destroy(&_cond))
		{
			perror(">> pthread_cond_destroy");
		}
	}

	void wait()
	{
		if (pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))
		{
			perror(">> pthread_cond_wait");
		}
	}

	void notify()
	{
		if (pthread_cond_signal(&_cond))
		{
			perror(">> pthread_cond_signal");
		}
	}

	void notifyAll()
	{
		if (pthread_cond_broadcast(&_cond))
		{
			perror(">> pthread_cond_broadcast");
		}
	}

private:
	pthread_cond_t _cond;
	MutexLock &_mutex;
};

} //end of namespace wd

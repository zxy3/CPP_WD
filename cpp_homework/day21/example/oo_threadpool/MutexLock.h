#pragma once
// 保证头文件只被编译一次
#include "Noncopyable.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include <iostream>
using namespace std;

namespace wd
{

class MutexLock
	: Noncopyable
{
public:
	// 构造函数，创建锁
	MutexLock()
		: _isLocking(false)
	{
		// 如果没有加锁的时候先注册一个锁
		if (pthread_mutex_init(&_mutex, nullptr))
		{
			perror(">> pthread_mutex_init");
		}
	}
	// 析构函数，删除锁
	~MutexLock()
	{
		if (pthread_mutex_destroy(&_mutex))
		{
			perror(">> pthread_mutex_destroy");
		}
	}
	// lock 加锁
	void lock()
	{
		if (pthread_mutex_lock(&_mutex))
		{
			perror(">> pthread_mutex_lock");
		}
		// 开关写成true
		_isLocking = true;
	}
	// unlock 关锁，开关置为false
	void unlock()
	{
		if (pthread_mutex_unlock(&_mutex))
		{
			perror(">> pthread_mutex_unlock");
		}
		_isLocking = false;
	}
	// 判断锁状态
	bool isLocking() const
	{
		return _isLocking;
	}
	// ？？
	pthread_mutex_t *getMutexLockPtr()
	{
		return &_mutex;
	}

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};
// ？？？
class MutexLockGuard
{
public:
	// 加锁
	MutexLockGuard(MutexLock &mutex)
		: _mutex(mutex)
	{
		_mutex.lock();
	}
	// 解锁
	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	MutexLock &_mutex;
};

} //end of namespace wd

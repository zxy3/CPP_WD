#pragma once
// 保证头文件只被编译一次
#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{
// 防止多次复制
class Thread
	: Noncopyable
{
public:
	// 构造函数
	Thread()
		: _pthid(0), _isRunning(false)
	{
	}
	// 析构函数
	virtual ~Thread();

	// 创建线程
	void start();
	// 回收线程
	void join();

private:
	// 防止被其他类调用
	virtual void run() = 0;
	//待执行的任务 函数的执行体，为了配合pthread_create接口传参（面向接口编程）
	static void *threadfunc(void *arg);

private:
	// 线程id
	pthread_t _pthid;
	// 线程开关
	bool _isRunning;
};

} //end of namespace wd

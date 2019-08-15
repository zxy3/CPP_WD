///
/// @file    Thread.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 09:40:52
///

#pragma once
// 继承Noncopyable 保证线程不可被复制
#include "Noncopyable.h"

#include <pthread.h>
// 用到了function接口
#include <functional>
using std::function;
// 基于对象的思想  没有继承，没有虚函数，直接实现
namespace wd
{

//具体类
class Thread
	: Noncopyable
{
public:
	// 代表的就是func
	using ThreadCallback = function<void()>;
	// cb 是一个回调函数
	// 构造函数 将cb用右值引用的方式传递进来
	Thread(ThreadCallback &&cb)
		: _pthid(0), _isRunning(false), _cb(std::move(cb))
	{
	}
	// 成员函数
	void start();
	void join();
	// 析构函数
	~Thread();

private:
	// 否则含有一个隐含的this指针，设置为静态不会多出一个参数
	// 跟OO相同
	static void *threadfunc(void *arg);

private:
	pthread_t _pthid;
	bool _isRunning;
	// func 回调函数
	ThreadCallback _cb;
};

} //end of namespace wd

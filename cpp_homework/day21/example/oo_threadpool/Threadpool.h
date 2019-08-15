#pragma once

#include "TaskQueue.h"

#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;
// 提供线程池的接口
namespace wd
{

class Task;
class Thread;

class Threadpool
{
	// 设计为友元
	friend class WorkerThread;

public:
	Threadpool(size_t threadNum = 4, size_t queSize = 10);
	~Threadpool();
	// 成员函数
	void start();
	// task是一个虚函数，只要添加指针即可
	void addTask(Task *task);
	void stop();

private:
	//
	Task *getTask();
	// 包工头 每个子线程要执行的任务
	void threadfunc();

private:
	// 线程数量
	size_t _threadNum;

	size_t _queSize;
	// 存在线程对象
	vector<unique_ptr<Thread>> _threads;
	//
	TaskQueue _taskque;
	// 什么时候退出的标志
	bool _isExit;
};

} //end of namespace wd

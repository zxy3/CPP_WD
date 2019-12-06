#pragma once

#include "TaskQueue.h"

#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;

namespace wd
{

class Thread;

class Threadpool
{
	friend class WorkerThread;

public:
	// 线程池的构造函数
	Threadpool(size_t threadNum = 4, size_t queSize = 10);
	~Threadpool();

	void start();
	//
	void addTask(Task &&task);

	void stop();

private:
	Task getTask();
	// 把每个回调函数注册给每个子线程
	void threadfunc();

private:
	size_t _threadNum;
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskque;
	bool _isExit;
};

} //end of namespace wd

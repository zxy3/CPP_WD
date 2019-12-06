#pragma once
// 保证头文件只被编译一次的一个标注
#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"

#include <queue>
using namespace std;

namespace wd
{

using ElemType = Task *;
// 任务队列
class TaskQueue
{
public:
	TaskQueue(size_t queSize = 10);

	bool empty() const;
	bool full() const;
	// 放任务
	void push(ElemType &elem);
	// 取任务 任务类型为elemtype
	ElemType pop();
	// 等待
	void wakeup();

private:
	size_t _queSize;
	// 任务队列
	queue<ElemType> _que;
	// 互斥锁
	MutexLock _mutex;
	// 条件变量：判断是否满
	Condition _notFull;
	Condition _notEmpty;
	// 开关
	bool _flag;
};

} //end of namespace wd

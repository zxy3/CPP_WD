 ///
 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-15 11:11:24
 ///
 
#pragma once

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>
using std::queue;

namespace wd
{


using Task = std::function<void()>; 
using ElemType = Task;


class TaskQueue
{
public:
	TaskQueue(size_t queSize = 10);

	bool empty() const;
	bool full() const;
	void push(ElemType & elem);
	ElemType pop();

	void wakeup();

private:
	size_t _queSize;
	queue<ElemType> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;
};


}//end of namespace wd

 

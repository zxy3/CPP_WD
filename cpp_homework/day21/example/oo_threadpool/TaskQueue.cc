 ///
 /// @file    TaskQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-15 11:14:49
 ///
 
#include "TaskQueue.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
 
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _flag(true)
{

}

bool TaskQueue::empty() const
{
	return _que.size() == 0;
}

bool TaskQueue::full() const
{
	return _que.size() == _queSize;
}


//运行在生产者线程
void TaskQueue::push(ElemType & elem)
{
	MutexLockGuard autolock(_mutex);
	while(full()) {//使用while是为了防止出现虚假唤醒
		_notFull.wait();//异常(虚假)唤醒
	}

	_que.push(elem);

	_notEmpty.notify();

}

//运行在消费者线程
ElemType TaskQueue::pop()
{
	//RAII技术
	MutexLockGuard autolock(_mutex);
	while(_flag && empty()) {
		_notEmpty.wait();
	}

	if(_flag) {
		ElemType elem = _que.front();
		_que.pop();

		_notFull.notify();

		return elem;
	} else 
		return nullptr;
}

void TaskQueue::wakeup()
{
	_flag = false;
	_notEmpty.notifyAll();
}

}//end of namespace wd

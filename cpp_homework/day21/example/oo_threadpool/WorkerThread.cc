///
/// @file    WorkerThread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 15:21:13
///

#include "WorkerThread.h"
// 先加载头文件
#include "Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;
// 实现头文件中的2个方法
namespace wd
{
// 构造函数
WorkerThread::WorkerThread(Threadpool &threadpool)
	: _threadpool(threadpool)
{
	cout << "WorkerThread()" << endl;
}
// 析构函数
WorkerThread::~WorkerThread()
{
	cout << "~WorkerThread()" << endl;
}
// run方法
void WorkerThread::run()
{
	_threadpool.threadfunc();
}

} //end of namespace wd

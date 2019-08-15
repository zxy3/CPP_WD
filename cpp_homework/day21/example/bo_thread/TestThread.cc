///
/// @file    TestThread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 09:38:51
///

#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

// 写一点，测一点
class Mytask
{
public:
	// 覆盖run方法
	void run()
	{
		// 产生随机数
		::srand(::clock());

		int cnt = 20;
		while (cnt--)
		{
			int number = ::rand() % 100;
			// pthread_self
			cout << "sub Thread " << pthread_self()
				 << ": number = " << number << endl;
			// 休眠1秒
			::sleep(1);
		}
	}
};

void task_process(int)
{
	// 获取随机数
	::srand(::clock());

	int cnt = 20;
	while (cnt--)
	{
		int number = ::rand() % 100;
		cout << "sub Thread " << pthread_self()
			 << ": number = " << number << endl;
		::sleep(1);
	}
}

int main(void)
{
	unique_ptr<wd::Thread> thread(new wd::Thread(
		// 绑定成员函数,Mytask()对象,或者用传递指针的方式也可以
		//std::bind(&Mytask::run, Mytask())
		// 直接传递对象
		std::bind(task_process, 1)));
	// 用指针调用
	thread->start();

	thread->join();
	return 0;
}

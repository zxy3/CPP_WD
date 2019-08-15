///
/// @file    Consumer.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 11:37:24
///
#include "Consumer.h"
#include "TaskQueue.h"
// 消费数据
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

void Consumer::run()
{
	int cnt = 20;
	while (cnt--)
	{
		// 拿到一个数据
		int number = _que.pop();
		// pthread_self（）
		// 消费一个数据
		cout << "consumer thread " << pthread_self() << " cnt = " << cnt
			 << ":  consume a number = " << number << endl;
		// 休眠1秒
		::sleep(1);
	}
}
} //end of namespace wd

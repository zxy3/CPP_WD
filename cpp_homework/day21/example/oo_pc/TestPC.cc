///
/// @file    TestPC.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 09:38:51
///

#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
// 加载命名空间
using namespace wd;

int main(void)
{
	// 往当前队列放10个数据
	TaskQueue taskque(10);
	// 用智能指针进行托管
	unique_ptr<Thread> producer1(new Producer(taskque));
	unique_ptr<Thread> producer2(new Producer(taskque));
	// 使用同一个taskque
	unique_ptr<Thread> consumer1(new Consumer(taskque));
	unique_ptr<Thread> consumer2(new Consumer(taskque));
	// 生产者和消费者，都开启线程的运行
	producer1->start();
	producer2->start();
	consumer1->start();
	consumer2->start();
	// 生产者，消费者，都等待线程的结束
	producer1->join();
	producer2->join();
	consumer1->join();
	consumer2->join();

	return 0;
}

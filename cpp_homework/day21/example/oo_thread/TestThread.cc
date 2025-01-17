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

class MyThread
: public wd::Thread
{
	void run()
	{
		::srand(::clock());	

		int cnt = 20;
		while(cnt--) {
			int number = ::rand() % 100;
			cout << "sub Thread " << pthread_self() 
				 << ": number = " << number << endl;
			::sleep(1);
		}
	}
};

 
int main(void)
{
	unique_ptr<wd::Thread> thread(new MyThread());
	thread->start();

	thread->join();

	MyThread thread1;
	// MyThread thread2 = thread1;
 
	return 0;
}

#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

void display()
{
	cout << "display() " << endl;
}
 
int main(void)
{
	cout << "enter main function..." << endl;
	// 程序终止的时候触发调用
	::atexit(display);
	::atexit(display);
	cout << "exit main function..." << endl;
	return 0;
}

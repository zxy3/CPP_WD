#include <iostream>
using std::cout;
using std::endl;

//默认值的设置：
//	一旦将某一个参数设为默认值之后，其后的所有的参数都需要设置默认值
//
//	默认值得设置是按照从右到左的顺序进行
int add(int x, int y =0, int z = 0)
{
	return x + y;
}	
 
int main(void)
{
	int a = 3, b = 4;
	cout << add(a) << endl
		//  << add() << endl
		 << add(a, b) << endl;

	return 0;
}

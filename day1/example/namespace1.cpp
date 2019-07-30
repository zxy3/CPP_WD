#include <iostream>
using std::cout; // using声明机制
using std::endl;

namespace wd
{

//命名空间中的实体
int number = 10;

void display()
{
    cout << "display() " << endl;
}

} //end of namespace wd

int main(void)
{
    cout << "wd::number = " << wd::number << endl;
    wd::display(); //作用域限定符

    return 0;
}

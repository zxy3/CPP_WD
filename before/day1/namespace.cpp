#include <iostream>

using namespace std; //using编译指令 (standard)一次性把std空间中的所有实体全部引入

int cout()
// 与命名空间的函数重名
{
    printf("hello\n");
    return 0;
}

namespace wd
{

//命名空间中的实体
int number = 10;

void display()
{
    std::cout << "display() " << std::endl;
}

} //end of namespace wd

int main(void)
{
    std::cout << "wd::number = " << wd::number << std::endl;
    wd::display(); //作用域限定符

    // cout(); //error

    return 0;
}

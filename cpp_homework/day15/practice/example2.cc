// 空间配置器
#include <memory>
#include <iostream>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    // STL allocator将上述两阶段操作区分开来。
    // 内存配置由alloc::allocator()负责，
    // 内存释放操作由alloc::deallocator()负责；
    // 对象构造由::constructor()负责，
    // 对象析构由::destroy()负责。
    allocator<int> a1;       // 开辟一个int类型的内存空间
    int *a = a1.allocate(1); // 用整形指针指向这个空间 1是开辟个数，用a获取
    // 此时没有任何元素，这个空间上没有对象
    a1.construct(a, 7); // 构造对象，放在刚才开辟的空间
    cout << "将初始化后的a[0]打印出来--------------";
    cout << a[0] << '\n';
    a1.deallocate(a, 1); // 释放内存

    // default allocator for strings
    allocator<string> a2;

    // same, but obtained by rebinding from the type of a1
    decltype(a1)::rebind<string>::other a2_1;
    // same, but obtained by rebinding from the type of a1 via allocator_traits
    allocator_traits<decltype(a1)>::rebind_alloc<string> a2_2;

    string *s = a2.allocate(2); // space for 2 strings

    a2.construct(s, "first");
    a2.construct(s + 1, "second");

    cout << s[0] << '\n'
         << s[1] << '\n';
    // 销毁对象，但不会销毁空间，每次销毁一个元素
    a2.destroy(s);
    a2.destroy(s + 1);
    // 指定一个位置s，回收元素个数2
    a2.deallocate(s, 2);
}
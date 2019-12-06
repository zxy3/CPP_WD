#include <iostream>
#include <functional>
using namespace std;

// using std::cout;
// using std::endl;

typedef void (*Function)();
// 定义一个普通类
class example
{
private:
    /* data */
public:
    example() = default;
    ~example();
    // {
    //     cout << "~example()" << endl;
    // }
    // display
    void display()
    {
        cout << "display------------" << endl;
    }
    // print
    void print()
    {
        cout << "print---------------" << endl;
    }
    int add(int a, int b)
    {
        // cout << "add(int a, int b)" << endl;
        return a + b;
    }
};

// test
void test0(void)
{
    example e;
    std::function<void()> f = std::bind(&example::display, e);
    f();
    // 占位符专用
    using namespace std::placeholders;
    auto d = bind(&example::add, e, _1, 2);
    cout << "d(12,2)-----------------" << d(12) << endl;
}

//main
int main(void)
{
    test0();
    return 0;
}
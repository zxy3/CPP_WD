///用模板类实现栈
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// 声明一个函数模板
template <class T, int kSize = 10>
class Stack
{
public:
    Stack()
        : _top(-1), _data(new T[kSize]())
    {
        cout << "Stack()" << endl;
    }

    ~Stack();

    bool full() const;
    bool empty() const;
    void push(const T &t);
    void pop();
    T &top() const;

private:
    int _top;
    T *_data;
};

// 实现
template <class T, int KSize>
Stack<T, kSize>::~Stack()
{
    if (_data)
    {
        delete[] _data;
    }
}
template <class T, int kSize>
void Stack<T, kSize>::push(const T &t)
{
    if (!full())
    {
        _data[++_top] = t;
    }
    else
    {
        //LogInfo();
        cout << "栈满!" << endl;
    }
}
//test
int main(void)
{
    Stack<int> stack;
    cout << "此时栈中是否为空?" << stack.empty() << endl;
    stack.push(1);
    cout << "此时栈中是否为空?" << stack.empty() << endl;

    for (int idx = 2; idx != 12; ++idx)
    {
        stack.push(idx);
    }
    cout << "此时栈中是否已满?" << stack.full() << endl;

    while (!stack.empty())
    {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << '\n';
    cout << "此时栈中是否为空?" << stack.empty() << endl;
    reutrn 0;
}
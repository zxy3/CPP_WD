#include <bits/stdc++.h>
using namespace std;

// 模板类
template <typename T, int num>
class myQueue
{
private:
    /* data */
    T _arr[num];
    int _front = 0;
    int _tell = 0;

public:
    myQueue()
    {
        _front = 0;
        _tell = 0;
#if 0
        cout << _front << " " << _tell << " " << num << endl;
#endif
    }
    ~myQueue()
    {
        cout << "~myQueue()" << endl;
    }
    bool empty();
    bool full();
    bool push(const T &_data);
    bool pop(T _data);
    void display();
};
//----------------------成员函数--------------------------
// 判断队列空
template <typename T, int num>
bool myQueue<T, num>::empty()
{
    return _front == _tell;
}
// 判断队列满
template <typename T, int num>
bool myQueue<T, num>::full()
{
#if 0
        cout << _front << " " << _tell << " " << num << endl;
#endif
    return _front == num;
}
// 入队
template <typename T, int num>
bool myQueue<T, num>::push(const T &data)
{
    if (!full())
    {
        cout << "push() -> " << data << endl;
        _arr[_front] = data;
        ++_front;
        return true;
    }
    else
    {
        return false;
    }
}
// 出队
template <typename T, int num>
bool myQueue<T, num>::pop(T data)
{
    if (!empty())
    {
        cout << "pop() -> " << data << endl;
        data = _arr[_tell];
        ++_tell;
#if 0
        cout << _front << " " << _tell << " " << num << endl;
#endif
        return true;
    }
    else
    {
#if 0
        cout << _front << " " << _tell << " " << num << endl;
#endif
        return false;
    }
}
// 打印队列
template <typename T, int num>
void myQueue<T, num>::display()
{
    cout << "void myQueue<T, num>::display() --> ";
#if 0
    cout << endl;
    cout << "_tell -> " << _tell << endl;
    cout << "_front -> " << _front << endl;
#endif
    if (_tell == _front)
    {
        cout << "判断队列 --> 此时队列空" << endl;
    }
    else
    {
        int temp = _tell;
        while (_front != temp)
        {
            cout << _arr[temp] << " <- ";
            ++temp;
        }
        cout << endl;
    }
}
// test
int main(void)
{
    myQueue<int, 5> qu1;
#if 0
    cout << "队列空间: " << sizeof(qu1) << endl;
#endif
    cout << "判断队列 --> ";
    qu1.full() == 1 ? cout << "此时队列满" << endl : cout << "此时队列空" << endl;
    int data1 = 1;
    int data2 = 2;
    qu1.push(1);
    qu1.push(2);
    qu1.display();
    qu1.pop(data1);
    qu1.pop(2);
    qu1.display();
    qu1.push(3);
    qu1.display();
    return 0;
}
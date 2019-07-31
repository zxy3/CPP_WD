// 编写一个类，实现简单的栈。栈中有以下操作：
// 		   > 元素入栈     void push(int);
// 		   > 元素出栈     void pop();
// 		   > 读出栈顶元素 int top();
// 		   > 判断栈空     bool emty();
// 		   > 判断栈满     bool full();
// 	如果栈溢出，程序终止。栈的数据成员由存放
#include <bits/stdc++.h>
using namespace std;
class Stack
{
public:
    // 构造函数
    Stack() = default;
    // Stack(const int *data, int len)
    // {
    //     _data = data;
    //     cout << "Stack(const int *data, int len)" << endl;
    //     _len = len;
    // }
    // Stack(int len)
    // {

    //     cout << "Stack(int len)" << endl;
    //     _len = len;
    // }
    //系统提供的拷贝构造函数不再满足需求
#if 0
	Stack(const Stack & rhs)
	: _data(rhs._data) //浅拷贝
	, _len(rhs._len)
	{
		cout << "Stack(const Stack &)" << endl;
	}
    //Stack(const Stack  rhs)
    //Stack(Stack & rhs)
    Stack(const Stack &rhs)
        : _data(new char[strlen(rhs._data) + 1]()) //深拷贝
          ,
          _len(rhs._len)
    {
        cout << "Stack(const Stack &)" << endl;
        strcpy(_data, rhs._data);
    }

	Stack & operator=(const Stack & rhs)
	{
		_data = rhs._data;
		_len = rhs._len;

		cout << "Stack & operator=(const Stack &)" << endl;
		return *this;
	}

    Stack &operator=(const Stack &rhs)
    {
        if (this != &rhs)
        {
            //自复制
            cout << "Stack & operator=(const Stack &)" << endl;
            delete[] _data; //回收左操作申请的空间

            //再进行深拷贝
            _data = new char[strlen(rhs._data) + 1]();
            strcpy(_data, rhs._data);
            _len = rhs._len;
        }
        return *this;
    }
#endif
    ~Stack()
    { //析构函数的作用是用来清理对象开辟的资源
        cout << "销毁----> ~Stack()" << endl;
    }

    // 打印原始数据
    void print();
    // > 元素入栈
    void push(int);
    // > 元素出栈
    void pop();
    // > 读出栈顶元素
    int top();
    // > 判断栈空
    bool emty();
    // > 判断栈满
    bool full();

private:
    static int _data[];
    static int _len;
};

//---------------------------------
// 类外初始化静态成员变量
int Stack::_len = 10;
int Stack::_data[10] = {0};

int i;
inline void Stack::print()
{
    i = 0;
    if (_data[i] == 0)
    {
        cout << "此时栈空" << endl;
    }
    while (i < _len && _data[i] != 0)
    {
        cout << _data[i];
        i++;
    }
    cout << "" << endl;
    cout << "栈总长:" << _len << endl;
}
// > 元素入栈
inline void Stack::push(int data)
{
    cout << "入栈操作" << endl;
    if (full())
    {
        cout << "不可入栈" << endl;
    }
    else
    {
        int top = i;
        _data[top] = data;
        print();
    }
}
// > 元素出栈
inline void Stack::pop()
{
    cout << "出栈操作" << endl;
    ;
    if (emty())
    {
        cout << "不可出栈";
    }
    else
    {
        i = 0;
        while (i <= sizeof(_data))
        {
            if (0 == _data[i])
            {
                break;
            }
            i++;
        }
        int top = i;
        _data[--top] = 0;
        print();
    }
}
// > 读出栈顶元素
inline int Stack::top()
{
    cout << "读栈顶元素 :";
    i = 0;
    while (i <= sizeof(_data))
    {
        if (0 == _data[i])
        {
            break;
        }
        i++;
    }
    cout << _data[--i]<<endl;
}
// > 判断栈空
inline bool Stack::emty()
{
    cout << "判断栈非空 :";
    if (0 == _data[0])
    {
        cout << "栈空" << endl;
        return true;
    }
    else
    {
        cout << "非空" << endl;
        return false;
    }
}
// > 判断栈满
inline bool Stack::full()
{
    cout << "判断栈满 :";
    i = 0;
    while (i <= sizeof(_data))
    {
        if (0 == _data[i])
        {
            break;
        }
        i++;
    }
    if (i == _len)
    {
        cout << "栈满" << endl;
        return true;
    }
    else
    {
        cout << "非满" << endl;
        return false;
    }
}

int main(void)
{
    // Stack s;
    // s.print();

    // Stack s1("123", strlen("123"));
    // s1.print();
    // s1.push('a');
    // s1.pop();

    Stack s2;
    s2.print();
    s2.push(10);
    s2.push(12);
    s2.push(14);
    s2.top();
    s2.pop();
    s2.top();
    return 0;
}
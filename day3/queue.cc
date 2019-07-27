//        > 元素入队             void push(int);
//        > 元素出队             void pop();
//        > 读取队头元素         int front();
//        > 读取队尾元素         int back();
//        > 判断队列是否为空     bool emty();
// 	      > 判断队列是否已满     bool full();

#include <bits/stdc++.h>
using namespace std;
class Queue
{
public:
    // 构造函数
    Queue() = default;

#if 0
	Queue(const Queue & rhs)
	: _data(rhs._data) //浅拷贝
	, _len(rhs._len)
	{
		cout << "Queue(const Queue &)" << endl;
	}
    //Queue(const Queue  rhs)
    //Queue(Queue & rhs)
    Queue(const Queue &rhs)
        : _data(new char[strlen(rhs._data) + 1]()) //深拷贝
          ,
          _len(rhs._len)
    {
        cout << "Queue(const Queue &)" << endl;
        strcpy(_data, rhs._data);
    }

	Queue & operator=(const Queue & rhs)
	{
		_data = rhs._data;
		_len = rhs._len;

		cout << "Queue & operator=(const Queue &)" << endl;
		return *this;
	}

    Queue &operator=(const Queue &rhs)
    {
        if (this != &rhs)
        {
            //自复制
            cout << "Queue & operator=(const Queue &)" << endl;
            delete[] _data; //回收左操作申请的空间

            //再进行深拷贝
            _data = new char[strlen(rhs._data) + 1]();
            strcpy(_data, rhs._data);
            _len = rhs._len;
        }
        return *this;
    }
#endif
    ~Queue()
    { //析构函数的作用是用来清理对象开辟的资源
        cout << "销毁队列" << endl;
    }

    // 打印原始数据
    void print();
    // > 元素入队
    void push(int);
    // > 元素出队
    void pop();
    // > 读取队头元素
    int front();
    // > 读取队尾元素
    int back();
    // > 判断队列是否为空
    bool emty();
    // > 判断队列满
    bool full();

private:
    typedef struct _Data
    {
        int _num = 0;
        struct _Data *_pNext = nullptr;
    } _Data_t, *_pData_t;
    _Data_t data;
    _pData_t phead = &data;
    _pData_t ptemp = &data;
    _pData_t ptail = &data;

    // 初始化静态结构体成员变量
    struct _Data1
    {
        int x;
        struct _Data *_pNext;
        _Data1(int num, _Data *p)
            : x(num), _pNext(p)
        {
        }
    };
    static _Data1 d1;
};

//--------------------------------

int i;
// Singleton * Singleton::_pInstance = nullptr;
Queue::_Data1 Queue::d1(12, nullptr);

// 打印队列
inline void Queue::print()
{
    while (ptemp)
    {
        cout << ptemp->_num;
        ptemp = ptemp->_pNext;
    }
    cout << endl;
}
// > 元素入队
inline void Queue::push(int num)
{
    cout << "元素入队" << endl;
    if (phead->_pNext == nullptr)
    {
        phead->_num = num;
    }
    else
    {
        _pData_t pNew = (_pData_t)calloc(1, sizeof(_Data_t));
        pNew->_num = num;
        ptail->_pNext = pNew;
        ptail = pNew;
        print();
    }
}

//             // if (0 != _data[i])
//             // {
//             //     _data[i] = data;
//             //     int j = 0;
//             //     while (j < _len)
//             //     {
//             //         cout << _data[i];
//             //         j++;
//             //     }
//             //     break;
//             // }
//             // else
//             // {
//             //     i++;
//             // }
//         }
//         print();
//     }
// }
// // > 元素出队
// inline void Queue::pop()
// {
//     cout << "出队操作" << endl;
//     ;
//     if (emty())
//     {
//         cout << "不可出队";
//     }
//     else
//     {
//         i = 0;
//         while (i <= sizeof(_data))
//         {
//             if (0 != _data[i])
//             {
//                 // 对头值为0表示出队
//                 _data[i] = 0;
//             }
//             i++;
//         }
//         print();
//     }
// }
// // > 读出对头元素
// inline int Queue::top()
// {
//     cout << "读对头元素 :";
//     if (!emty())
//     {
//         i = 0;
//         while (i < _len)
//         {
//             if (_data[i] != 0)
//             {
//                 cout << _data[i] << endl;
//                 break;
//             }
//             else
//             {
//                 i++;
//             }
//         }
//     }
//     else if (emty())
//         ;
// }

// > 判断队列空
inline bool Queue::emty()
{
    cout << "判断队列 :";
    if (phead == nullptr)
    {
        cout << "空" << endl;
        return true;
    }
    else
    {
        cout << "非空" << endl;
        return false;
    }
}
// // > 判断队列满
// inline bool Queue::full()
// {
//     cout << "判断队列满 :";
//     i = _len;
//     if (0 != _data[--i])
//     {
//         cout << "满" << endl;
//         return true;
//     }
//     else
//     {
//         cout << "非满" << endl;
//         return false;
//     }
// }

int main(void)
{
    Queue s2;
    s2.print();
    s2.emty();
    s2.push(10);
    // s2.push(12);
    // s2.push(14);
    // s2.front();
    // s2.pop();
    // s2.front();
    return 0;
}
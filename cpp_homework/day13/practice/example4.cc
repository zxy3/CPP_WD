///普通类-->模版类
#include <iostream>
using namespace std;

#if 0
class StackA
{
private:
    int point;
    int size;
    int *sz;

public:
    StackA(int iNum = 1)
    {
        point = 0;
        size = iNum;
        sz = new int[size];
    }
    ~StackA()
    {
        delete[] sz;
    }
    bool isEmpty() { return point == 0; }
    bool isFull() { return point == size; }
    int &GetPos() { return point; }
    bool push(const int &obj);
    bool pop(int &obj);
};

bool StackA::push(const int &obj)
{
    if (isFull())
        return false;
    else
    {
        sz[point++] = obj;
        return true;
    }
}

bool StackA::pop(int &obj)
{
    if (isEmpty())
        return false;
    else
    {
        obj = sz[--point];
        return true;
    }
}

int main()
{
    StackA st(10); //普通类, int类型
                   //	StackA<int> st(10);			//模版类, int类型
    cout << "开始时st是否为空？ " << st.isEmpty() << endl;

    st.push(5); //压入元素5
    cout << "此时st是否为空？ " << st.isEmpty() << endl;

    for (int i = 1; i < 10; i++)
    {
        st.push(i); //压入9个元素
    }
    cout << "此时st是否已满？" << st.isFull() << endl;

    int rec = 0;
    while (st.pop(rec))
        cout << rec << "  ";
    cout << endl;

    return 0;
}
#endif

#if 1
template <class T, int num> //类型参数表
//或template <class T = int, int num = 10>
class Stack //Stack类定义
{
private:
    T sz[num]; //存储空间，用数组表示
    int point; //指针，表示存储位置（即元素个数）

public:
    Stack() //构造函数
    {
        point = 0; //初始位置为0，栈底
    }

    bool isEmpty();       //判断栈是否为空
    bool isFull();        //判断栈是否已满
    bool push(const T &); //将一个元素压入栈
    bool pop(T &);        //从栈中弹出一个元素
    int &GetPos()
    {
        return point;
    }
};

template <class T, int num> //参数列表不要求字字相同，但形式要相同
bool Stack<T, num>::isEmpty()
{
    return point == 0; //point为0，说明当前无元素
}

template <class T, int num>
bool Stack<T, num>::isFull()
{
    return point == num; //point为num，说明数组已满
}

template <class T, int num>
bool Stack<T, num>::push(const T &obt)
{
    if (isFull())
        return false; //如果栈已满，压入不成功，返回false
    else
    {
        sz[point] = obt; //将传入的元素存储在point指向的当前位置
        point++;         //point加1，向栈顶移动
        return true;     //压入成功，返回true
    }
}

template <class T, int num>
bool Stack<T, num>::pop(T &obt)
{
    if (isEmpty())
        return false; //如果栈已空，无法弹出，返回false
    else
    {
        point--;         //point减1，向栈底移动，指向存储的最上面一个元素
        obt = sz[point]; //将point指向的当前位置元素复制给传入参数
        return true;     //弹出成功，返回true
    }
}

int main()
{
    Stack<int, 10> st; //模版类, 模版参数为<class T, int num>
    cout << "开始时st是否为空？ " << st.isEmpty() << endl;

    st.push(5); //压入元素5
    cout << "此时st是否为空？ " << st.isEmpty() << endl;

    for (int i = 1; i < 10; i++)
    {
        st.push(i); //压入9个元素
    }
    cout << "此时st是否已满？" << st.isFull() << endl;

    int rec = 0;
    while (st.pop(rec))
        cout << rec << "  ";
    cout << endl;

    return 0;
}
#endif

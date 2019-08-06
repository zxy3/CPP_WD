///迭代器的使用
#include <iostream>
#include <vector>

using namespace std;

class example
{
private:
    /* data */
    int _size;
    int _cnt;
    int *_data;

public:
    example(int);
    ~example();
    void display() const;
    // 模板类--嵌套在普通类里面
    template <class Iterator>
    // beg和end是模板类创建的对象
    void setData(Iterator beg, Iterator end)
    {
        while (beg != end && _cnt < _size)
        {
            _data[_cnt] = *beg;
            ++_cnt;
            ++beg;
        }
    }
};

example::example(int data)
    : _size(data),
      _cnt(0),
      _data(new int[_size]())
{
    cout << "example::example(int data)" << endl;
}
example::~example()
{
    cout << "example::~example()" << endl;
}
inline void example::display() const
{
    for (int i = 0; i != _cnt; ++i)
    {
        cout << _data[i] << " ";
    }
    cout << endl;
}

// test
int main(void)
{
    vector<int> numbers(10, 1);

    example e(10);
    // begin和end是迭代器
    e.setData(numbers.begin(), numbers.end());
    e.display();

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    example e2(10);
    e2.setData(arr, arr + 10);
    e2.display();

    return 0;
}
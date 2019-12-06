///类模板-概念
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class example
{
private:
    int _size;
    int _cnt;
    int *_data;

public:
    // 模板类
    example(int size)
        : _size(size),
          _cnt(0),
          _data(new int[_size])
    {
        cout << "example()" << endl;
    }
    ~example()
    {
        cout << "~example()" << endl;
    }
    void display() const;
    template <class T>
    void setdata(T beg, T end, int index)
    {
        while (beg != end)
        {
            _data[_cnt++] = *beg;
            ++beg;
        }
        // 此句会先得到执行
        cout << index << endl;
    }
};

void example::display() const
{
    for (int idx = 0; idx != _cnt; ++idx)
    {
        cout << _data[idx] << " ";
    }
    cout << endl;
}
// test
int main(void)
{
    vector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 0);
    for (auto &data : numbers)
    {
        cout << data << " ";
    }
    cout << '\n';

    example ex(10);
    ex.setdata(numbers.begin(), numbers.end(), 1);
    // iota(ex.begin(), ex.end(), 0);  ex不是容器，不能用迭代器
    ex.display();
    return 0;
}

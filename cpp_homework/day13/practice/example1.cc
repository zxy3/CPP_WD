///反向迭代器相关知识点
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

//rend以及rbegin,r-反向
#if 0
int main()
{
    // 初始化一个数组
    int a[] = {4, 6, -3, 9, 10};
    cout << "Array backwards: ";
    // 通过反向迭代器拿到数组反向的头部和尾部，然后输出到一个流对象中，打印到终端
    copy(rbegin(a), rend(a), ostream_iterator<int>(cout, " "));

    // 初试化一个容器
    cout << "\nVector backwards: ";
    vector<int> v = {4, 6, -3, 9, 10};
    // 拿到容器的反向的头部和尾部，然后输出到一个流对象中，打印到终端
    copy(rbegin(v), rend(v), ostream_iterator<int>(cout, " "));
    cout << "\n";
}
#endif

//输入流迭代器，输出流迭代器
#if 1
int main()
{
    // 只有容器才有迭代器
    // 创建一个字符流对象，高级之处是不用再终端上进行输入
    istringstream str("1.0 2 3 4 5 6");
    // 把流对象看做一个容器，为它创建一个流迭代器
    copy(istream_iterator<double>(str), istream_iterator<double>(), ostream_iterator<double>(cout, "-> "));
    // str.seekg(std::ios::beg);
    cout << "--------------------111" << endl;

    // 求局部和接口
    partial_sum(istream_iterator<int>(str), istream_iterator<int>(), ostream_iterator<double>(cout, " "));

    istringstream str2("1 3 5 7 8 9 10");
    cout << "\nThe first even number is " << *find_if(istream_iterator<double>(str2), istream_iterator<double>(), [](int i) {
        return i % 2 == 0;
    }) << ".\n";
    //" 9 10" left in the stream
}
#endif

// copy
#if 0
int main()
{
    // 定义一个含有10个元素的容器
    vector<int> from_vector(10);
    // 初始化容器内部的元素
    iota(from_vector.begin(), from_vector.end(), 0);
    // 在定义一个容器，不指定大小
    vector<int> to_vector;
    // 从第一个容器拷贝到第二个容器，顺序方式
    copy(from_vector.begin(), from_vector.end(), back_inserter(to_vector));
    // or, alternatively,
    vector<int> to_vector2(from_vector.size());
    copy(from_vector.begin(), from_vector.end(), to_vector2.begin());
    cout << "to_vector contains: ";
    copy(to_vector2.begin(), to_vector2.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';
    // either way is equivalent to
    vector<int> to_vector3 = from_vector;
    copy(from_vector.begin(), from_vector.end(), to_vector3.begin());
    cout << "to_vector contains: ";
    copy(to_vector3.begin(), to_vector3.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';
    cout << "to_vector contains: ";
    // 从第二个容器拷贝到输出流对象中
    copy(to_vector.begin(), to_vector.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
#endif

//反向迭代器
#if 0
int main()
{
    string s = "Hello, world";
    // rbegin拿到的是反向的头部（看做一个指针），复制给一个反向迭代器
    reverse_iterator<string::iterator> r = s.rbegin();
    r[7] = 'O'; // replaces 'o' with 'O'
    cout << "-----------" << r[7] << endl;
    cout << "----------" << s << endl;
    // 迭代器现在指向“O”
    r += 7; // iterator now points at 'O'
    cout << "----------" << s << endl;
    // 从r指向的位置，反向迭代，rend拿到的是反向的尾部，正向的头部
    string rev(r, s.rend());
    string rev1(s.rbegin(), s.rend());
    cout << rev << '\n';
    cout << rev1 << '\n';
}
#endif
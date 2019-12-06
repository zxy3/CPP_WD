#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#if 0
struct Sum
{
    Sum() : sum{0} {}
    void operator()(int n) { sum += n; }
    int sum;
};

int main()
{
    vector<int> nums{3, 4, 2, 8, 15, 267};
    auto print = [](const int &n) { cout << " " << n; };
    cout << "打印数组:";
    for_each(nums.begin(), nums.end(), print);
    cout << '\n';
    // 可进行修改操作:lambda表达式 -> 匿名函数[]表示获取元素（）表示形参列表{}表示函数的执行体
    for_each(nums.begin(), nums.end(), [](int &n) { n++; });
    // calls Sum::operator() for each number
    Sum s = for_each(nums.begin(), nums.end(), Sum());
    cout << "after: ";
    for_each(nums.begin(), nums.end(), print);
    cout << '\n';
    cout << "sum: " << s.sum << '\n';
}
#endif
///lambda获取引用操作
#if 0

#include <iostream>
using namespace std;
int main()
{
    int a = 1, b = 1, c = 1;

    auto m1 = [a, &b, &c]() mutable {
        auto m2 = [a, b, &c]() mutable {
            cout << a << b << c << '\n';
            a = 4;
            b = 4;
            c = 4;
        };
        a = 3;
        b = 3;
        c = 3;
        m2();
    };

    a = 2;
    b = 2;
    c = 2;

    m1();                             // calls m2() and prints 123
    cout << a << b << c << '\n'; // prints 234
}
#endif

#if 0
#include <iostream>
using namespace std;
int main()
{
    int a = 1, b = 1, c = 1;
 
    auto m1 = [a, &b, &c](){
        cout << "-----------"<<a << b << c << '\n';
        // auto m2 = [a, b, &c]() mutable {
        //     cout << "-----"<<a << b << c << '\n';
        //     a = 4; b = 4; c = 4;
        // };
        // a = 3; b = 3; c = 3;
        // m2();
    };
 
    a = 2; b = 2; c = 2;
 
    m1();                             // calls m2() and prints 123
    cout << a << b << c << '\n'; // prints 234
}
#endif

///remove
///动态扩容，先创建一个原来空间2倍大的空间，元素转移到新空间，销毁原来的空间
#if 0
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

int main()
{
    // erase-remove惯用法 用remove移动到末尾，然后删除
    string str1 = "Text 66 with some 66 spaces";
    //没有直接删除元素，它不关心容器，不知道是什么元素,
    //一删除元素，迭代器就失效，所以不能执行这个操作
    remove(str1.begin(), str1.end(), 66);
    cout << str1 << endl;

    str1.erase(remove(str1.begin(), str1.end(), ' '),
               str1.end());
    cout << str1 << '\n';

    cout << "第二种情况" << '\n';
    string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(remove_if(str2.begin(), str2.end(), [](unsigned char x) { return isspace(x); }),
               str2.end());
    cout << str2 << '\n';

    vector<int> data;
    data.push_back(1);
    data.push_back(2);
    // auto *it = data.begin();
    // cout << *it << " " endl;
    // for (; it != data.end(); it+)
    // {
        // cout << *it << " " endl;
    // }
}
#endif
///replace
#if 1
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
using namespace std;

int main()
{
    array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    for (int a : s)
    {
        cout << a << " ";
    }
    cout << '\n';

    replace(s.begin(), s.end(), 8, 88);
    cout << "8 替换成 88 -------------";
    for (int a : s)
    {
        cout << a << " ";
    }
    cout << '\n';

    replace_if(s.begin(), s.end(),
               bind(less<int>(), placeholders::_1, 5), 55);
    for (int a : s)
    {
        cout << a << " ";
    }
    cout << '\n';
}
#endif
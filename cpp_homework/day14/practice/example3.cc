///bind 操作
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;
// 打印参数
void test(int i, double d, const string &s)
{
    cout << "i= " << i << " d= " << d << " s= " << s << endl;
}
// 打印参数
int test1(int i, double d, const string &s)
{
    cout << "i= " << i << " d= " << d << " s= " << s << endl;
    return i;
}
// test
int main(void)
{
    // typedef void (*Function)(); 函数类型
    // 函数容器
    function<void()> fp;
    string s = "first";
    int a = 3;
    double b = 6.7;
    // 用集合中的元素绑定一个带3个参数的函数
    fp = bind(&test, a, b, s);
    fp();
    // 返回值是空，参数是一个Int类型，一个string类型
    function<void(int, const string &)> fp1;
    double b2 = 4.6;
    fp1 = bind(test, _1, b2, _2);
    // 占位符的参数一定要在函数被调的时候填写
    fp1(4, "kity");
    // 返回值int 参数int 和string 引用类型
    function<int(int, const string &)> fp2;
    fp2 = bind<int>(test1, _1, b2, _2);
    // int y = fp2(4, "kity");
    cout << "fp2(4, kity )-------------" << fp2(4, "kity") << endl;
    // 直接传参数，不用占位符
    auto fn = bind(test, 10, 23.3, "heko"); //不用function指定函数参数，
    fn();
    // 调换占位符的顺序，依然按照占位符的数字对应参数,占位符的数字表示形参的位置
    auto ff = bind(test, _1, _3, _2); //bind中的i参数类型与test的_j的参数类型对应
    ff(12, "ppp", 12.5);

    class A
    {
    public:
        void print(int a, double x)
        {
            cout << a << " " << x << endl;
        }
    };
    //绑定类中的成员函数
    A a3;
    auto fclass = bind(&A::print, &a3, 11, 7.7);
    // 此时fclass为一个函数
    cout << "fclass()--------------";
    fclass();
    return 0;
}
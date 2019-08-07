///嵌套模版类的模版类
#include <iostream>
using namespace std;

// 模板类
template <class T>
class Outside //外部Outside类定义
{
public:
    template <class R>
    class Inside //嵌套类模板定义
    {
    private:
        // 类本身作为一个成员
        R r;

    public:
        Inside(R x) //模板类的成员函数可以在定义时实现
        {
            r = x;
        }
        //void display();
        void display()
        {
            cout << "Inside: " << r << endl;
        }
    };
    //Outside类的构造函数
    Outside(T x)
        : t(x)
    {
        cout << "Outside(T x) : t(x)" << endl;
    }

    // 外部类的成员函数，调用内部类的成员函数
    void display()
    {
        cout << "Outside:";
        t.display();
    }

private:
    Inside<T> t;
};
#if 0
template <class T>
template <class R>
void Outside<T>::Inside<R>::display() //模板类的成员函数也可以在定义外实现
{                                     //但必须是在所有类定义的外边,不能放在Outside内Inside外去实现.
    cout << "Inside: " << Outside<T>::Inside<R>::r << endl;
}

template <class T>
void Outside<T>::display()
{
    cout << "Outside:";
    t.display();
}
#endif

int main()
{
    //声明Inside类对象obin
    Outside<int>::Inside<double> obin(3.5);
    // 内部类display方法
    obin.display();
    // 外部类display方法
    Outside<int> obout(2); //创建Outside类对象obout
    obout.display();

    // getchar();linux不需要这句
    return 0;
}

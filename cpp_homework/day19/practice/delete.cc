#include <iostream>
#include <memory>
#include <string>
using namespace std;

//自定义删除器方式:
//主要就是自己编写一个删除器，指定输入的参数，然后实现相应的释放操作，并将这个删除器传入 unique_ptr中。
struct FileDeleter
{
    void operator()(FILE *fp)
    {
        if (fp)
        {
            fclose(fp);
            cout << ">> fclose(fp)" << endl;
        }
    }
};

// test0
void test0()
{
    unique_ptr<FILE, FileDeleter> up(fopen("test.txt", "a+"), FileDeleter());

    string msg = "孤寂零落,执奋为谁？\n";
    fwrite(msg.c_str(), 1, msg.size(), up.get());
}
// test1
void test1()
{
    shared_ptr<FILE> sp(fopen("test.txt", "a+"), FileDeleter());
    string msg = "hello,world\n";
    fwrite(msg.c_str(), 1, msg.size(), sp.get());
}

// main
int main(void)
{
    test0();
    // test1();

    return 0;
}


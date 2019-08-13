///move
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

// main
int main(void)
{
    // 移动2个左值对象
    string s1 = "china";
    string s2 = "USA";
    // 将S1移动到S2，此时S1就是空的
    s2 = move(s1);
    cout << "s2 -----> " << s2 << endl;

    // 移动右值
    // string s3 = "taiwan";
    string s4(move("taiwan"));
    string s5 = move("aomen");
    cout << "s4 -----> " << s4 << endl;
    cout << "s5 -----> " << s5 << endl;
}
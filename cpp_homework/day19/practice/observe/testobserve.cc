#include "subject.h"
#include "observe.h"

#include <iostream>
#include <memory>
using namespace std;

int main(void)
{
    // 创建对象
    unique_ptr<observer> baby1(new baby("大宝"));
    unique_ptr<observer> baby2(new baby("小宝"));
    unique_ptr<observer> nurse1(new nurse("小丽"));
    unique_ptr<observer> nurse2(new nurse("小美"));
    ring ring;

    // 添加观察对象2个
    ring.attach(baby1.get());
    ring.attach(nurse1.get());
    guest guest("lili");
    // 产生行为
    guest.knock(ring);
    // 删除观察者
    // ring.detach(nurse2.get());
    cout << "-------------------------------------------" << endl;
    guest.knock(ring);
    return 0;
}
#include "subject.h"
#include "observe.h"

#include <iostream>
#include <algorithm>
using namespace std;

//--------实现头文件中类的接口------------
// attch
void ring::attach(observer *obj)
{
    auto it = find(_oblist.begin(), _oblist.end(), obj);
    // 如果没有就在集合中添加节点
    if (it == _oblist.end())
    {
        _oblist.push_back(obj);
    }
}
// detach
void ring::detach(observer *obj)
{
    auto it = find(_oblist.begin(), _oblist.end(), obj);
    if (it != _oblist.end())
    {
        _oblist.erase(it);
    }
}
// notify
void ring::notify()
{
    for (auto &obj : _oblist)
    {
        obj->update();
    }
}
// ispressed
void ring::isPressed()
{
    if (!_isalarming)
    {
        // 模拟铃声（场景）
        _isalarming = true;
        notify();
    }
    // 通知完毕后，开关置为false
    _isalarming = false;
}
// knock
void guest::knock(ring &ring)
{
    cout << ">>> guest --> " << _name << "  正在敲门！" << endl;
    //通知所有观察者
    ring.isPressed();
}

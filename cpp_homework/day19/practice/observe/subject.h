#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class observer;
// 角色类，都只提供接口
class subject
{
public:
    // -----------成员函数-------------
    virtual void attach(observer *obj) = 0;
    virtual void detach(observer *obj) = 0;
    virtual void notify() = 0;
    // 基类是虚函数，其他派生类的析构函数都要是虚函数
    virtual ~subject()
    {
        // cout << "delete subject()" << endl;
    }

private:
protected:
};

// ring
class ring
    : public subject
{
private:
// 添加观察者
    list<observer *> _oblist;
    bool _isalarming;

public:
    // 构造函数
    ring()
        : _isalarming(false)
    {
    }
    // 析构函数
    // 成员函数
    void isPressed();
    //基类的接口都要实现掉
    virtual void attach(observer *obj);
    virtual void detach(observer *obj);
    virtual void notify();

protected:
};

class guest
{
public:
    guest(const string &name)
        : _name(name)
    {
    }
    // 成员函数
    void knock(ring &ring);

private:
    string _name;
};
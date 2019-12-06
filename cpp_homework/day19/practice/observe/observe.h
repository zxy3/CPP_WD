// 观察者模式
#pragma once
// 护士和baby两个类写在头文件中
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
using namespace std;
// 观察者类
class observer
{
    // 基类都是接口
public:
    virtual void update(){
        // cout << "virtual void update()" << endl;
    };
    virtual ~observer()
    {
        // cout << "~observer()" << endl;
    }
};

// baby
class baby
    : public observer
{
private:
    string _name = "null";

public:
    // 构造函数
    baby() = default;
    baby(const string &name)
        : _name(name)
    {
    }
    // 析构函数
    ~baby()
    {
        // cout << "delete baby()" << endl;
    }
    // 成员函数
    void update()
    {
        // 根据时钟周期，获得伪随机数
        ::srand(::clock());
        int number = ::rand() % 100;
        if (number < 70)
        {
            cout << "小孩 ---> " << _name << " 正在睡觉！" << endl;
        }
        else
        {
            cout << "小孩 ---> " << _name << " 开始要哭了！" << endl;
        }
    }
};

// nurse
class nurse
    : public observer
{
private:
    string _name = "null";

public:
    // 构造函数
    nurse() = default;
    nurse(const string &name)
        : _name(name)
    {
    }
    // 析构函数
    ~nurse()
    {
        // cout << "delete nurse()" << endl;
    }
    // 成员函数
    void update()
    {
        // 根据时钟周期，获得伪随机数
        ::srand(::clock());
        int number = ::rand() % 100;
        if (number < 70)
        {
            cout << "护士 --> " << _name << " 正在休息！" << endl;
        }
        else
        {
            cout << "护士 --> " << _name << "正在睡觉！" << endl;
        }
    }
};

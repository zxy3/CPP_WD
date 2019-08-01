#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

// 城市
class city
{
private:
    /* 城市 */
    string _city = "null";

public:
    city() = default;
    ~city()
    {
        cout << "~warrior()" << endl;
    }
};
// 编号和生命值（基类：每个武士都会有）
class base
{
private:
    int _no = 0;
    int _life_value = 0;

public:
};
// dragon
class dragon
    : public base
{
private:
    // 士气(没网了，暂时用拼音)
    double shiqi;
    double wuqi = no % 3;

public:
    dragon()
    {
        cout << "dragon()" << endl;
    }
    ~dragon()
    {
        cout << "~dragon()" << endl;
    }
};
// ninja
class ninja
    : public base
{
private:
    double _wuqi1 = no % 3;
    double _wuqi2 = (no + 1) % 3;

public:
    ninja()
    {
        cout << "ninja()" << endl;
    }
    ~ninja()
    {
        cout << "~ninja()" << endl;
    }
};
// iceman
class iceman
    : public base
{
private:
    double wuqi = no % 3;

public:
    iceman()
    {
        cout << "iceman()" << endl;
    }
    ~iceman()
    {
        cout << "~iceman()" << endl;
    }
};
// lion
class lion
    : public base
{
private:
    int loyalty = lifeElement;

public:
    lion()
    {
        cout << "lion()" << endl;
    }
    ~lion()
    {
        cout << "~lion()" << endl;
    }
};
// wolf
class wolf
    : public base
{
private:
public:
    wolf()
    {
        cout << "wolf()" << endl;
    }
    ~wolf()
    {
        cout << "~wolf()" << endl;
    }
};
// 武器sword, bomb,和arrow，编号分别为0,1,2
class arms
{
private:
    int _armsNo;

public:
    arms()
    {
        cout << "arms()" << endl;
    }
    ~arms()
    {
        cout << "~arms()" << endl;
    }
};
// 司令部
class Command
{
private:
    // 编号
    int no;
    // 生命元
    int lifeElement;
public:
    Command() {}
    ~Command() {}
};

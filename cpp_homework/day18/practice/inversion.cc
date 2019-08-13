///依赖倒置原则
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#if 0
class Apple
{
public:
    string name() const
    {
        return "apple";
    }
};

class Banana
{
public:
    string name() const
    {
        return "banana";
    }
};

class Mike
{
public:
    void eat(const Apple &apple)
    {
        cout << "Mike eat " << apple.name() << endl;
    }

    void eat(const Banana &banana)
    {
        cout << "Mike eat " << banana.name() << endl;
    }
};
// test
int main()
{
    Mike mike;
    Apple apple;
    Banana banana;
    mike.eat(apple);
    mike.eat(banana);

    return 0;
}
#endif

// 依赖倒置原则example 2
#if 1
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Fruit
{
public:
    virtual string name() const = 0;
};
class People
{
public:
    virtual void eat(Fruit *fruit) = 0;
};

class Apple 
: public Fruit
{
public:
// 重写基类的接口
    string name() const
    {
        return "apple";
    }
};

class Banana 
: public Fruit
{
public:
// 重写基类的接口
    string name() const
    {
        return "banana";
    }
};

class Mike 
: public People
{
public:
// 重写基类的接口 
    void eat(Fruit *fruit)
    {
        cout << "Mike eat " << fruit->name() << endl;
    }
};

class Tom 
: public People
{
public:
    void eat(Fruit *fruit)
    {
        cout << "Tom eat " << fruit->name() << endl;
    }
};
// test
int main(void)
{
    People *p1 = new Mike;
    People *p2 = new Tom;
    Fruit *f1 = new Apple;
    Fruit *f2 = new Banana;

    p1->eat(new Apple);
    p1->eat(f2);

    return 0;
}
#endif
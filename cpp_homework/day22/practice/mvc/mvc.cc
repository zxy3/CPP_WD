// MVC
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

// ----------------- student 用于保存学生信息
class Student
{
public:
    // explicit 不可被更改
    explicit Student(size_t id = 0, const string &name = string())
        : _id(id), _name(name)
    {
        cout << "id --->" << id << "    name --> " << name << endl;
    }
    // -------------成员函数-------------------------
    // 返回id
    size_t getId() const
    {
        return _id;
    }
    // 返回name
    string getName() const
    {
        return _name;
    }
    // 设置id
    void setId(size_t id)
    {
        _id = id;
    }
    // 设置name
    void setName(const string &name)
    {
        _name = name;
    }

private:
    size_t _id;
    string _name;
};
//---------------------- view 展示层，只负责展示
class View
{
public:
    // 构造函数
    View() = default;
    // 一个类中使用了另外一个类的成员，关联关系
    View(Student *student)
        : _student(student)
    {
    }
    // 设置成员
    void reset(Student *student)
    {
        _student = student;
    }
    // 展示信息
    virtual void show() const
    {
        cout << "[show()]  "
             << " id: " << _student->getId()
             << "name:" << _student->getName() << endl;
    }

protected:
    Student *_student = nullptr;
};
//------------------- Controller 控制层，没有自己的成员，全部是基于student的方法，控制
// 控制层是最上层
class Controller
{
public:
    // 成员函数
    void attach(const Student &student)
    {
        // 系统调用，往集合中添加元素
        // student.getId() 不用友元，不用继承，可以直接调用
        _students.insert(make_pair(student.getId(), student));
    }
    void detach(size_t id)
    {
        _students.erase(id);
    }
    // 三者都是关联关系
    // 给一个集合的地址就能打印出来整个集合
    void show(View *view)
    {
        for (auto it = _students.begin(); it != _students.end(); ++it)
        {
            view->reset(&(it->second));
            // auto tmp = _students.begin()->second;
            // cout << "it->second ---> "<< tmp <<endl;
    
            cout << "------------------------" << endl;
            view->show();
            cout << endl;
        }
    }

private:
    // 由一个键值对组成的集合
    map<size_t, Student> _students;
};

// -------------test
int main(void)
{
    Controller controller;
    controller.attach(Student(1, "Mike"));
    controller.attach(Student(2, "Jackie"));
    controller.attach(Student(3, "John"));
    unique_ptr<View> view(new View());
    controller.show(view.get());
    return 0;
}
#include <iostream>
using namespace std;

class person
{
private:
    /*姓名，年龄*/
    string _name = "null";
    int _age = 0;

public:
    person() = default;
    person(string name, int age)
        : _name(name), _age(age)
    {
        cout << "person(string name,int age)" << endl;
    }
    ~person()
    {
        cout << "~person()" << endl;
    }
    // 用来输出name和age
    void display()
    {
        cout << "姓名:" << _name << "  "
             << "年龄:" << _age << endl;
    }
};
#if 0
void test0(void)
{
    string s1 = "hi";
    string s2 = "hello world";
    s1 = s2;
    cout << s1 << endl;
}
#endif
#if 0
void test1(void)
{
    person p("xiongda", 23);
    p.display();
}
#endif
class employee
    : public person
{
private:
    /* 部门，工资 */
    string _department = "null";
    int _salary = 0;

public:
    employee() = default;
    employee(string name, int age, string department, int salary)
        : person(name, age),
          _department(department),
          _salary(salary)
    {
        cout << "employee(string department,int salary)" << endl;
    }
    ~employee()
    {
        cout << " ~employee()" << endl;
    }
    // 用来输出职工姓名、年龄、部门、工资
    void display()
    {
        person::display();
        cout << "部门" << _department << " "
             << "工资" << _salary << endl;
    }
    int getSalary()
    {
        return _salary;
    }
};
#if 1
void test2(void)
{
    employee ep1("xongda", 23, "销售", 10000);
    ep1.display();
    employee ep2("lili", 24, "销售", 12000);
    ep2.display();
    employee ep3("lele", 22, "销售", 10000);
    ep3.display();
    cout << "平均工资：" << (ep1.getSalary() + ep2.getSalary() + ep3.getSalary()) / 3 << endl;
}
#endif

//main
int main(void)
{
    // test0();
    // test1();
    test2();
    return 0;
}
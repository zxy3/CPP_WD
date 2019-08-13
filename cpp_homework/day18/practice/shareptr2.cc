// weak_ptr
#include <iostream>
#include <memory>
using namespace std;
// 先声明一下，不然不能在child中定义
class parent;
// child
class child
{
private:
public:
    // 构造函数
    child()
    {
        cout << "child()" << endl;
    }
    // 析构函数
    ~child()
    {
        cout << "~child()" << endl;
    }
    //放另外一个类的成员
    shared_ptr<parent> _pParent;

protected:
};
// parent
class parent
{
private:
public:
    // 构造函数
    parent()
    {
        cout << "parent()" << endl;
    }
    // 析构函数
    ~parent()
    {
        cout << "~parent()" << endl;
    }
    // child类的成员
    shared_ptr<child> _pChild;

protected:
};
// main
int main(void)
{
    // 指向对象的第一个指针
    shared_ptr<parent> pParent(new parent());
    shared_ptr<child> pChild(new child());
    // 指向对象的第二个指针
    pParent->_pChild = pChild;
    pChild->_pParent = pParent;

    cout << "pParent->_pChild -----> " << pParent->_pChild << endl;
    cout << "pChild->_pParent -----> " << pChild->_pParent << endl;
    // 此时2个对象的引用计数都是2
    cout << "-----------------------------" << endl;
    cout << "parent 引用计数 = " << pParent.use_count() << endl
         << "child  引用计数 = " << pChild.use_count() << endl;

    return 0;
}
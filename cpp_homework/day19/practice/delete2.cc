#include <iostream>
#include <assert.h>

using namespace std;

#define PTR_ASSERT(data) assert(data)
// PTR_ASSERT(m_ptr != NULL);  带参数的宏定义

template <class T>
struct defalute_deleter
{
    void defalute_deleter_method()
    {
        cout << "void defalute_deleter_method()" << endl;
    }
    void operator()(T *ptr)
    {
        if (ptr != NULL)
        {
            cout << "void operator()(T *ptr)" << endl;
            delete ptr;
            ptr = NULL;
        }
    }
};

template <typename T, typename deleter = defalute_deleter<T>>
class unique_ptr
{
public:
    // explicit 关键字，不可在隐式转换中存在
    explicit unique_ptr(T *ptr = NULL);
    // 构造函数
    unique_ptr(T *ptr, deleter d);
    // 析构函数
    ~unique_ptr();
    // ------------------成员函数--------------------
    // 返回值为T*类型的函数
    T *get();
    // reset
    void reset(T *ptr = NULL);
    // getdelete
    deleter &getDeleter();
    // relrase
    T *release();

public:
    // 重载
    T &operator*();
    T *operator->();
    operator bool() const;

private:
    unique_ptr(unique_ptr &up);
    unique_ptr &operator=(unique_ptr &up);

private:
    T *m_ptr;

    deleter m_deleter;
};

template <typename T, typename deleter>
unique_ptr<T, deleter>::unique_ptr(T *ptr /* = NULL */, deleter d)
{
    if (ptr != NULL)
    {
        m_ptr = ptr;
        m_deleter = d;
    }
}

template <typename T, typename deleter>
unique_ptr<T, deleter>::unique_ptr(T *ptr /* = NULL */)
{
    if (ptr != NULL)
    {
        m_ptr = ptr;
    }
}

template <typename T, typename deleter>
unique_ptr<T, deleter>::~unique_ptr()
{
    if (m_ptr != NULL)
    {
        m_deleter(m_ptr);
        m_ptr = NULL;
    }
}

template <typename T, typename deleter>
T &unique_ptr<T, deleter>::operator*()
{
    PTR_ASSERT(m_ptr != NULL);
    return *m_ptr;
}

template <class T, class deleter>
T *unique_ptr<T, deleter>::operator->()
{
    PTR_ASSERT(m_ptr != NULL);

    return m_ptr;
}

template <typename T, typename deleter>
T *unique_ptr<T, deleter>::get()
{
    return m_ptr;
}

template <typename T, typename deleter>
void unique_ptr<T, deleter>::reset(T *ptr)
{
    T *old_ptr = m_ptr;
    m_ptr = ptr;

    if (old_ptr != NULL)
    {
        m_deleter(old_ptr);
        old_ptr = NULL;
    }
}

template <typename T, typename deleter>
deleter &unique_ptr<T, deleter>::getDeleter()
{
    return m_deleter;
}

template <typename T, typename deleter>
T *unique_ptr<T, deleter>::release()
{
    T *pTemp = m_ptr;
    m_ptr = NULL;

    return pTemp;
}

template <typename T, typename deleter>
unique_ptr<T, deleter>::operator bool() const
{
    return m_ptr != NULL;
}

//Test class
class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }

    void method()
    {
        cout << "void method()" << endl;
    }
};

//custom deleter
template <class T>
struct custom_deleter
{
    void deleter_method()
    {
        cout << " void deleter_method()" << endl;
    }

    void operator()(T *ptr)
    {
        cout << "void operator()(T *ptr) " << endl;
        delete ptr;
        ptr = NULL;
    }
};

// main
int main()
{
    //default deleter
    cout << "=======default deleter====interface test begin: ========== " << endl;
    unique_ptr<Test> up(new Test());

    cout << "operator ->  ---->";
    up->method();

    cout << "operator * ----->";
    (*up).method();

    cout << "operator bool -------> ";
    if (up)
    {
        cout << "obj is exit" << endl;
    }

    cout << "get ------> ";
    up.get()->method();

    cout << "getDeleter -------> ";
    defalute_deleter<Test> del = up.getDeleter();
    del.defalute_deleter_method();

    cout << "release -------> ";
    unique_ptr<Test> up1(up.release());

    //if take this,  will die
    //(*up).method();

    cout << "reset --------> ";
    up1.reset();

    //Custom deleter
    cout << "=======Custom deleter====interface test begin: ========== " << endl;
    custom_deleter<Test> d;
    unique_ptr<Test, custom_deleter<Test>> up_custom_dele(new Test(), d);

    cout << "operator ----->: ";
    up_custom_dele->method();

    cout << "operator * ------> ";
    (*up_custom_dele).method();

    cout << "operator bool -------> ";
    if (up_custom_dele)
    {
        cout << "obj is exit" << endl;
    }

    cout << "get ------> ";
    up_custom_dele.get()->method();

    cout << "getDeleter -------> ";
    custom_deleter<Test> custom_del = up_custom_dele.getDeleter();
    custom_del.deleter_method();

    cout << "release ------> ";
    unique_ptr<Test> up3(up_custom_dele.release());

    //if take this,  will die
    //(*up_custom_dele).method();

    cout << "reset: " << endl;
    up3.reset();

    return 0;
}
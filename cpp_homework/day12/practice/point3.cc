#ifndef MAGIC_SINGLETON_H
#define MAGIC_SINGLETON_H

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Magic_Singleton
{
public:
    //获取全局单例对象
    template <typename... Args>
    static std::shared_ptr<T> GetInstance(Args &&... args)
    {
        if (!_pSington)
        {
            if (nullptr == _pSington)
            {
                _pSington = std::make_shared<T>(std::forward<Args>(args)...);
                // _pSington = new T;
            }
        }
        return _pSington;
    }

    static void Destory()
    {
        if (_pSington)
        {
            _pSington.reset();
            _pSington = nullptr;
            // delete [] _pSington;
        }
    }

private:
    explicit Magic_Singleton();
    Magic_Singleton(const Magic_Singleton &) = delete;
    Magic_Singleton &operator=(const Magic_Singleton &) = delete;
    ~Magic_Singleton();

private:
    static std::shared_ptr<T> _pSington;
};

template <typename T>
std::shared_ptr<T> Magic_Singleton<T>::_pSington = nullptr;

#endif

class computer
{
public:
    computer(const string &strData)
        : _strData(strData)
    {
        cout << _strData.data() << endl;
    };
    ~computer()
    {
        cout << " ~computer()" << endl;
    };

private:
    string _strData;
};

int main(void)
{
    computer com = Magic_Singleton<computer>::GetInstance("xiaomi");
    Magic_Singleton<computer>::Destory();
    return 0;
}
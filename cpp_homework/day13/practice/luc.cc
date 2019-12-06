#include <bits/stdc++.h>
using namespace std;
// 1.	获取数据 get 和 写入数据 putD
// 2.	获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1
// 3.	写入数据 putD(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

class LRUCache
{
public:
    // 构造函数
    LRUCache(int capacity)
        : _cap(capacity)
    {
        cout << "LRUCache(int capacity) " << endl;
    }
    // 查找成功，移动到头部
    // O(1)
    // hash 查找，如果找到了，就把 list 中的节点接下来移到头部
    int get(int key)
    {
        auto it = _m.find(key);
        if (it == _m.end())
        {
            // 查找失败
            return -1;
        }
        // 查找成功
        int val = it->second->second;
        cout << "---------------val " << val << endl;
        // 删除查到元素的下一个元素
        _list.erase(it->second);
        // 将后面紧接着一个元素移动到头部
        _list.push_front(make_pair(key, val));
        _m[key] = _list.begin();
        return it->second->second;
    }

    // 先查找旧 key 是否存在，如果存在，将节点移动到首部。
    // 如果不存在，插入新节点。--相当于更新veluad的值
    // 如果容量超限，删除使用频率最少的节点。
    void put(int key, int value)
    {
        // 查找
        auto it = _m.find(key);
        if (it != _m.end())
        {
            _list.erase(it->second);
        }
        // 头部添加节点
        _list.push_front(make_pair(key, value));
        _m[key] = _list.begin();
        if (_list.size() > _cap)
        {
            int key = _list.back().first;
            _m.erase(key);
            _list.pop_back(); //删除容器中最后一个元素，并改变容器的大小
        }
    }

private:
    unordered_map<int, list<pair<int, int>>::iterator> _m;
    // 新节点或刚访问的节点插入表头，因为表头指针可以通过 begin 很方便的获取到。
    list<pair<int, int>> _list;
    int _cap;
};

// test
int main(void)
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);    // 返回  1
    cache.put(3, 3); // 该操作，会将 key 2 作废
    cache.get(2);    // 返回 -1 (结果不存在)
    cache.put(4, 4); // 该操作，会将 key 1 作废
    cache.get(1);    // 返回 -1 (结果不存在)
    cache.get(3);    // 返回  3
    cache.get(4);    // 返回  4
    return 0;
}
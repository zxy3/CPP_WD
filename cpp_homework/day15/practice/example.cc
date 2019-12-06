#include <bits/stdc++.h>
using namespace std;

template <typename Tp>
class Vector
{
public:
    Vector()
        : _elems(NULL), _first_free(NULL), _end(NULL)
    {
    }

    ~Vector()
    {
        if (_elems)
        {
            while (_elems != _first_free)
                _alloc.destroy(--_first_free);
            _alloc.deallocate(_elems, capacity());
        }
    }

    void push_back(const Tp &value)
    {
        if (size() == capacity())
        {
            reallocate();
        }
        _alloc.construct(_first_free++, value);
    }
    void pop_back()
    {
        if (size() > 0)
        {
            _alloc.destory(--_first_free);
        }
    }
    size_t size() const
    {
        return _first_free - _elems;
    }
    size_t capacity() const
    {
        return _end - _elems;
    }
    Tp &operator[](size_t idx)
    {
        return _elems[idx];
    }

private:
    void reallocate()
    {
        size_t oldCapacity = capacity();
        size_t newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

        Tp *newElems = _alloc.allocate(newCapacity);
        if (_elems)
        {
            std::uninitialized_copy(_elems, _first_free, newElems);
            while (_elems != _first_free)
                _alloc.destroy(--_first_free);
            _alloc.deallocate(_elems, oldCapacity);
        }
        _elems = newElems;
        _first_free = _elems + oldCapacity;
        _end = _elems + newCapacity;
    }

private:
    static std::allocator<Tp> _alloc;
    Tp *_elems;
    Tp *_first_free;
    Tp *_end;
};

template <typename Tp>
std::allocator<Tp> Vector<Tp>::_alloc;

void display(Vector<int> &vec)
{
    cout << "vec's size = " << vec.size() << endl;
    cout << "vec's capacity = " << vec.capacity() << endl;
}
// test
void test(void)
{
    Vector<int> vecInt;
    display(vecInt);

    vecInt.push_back(1);
    display(vecInt);
    vecInt.push_back(2);
    display(vecInt);
    vecInt.push_back(3);
    display(vecInt);

    for (auto idx = 0; idx != vecInt.size(); ++idx)
    {
        cout << vecInt[idx] << " ";
    }
    cout << endl;
}
// main
int main(void)
{
    test();
    return 0;
}
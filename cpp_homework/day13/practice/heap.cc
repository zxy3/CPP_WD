#include <iostream>
using namespace std;
#define SWAP(auto &num1, auto &num2) \
    {                                \
        auto temp = num1;            \
        num1 = num2;                 \
        num2 = temp                  \
    }
// int Swap(int &a, int &b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }

template <class Iterator>
void Heap_build(Iterator a[], Iterator root, Iterator len)
{
    auto lchild = root * 2 + 1;
    if (lchild < len)
    {
        auto flag = lchild;
        auto rchild = lchild + 1;
        if (rchild < lchild)
        {
            if (a[rchild] > a[flag])
            {
                flag = rchild;
            }
        }
        if (a[root] < a[flag])
        {
            SWAP(a[root], a[flag]);
            Heap_build(a, flag, length);
        }
    }
}
// void Heap_build(int a[], int root, int length)
// {
//     int lchild = root * 2 + 1;
//     if (lchild < length)
//     {
//         int flag = lchild;
//         int rchild = lchild + 1;
//         if (rchild < length)
//         {
//             if (a[rchild] > a[flag])
//             {
//                 flag = rchild;
//             }
//         }
//         if (a[root] < a[flag])
//         {
//             Swap(a[root], a[flag]);
//             Heap_build(a, flag, length);
//         }
//     }
// }
void Heap_sort(int a[], int len)
{
    for (int i = len / 2 - 1, i >= 0; i--) //从最后一个非叶子节点的父节点开始建堆
    {
        Heap_build(a, i, len);
    }
    for (int j = len - 1; j > 0; j--)
    {
        SWAP(a[0], a[j]);
        Heap_build(a, 0, j);
    }
}
// test
int main(void)
{

    return 0;
}

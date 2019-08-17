#pragma once

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}

	Noncopyable(const Noncopyable &) = delete;
	Noncopyable &operator=(const Noncopyable &) = delete;
};

} //end of namespace wd

// ------------------笔记---------------------
//explicit //禁止隐式（转换）调用禁止隐式（转换）调用
//对于const数据成员，只能放在初始化表达式中
//进行初始化
//explicit
//Point(int ix = 0, int iy = 0)
//对于引用数据成员，只能放在初始化表达式中
//进行初始化
//explicit
//Point(int ix = 0, int iy = 0)
//: _ix(ix)
//, _iy(iy)
//, _ref(_ix)
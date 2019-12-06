///
/// @file    Noncopyable.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 10:11:31
///

#pragma once

namespace wd
{

class Noncopyable
{
	// 定义了protected方法的类，叫抽象类
protected:
	Noncopyable() {}
	~Noncopyable() {}
	// 成员函数
	Noncopyable(const Noncopyable &) = delete;
	Noncopyable &operator=(const Noncopyable &) = delete;
};

} //end of namespace wd

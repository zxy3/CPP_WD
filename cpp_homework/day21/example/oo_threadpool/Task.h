///
/// @file    Task.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-07-15 15:06:36
///

//  任务接口
#pragma once

namespace wd
{

class Task
{
public:
	virtual void process() = 0;
	// 析构函数也要是虚函数
	virtual ~Task() {}
};

} //end of namespace wd

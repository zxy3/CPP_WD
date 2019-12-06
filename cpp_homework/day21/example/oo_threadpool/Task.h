//任务接口
#pragma once
// 保证头文件只被编译一次
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

 ///
 /// @file    Mylogger.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-29 09:39:27
 ///
 
#pragma once

#include <log4cpp/Category.hh>

using namespace log4cpp;

namespace wd
{

class Mylogger
{
public:
	static Mylogger * getInstance();
	static void destroy();

	void error(const char * msg);

	template <typename T,typename... Args>
	void error(T t,Args... args);

	

	void warn(const char * msg);
	void info(const char * msg);
	void debug(const char * msg);

private:
	Mylogger();
	~Mylogger();

private:
	static Mylogger * _pInstance;
	Category & _mycategory;
};

#define prefix(msg)	string("[").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(std::to_string(__LINE__))\
		.append("] ").append(msg)



}//end of namespace wd


#include "Mylogger.cc"
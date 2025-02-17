#pragma once

#define DECLARE_SINGLE(classname)							\
public:														\
	static classname& GetInstance()							\
	{														\
		static classname s_instance = new classname();		\
		return *s_instance;									\
	}														\
private:													\
	classname() {}											

#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr)					\
	if (ptr)								\
	{										\
		delete ptr;							\
		ptr = nullptr;						\
	}
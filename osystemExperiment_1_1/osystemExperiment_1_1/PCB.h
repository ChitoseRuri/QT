#pragma once
#if defined(DEBUG) | defined(_DEBUG)
#define _NOEXCEPT_IN_RELEASE_
#else
#define NDEBUG
#define _NOEXCEPT_IN_RELEASE_ noexcept
#endif

#define _In
#define _Out
#include <string>
#include <assert.h>

class PCB
{
public:
	enum class Status
	{
		NotNow,
		Run,
		Wait,
		Finish
	};

//私有成员定义
private:
	std::string m_Name;//进程名称
	unsigned m_ReachTime;//进程到达时间
	unsigned m_TotalTime;//进程需要工作的时间
	unsigned m_WorkTime;//进程已经被CPU工作的时间
	Status m_Status;//进程状态
public:
	static std::string StatusToString(Status status) noexcept;
	std::string StatusToString() noexcept;

public:
	PCB(std::string name, unsigned reachTime, unsigned totalTimee);
	~PCB();
	//设置进程状态
	void SetStatus(Status status) noexcept;
	//获取进程状态
	const Status & GetStatus() noexcept;
	//获取进程到达时间
	unsigned GetReachTime() noexcept;
	//获取线程总共需要完成的时间
	unsigned GetTotalTime() noexcept;
	//获取线程已经运行的时间
	unsigned GetWorkTime() noexcept;
	//获取线程名称
	const std::string & GetName() noexcept;
	//更新进程
	unsigned Update(unsigned interval) _NOEXCEPT_IN_RELEASE_;
};

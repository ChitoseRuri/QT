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

class JCB
{
public:
	enum class Status
	{
		Wait,
		Run,
		Ready,
		Finish
	};

//私有成员定义
private:
	std::string m_Name;//进程名称
	unsigned m_ReachTime;//进程到达时间
	unsigned m_TotalTime;//进程需要工作的时间
	unsigned m_WorkTime;//进程已经被CPU工作的时间
	unsigned m_MarkTime;//进程就绪的时间点
	unsigned m_FinishTime;//进程完成的时间点
	unsigned m_CurrentTime;
	unsigned m_Flag;

	Status m_Status;//进程状态
public:
	static std::string StatusToString(Status status) noexcept;
	std::string StatusToString() noexcept;

public:
	JCB(std::string name, unsigned reachTime, unsigned totalTimee);
	~JCB();
	//设置进程状态
	void setStatus(Status status) noexcept;
	//获取进程状态
	const Status & getStatus() const noexcept;
	//设置进程就绪的时间点
	void setMarkTime(unsigned time) noexcept;
	//设置进程完成的时间点
	void setFinishTime(unsigned time) noexcept;
	//增加周转时间
	void addCurrentTime(unsigned time) noexcept;
	//获取周转时间
	const unsigned & getCurrentTime() const noexcept;
	//获取进程到达时间
	unsigned getReachTime() const noexcept;
	//获取线程总共需要完成的时间
	unsigned getTotalTime() const noexcept;
	//获取线程已经运行的时间
	unsigned getWorkTime() const noexcept;
	//获取线程名称
	const std::string & getName() const noexcept;

	void setFlag(unsigned flag) noexcept;
	const unsigned & getFlag() const noexcept;
	//更新进程
	unsigned Update(unsigned interval) _NOEXCEPT_IN_RELEASE_;
};

#include "JCB.h"
using std::string;

std::string JCB::StatusToString(Status status) noexcept
{
	switch (status)
	{
	case JCB::Status::Wait:return string("Wait");break;
	case JCB::Status::Run:return string("Run");break;
	case JCB::Status::Finish:return string("Finish");break;
	case JCB::Status::Ready:return string("Ready"); break;
	default:return string("Bug"); break;
	}
}

std::string JCB::StatusToString() noexcept
{
	switch (m_Status)
	{
	case JCB::Status::Wait:return string("Wait"); break;
	case JCB::Status::Run:return string("Run"); break;
	case JCB::Status::Finish:return string("Finish"); break;
	case JCB::Status::Ready:return string("Ready"); break;
	default:return string("Bug"); break;
	}
}

JCB::JCB(std::string name, unsigned reachTime, unsigned totalTime):
	m_Name(name),
	m_ReachTime(reachTime),
	m_TotalTime(totalTime),
	m_WorkTime(0),
	m_FinishTime(0),
	m_MarkTime(0),
	m_Status(Status::Wait),
	m_CurrentTime(0)
{
}

JCB::~JCB()
{
}

void JCB::setStatus(Status status) noexcept
{
	m_Status = status;
}

const JCB::Status & JCB::getStatus() const noexcept
{
	return m_Status;
}

void JCB::setMarkTime(unsigned time) noexcept
{
	m_MarkTime = time;
}

void JCB::setFinishTime(unsigned time) noexcept
{
	assert(time > m_MarkTime);
	m_FinishTime = time;
}

void JCB::addCurrentTime(unsigned time) noexcept
{
	m_CurrentTime += time;
}

const unsigned & JCB::getCurrentTime() const noexcept
{
	return m_CurrentTime;
}

unsigned JCB::getReachTime() const noexcept
{
	return m_ReachTime;
}

unsigned JCB::getTotalTime() const noexcept
{
	return m_TotalTime;
}

unsigned JCB::getWorkTime() const noexcept
{
	return m_WorkTime;
}

const std::string & JCB::getName() const noexcept
{
	return m_Name;
}

void JCB::setFlag(unsigned flag) noexcept
{
	m_Flag = flag;
}

const unsigned & JCB::getFlag() const noexcept
{
	return m_Flag;
}

unsigned JCB::Update(unsigned interval) _NOEXCEPT_IN_RELEASE_
{
	assert(m_Status == Status::Run);//调用这个函数的时候必然是运行状态
	m_WorkTime += interval;
	if (m_WorkTime >= m_TotalTime)//表示该次循环内运行完成，把剩余时间吐出来
	{
		m_Status = Status::Finish;
		m_WorkTime = m_TotalTime;
		addCurrentTime(m_TotalTime);
		return  m_WorkTime - m_TotalTime;
	}
	return 0;
}

#include "PCB.h"
using std::string;

std::string PCB::StatusToString(Status status) noexcept
{
	switch (status)
	{
	case PCB::Status::NotNow:return string("NotNow");break;
	case PCB::Status::Run:return string("Run");break;
	case PCB::Status::Finish:return string("Finish");break;
	case PCB::Status::Wait:return string("Wait"); break;
	default:return string("Bug"); break;
	}
}

std::string PCB::StatusToString() noexcept
{
	switch (m_Status)
	{
	case PCB::Status::NotNow:return string("NotNow"); break;
	case PCB::Status::Run:return string("Run"); break;
	case PCB::Status::Finish:return string("Finish"); break;
	case PCB::Status::Wait:return string("Wait"); break;
	default:return string("Bug"); break;
	}
}

PCB::PCB(std::string name, unsigned reachTime, unsigned totalTime):
	m_Name(name),
	m_ReachTime(reachTime),
	m_TotalTime(totalTime),
	m_WorkTime(0),
	m_Status(Status::NotNow)
{
}

PCB::~PCB()
{
}

void PCB::SetStatus(Status status) noexcept
{
	m_Status = status;
}

const PCB::Status & PCB::GetStatus() noexcept
{
	return m_Status;
}

unsigned PCB::GetReachTime() noexcept
{
	return m_ReachTime;
}

unsigned PCB::GetTotalTime() noexcept
{
	return m_TotalTime;
}

unsigned PCB::GetWorkTime() noexcept
{
	return m_WorkTime;
}

const std::string & PCB::GetName() noexcept
{
	return m_Name;
}

unsigned PCB::Update(unsigned interval) _NOEXCEPT_IN_RELEASE_
{
	assert(m_Status == Status::Run);//�������������ʱ���Ȼ������״̬
	m_WorkTime += interval;
	if (m_WorkTime > m_TotalTime)//��ʾ�ô�ѭ����������ɣ���ʣ��ʱ���³���
	{
		m_Status = Status::Finish;
		m_WorkTime = m_TotalTime;
		return  m_WorkTime - m_TotalTime;
	}
	return 0;
}

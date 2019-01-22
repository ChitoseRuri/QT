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

//˽�г�Ա����
private:
	std::string m_Name;//��������
	unsigned m_ReachTime;//���̵���ʱ��
	unsigned m_TotalTime;//������Ҫ������ʱ��
	unsigned m_WorkTime;//�����Ѿ���CPU������ʱ��
	Status m_Status;//����״̬
public:
	static std::string StatusToString(Status status) noexcept;
	std::string StatusToString() noexcept;

public:
	PCB(std::string name, unsigned reachTime, unsigned totalTimee);
	~PCB();
	//���ý���״̬
	void SetStatus(Status status) noexcept;
	//��ȡ����״̬
	const Status & GetStatus() noexcept;
	//��ȡ���̵���ʱ��
	unsigned GetReachTime() noexcept;
	//��ȡ�߳��ܹ���Ҫ��ɵ�ʱ��
	unsigned GetTotalTime() noexcept;
	//��ȡ�߳��Ѿ����е�ʱ��
	unsigned GetWorkTime() noexcept;
	//��ȡ�߳�����
	const std::string & GetName() noexcept;
	//���½���
	unsigned Update(unsigned interval) _NOEXCEPT_IN_RELEASE_;
};

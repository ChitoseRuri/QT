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

//˽�г�Ա����
private:
	std::string m_Name;//��������
	unsigned m_ReachTime;//���̵���ʱ��
	unsigned m_TotalTime;//������Ҫ������ʱ��
	unsigned m_WorkTime;//�����Ѿ���CPU������ʱ��
	unsigned m_MarkTime;//���̾�����ʱ���
	unsigned m_FinishTime;//������ɵ�ʱ���
	unsigned m_CurrentTime;
	unsigned m_Flag;

	Status m_Status;//����״̬
public:
	static std::string StatusToString(Status status) noexcept;
	std::string StatusToString() noexcept;

public:
	JCB(std::string name, unsigned reachTime, unsigned totalTimee);
	~JCB();
	//���ý���״̬
	void setStatus(Status status) noexcept;
	//��ȡ����״̬
	const Status & getStatus() const noexcept;
	//���ý��̾�����ʱ���
	void setMarkTime(unsigned time) noexcept;
	//���ý�����ɵ�ʱ���
	void setFinishTime(unsigned time) noexcept;
	//������תʱ��
	void addCurrentTime(unsigned time) noexcept;
	//��ȡ��תʱ��
	const unsigned & getCurrentTime() const noexcept;
	//��ȡ���̵���ʱ��
	unsigned getReachTime() const noexcept;
	//��ȡ�߳��ܹ���Ҫ��ɵ�ʱ��
	unsigned getTotalTime() const noexcept;
	//��ȡ�߳��Ѿ����е�ʱ��
	unsigned getWorkTime() const noexcept;
	//��ȡ�߳�����
	const std::string & getName() const noexcept;

	void setFlag(unsigned flag) noexcept;
	const unsigned & getFlag() const noexcept;
	//���½���
	unsigned Update(unsigned interval) _NOEXCEPT_IN_RELEASE_;
};

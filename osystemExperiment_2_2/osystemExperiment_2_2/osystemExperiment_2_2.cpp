#include "osystemExperiment_2_2.h"
using std::string;

osystemExperiment_2_2::osystemExperiment_2_2(QWidget *parent)
	: QMainWindow(parent),
	m_Interval(21),//���ø��¼��
	m_JCBInsertIndex(0),
	m_TotalTime(0),
	m_pQTimer(new QTimer(this)),
	m_Weight(1)
{
	ui.setupUi(this);
	Initialize();
}

osystemExperiment_2_2::~osystemExperiment_2_2()
{
	for each (JCB * var in m_JCBs)
	{
		delete var;
	}
	delete m_pQTimer;
}

void osystemExperiment_2_2::Initialize()
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//�����������
	{
		string name("Process_");//��ʱ����
		for (int i = 0; i < 5; i++)
		{
			m_JCBs.emplace_back(new JCB(name + std::to_string(i), qrand() % 20000, qrand() % 8000));//��ʼ��������Ϣ
		}
	}
	//���ݵ���ʱ���������
	std::sort(m_JCBs.begin(), m_JCBs.end(),
		[](JCB * pLeft, JCB * pRight) {return pLeft->getReachTime() < pRight->getReachTime(); });
	for (int i = 0; i < 5; i++)
	{
		m_JCBs[i]->setFlag(i);
	}
	//��ui�������ʾ��label����һ�������޸�
	m_JCBLabels = std::vector<JCB_Label>{
		JCB_Label(ui.label_name_1, ui.label_progressStatus_1, ui.label_reachTime_1, ui.label_totalTime_1,
		ui.label_workTime_1,ui.label_currentTime_1,ui.label_currentTimeWithWeight_1),
		JCB_Label(ui.label_name_2, ui.label_progressStatus_2, ui.label_reachTime_2, ui.label_totalTime_2, 
			ui.label_workTime_2, ui.label_currentTime_2, ui.label_currentTimeWithWeight_2),
		JCB_Label(ui.label_name_3, ui.label_progressStatus_3, ui.label_reachTime_3, ui.label_totalTime_3, 
		ui.label_workTime_3,ui.label_currentTime_3,ui.label_currentTimeWithWeight_3),
		JCB_Label(ui.label_name_4, ui.label_progressStatus_4, ui.label_reachTime_4, ui.label_totalTime_4, 
		ui.label_workTime_4,ui.label_currentTime_4,ui.label_currentTimeWithWeight_4),
		JCB_Label(ui.label_name_5, ui.label_progressStatus_5, ui.label_reachTime_5, ui.label_totalTime_5, 
		ui.label_workTime_5,ui.label_currentTime_5,ui.label_currentTimeWithWeight_5)
	};
	//�ѽ������ơ�����ʱ�䡢��Ҫ����ʱ�����Label
	for (int iIndex = 0; iIndex < 5; iIndex++)
	{
		m_JCBLabels[iIndex].name->setText(QString::fromStdString(m_JCBs[iIndex]->getName()));
		m_JCBLabels[iIndex].reachTime->setText(QString::number(m_JCBs[iIndex]->getReachTime()));
		m_JCBLabels[iIndex].totalTime->setText(QString::number(m_JCBs[iIndex]->getTotalTime()));
		m_JCBLabels[iIndex].workTime->setText(QString::number(0));
		m_JCBLabels[iIndex].progressStatus->setText(QString("Wait"));
	}
	connect(m_pQTimer, SIGNAL(timeout()), this, SLOT(UpdateLabel()));
	m_LastTime = timeGetTime();
	m_pQTimer->start(m_Interval);//�趨����ʱ�䲢��ʼ
}

void osystemExperiment_2_2::UpdateLabel()
{
	unsigned temp = timeGetTime();
	unsigned interval = temp - m_LastTime;
	m_LastTime = temp;
	unsigned leftTime = 0;
	unsigned lastTime = 0;
	m_TotalTime += interval;
	while (true)
	{
		if (m_JCBInsertIndex < m_JCBs.size() && m_JCBs[m_JCBInsertIndex]->getReachTime() < m_TotalTime)//�ж���û���½��̲���
		{
			leftTime =  m_JCBs[m_JCBInsertIndex]->getReachTime() - m_TotalTime - lastTime;//�еĻ��������ǰʣ��ʱ��
		}
		else
		{
			leftTime = interval - lastTime;
		}
		lastTime += leftTime;//����ε�ʱ�������ܺ�ʱ
		while (!m_WorkJCBs.empty() && leftTime)//��������б�Ϊ�ղ�����ʣ��ʱ��
		{
			auto temp = leftTime;
			leftTime = m_WorkJCBs[0]->Update(leftTime);//��ʣ��ʱ�������������еĽ��̣��õ�ʹ�ú��ʣ��ʱ��
			auto size = m_WorkJCBs.size();
			for (size_t index = 1; index < size; index++)
			{
				m_WorkJCBs[index]->addCurrentTime(temp - leftTime);
			}
			if (m_WorkJCBs[0]->getStatus() == JCB::Status::Finish)//���������֮�����״̬Ϊ���
			{
				//m_WorkJCBs[0]->setFinishTime(m_TotalTime - leftTime);
				const unsigned & index = m_WorkJCBs[0]->getFlag();
				m_JCBLabels[index].currentTime->setText(QString::number(m_WorkJCBs[0]->getCurrentTime()));
				m_JCBLabels[index].currentTimeWithWeight->setText(QString::number(m_Weight * m_WorkJCBs[0]->getCurrentTime()));
				m_WorkJCBs.erase(m_WorkJCBs.begin());//�Ѹý��̴ӹ����б��޳�
				m_Weight++;//Ȩֵ����
				if (!m_WorkJCBs.empty())
				{
					m_WorkJCBs[0]->setStatus(JCB::Status::Run);
				}
			}
		}
		if (lastTime == interval)//����ۻ�ʱ����������
		{
			break;
		}
		//��Ϊ��תҲ�����ۻ�ʱ�䣬�ۻ�ʱ�䲻����Ȼ���½��̲���
		m_JCBs[m_JCBInsertIndex]->setStatus(JCB::Status::Ready);
		m_WorkJCBs.push_back(m_JCBs[m_JCBInsertIndex++]);//�����½���
		if (m_WorkJCBs.size() > 1)
		{
			std::sort(m_WorkJCBs.begin() + 1, m_WorkJCBs.end(), [](JCB * pLeft, JCB * pRight) {
				return (pLeft->getCurrentTime() + pLeft->getTotalTime()) / pLeft->getTotalTime() >
					(pRight->getCurrentTime() + pRight->getTotalTime()) / pRight->getTotalTime(); });//����Ӧ������
		}
		m_WorkJCBs[0]->setStatus(JCB::Status::Run);
	}
	if (m_JCBInsertIndex == m_JCBs.size() && m_WorkJCBs.empty())
	{
		m_pQTimer->stop();
	}
	for (int iIndex = 0; iIndex < 5; iIndex++)
	{
		m_JCBLabels[iIndex].progressStatus->setText(QString::fromStdString(m_JCBs[iIndex]->StatusToString()));
		m_JCBLabels[iIndex].workTime->setText(QString::number(m_JCBs[iIndex]->getWorkTime()));
	}
}
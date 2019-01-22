#include "osystemExperiment_1_1.h"
using std::string;

osystemExperiment_1_1::osystemExperiment_1_1(QWidget *parent)
	: QMainWindow(parent),
	m_Interval(21),//设置更新间隔
	m_PCBInsertIndex(0),
	m_TotalTime(0),
	m_pQTimer(new QTimer(this))
{
	ui.setupUi(this);
	Initialize();
}

osystemExperiment_1_1::~osystemExperiment_1_1()
{
	for each (PCB * var in m_PCBs)
	{
		delete var;
	}
	delete m_pQTimer;
}

void osystemExperiment_1_1::Initialize()
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//填入随机种子
	{
		string name("Process_");//临时变量
		for (int i = 0; i < 5; i++)
		{
			m_PCBs.emplace_back(new PCB(name + std::to_string(i), qrand() % 20000, qrand() % 8000));//初始化进程信息
		}
	}
	//根据到达时间排序进程
	std::sort(m_PCBs.begin(), m_PCBs.end(),
		[](PCB * pLeft, PCB * pRight) {return pLeft->GetReachTime() < pRight->GetReachTime(); });
	//把ui里面的显示用label保存一份用于修改
	m_PCBLabels = std::vector<PCB_Label>{
		PCB_Label(ui.label_name_1, ui.label_progressStatus_1, ui.label_reachTime_1, ui.label_totalTime_1, ui.label_workTime_1),
		PCB_Label(ui.label_name_2, ui.label_progressStatus_2, ui.label_reachTime_2, ui.label_totalTime_2, ui.label_workTime_2),
		PCB_Label(ui.label_name_3, ui.label_progressStatus_3, ui.label_reachTime_3, ui.label_totalTime_3, ui.label_workTime_3),
		PCB_Label(ui.label_name_4, ui.label_progressStatus_4, ui.label_reachTime_4, ui.label_totalTime_4, ui.label_workTime_4),
		PCB_Label(ui.label_name_5, ui.label_progressStatus_5, ui.label_reachTime_5, ui.label_totalTime_5, ui.label_workTime_5)
	};
	//把进程名称、到达时间、需要的总时间填进Label
	for (int iIndex = 0; iIndex < 5; iIndex++)
	{
		m_PCBLabels[iIndex].name->setText(QString::fromStdString(m_PCBs[iIndex]->GetName()));
		m_PCBLabels[iIndex].reachTime->setText(QString::number(m_PCBs[iIndex]->GetReachTime()));
		m_PCBLabels[iIndex].totalTime->setText(QString::number(m_PCBs[iIndex]->GetTotalTime()));
		m_PCBLabels[iIndex].workTime->setText(QString::number(0));
		m_PCBLabels[iIndex].progressStatus->setText(QString("NotNow"));
	}
	connect(m_pQTimer, SIGNAL(timeout()), this, SLOT(UpdateLabel()));
	m_LastTime = timeGetTime();
	m_pQTimer->start(m_Interval);//设定更新时间并开始
}

void osystemExperiment_1_1::UpdateLabel()
{
	unsigned temp = timeGetTime();
	unsigned interval = temp - m_LastTime;
	m_TotalTime += interval;
	m_LastTime = temp;
	unsigned leftTime;
	unsigned lastTime = 0;
	while (true)
	{
		if (m_PCBInsertIndex < m_PCBs.size() && m_PCBs[m_PCBInsertIndex]->GetReachTime() < m_TotalTime)//判断有没有新进程插入
		{
			leftTime = m_Interval + m_PCBs[m_PCBInsertIndex]->GetReachTime() - m_TotalTime - lastTime;//有的话计算插入前剩余时间
		}
		else
		{
			leftTime = interval - lastTime;
		}
		lastTime += leftTime;//把这次的时间计算进总耗时
		while (!m_WorkPCBs.empty() && leftTime)//如果工作列表不为空并且有剩余时间
		{
			leftTime = m_WorkPCBs[0]->Update(leftTime);//把剩余时间用来更新现有的进程，得到使用后的剩余时间
			if (m_WorkPCBs[0]->GetStatus() == PCB::Status::Finish)//如果更新完之后进程状态为完成
			{
				m_WorkPCBs.erase(m_WorkPCBs.begin());//把该进程从工作列表剔除
				if (!m_WorkPCBs.empty())
				{
					m_WorkPCBs[0]->SetStatus(PCB::Status::Run);
				}
			}
		}
		if (lastTime == interval)//如果累积时间满，跳出
		{
			break;
		}
		//因为空转也加入累积时间，累积时间不满必然有新进程插入
		m_PCBs[m_PCBInsertIndex]->SetStatus(PCB::Status::Wait);
		m_WorkPCBs.push_back(m_PCBs[m_PCBInsertIndex++]);//插入新进程
		//m_WorkPCBs[0]->SetStatus(PCB::Status::Wait);
		if (m_WorkPCBs.size() > 1)
		{
			std::sort(m_WorkPCBs.begin() + 1, m_WorkPCBs.end(), [](PCB * pLeft, PCB * pRight) {
				return pLeft->GetTotalTime() < pRight->GetTotalTime(); });//排序
		}
		m_WorkPCBs[0]->SetStatus(PCB::Status::Run);
	}
	if (m_PCBInsertIndex == m_PCBs.size() && m_WorkPCBs.empty())
	{
		m_pQTimer->stop();
	}
	for (int iIndex = 0; iIndex < 5; iIndex++)
	{
		m_PCBLabels[iIndex].progressStatus->setText(QString::fromStdString(m_PCBs[iIndex]->StatusToString()));
		m_PCBLabels[iIndex].workTime->setText(QString::number(m_PCBs[iIndex]->GetWorkTime()));
	}
}

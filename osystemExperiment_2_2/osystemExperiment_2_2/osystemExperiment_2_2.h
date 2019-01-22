#pragma once

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <qtimezone.h>
#include <vector>
#include <Windows.h>
#include "ui_osystemExperiment_2_2.h"
#include "JCB.h"

#pragma comment( lib,"winmm.lib" )
class osystemExperiment_2_2 : public QMainWindow
{
	Q_OBJECT

private:
	//类内结构体，方便管理Label集合
	struct JCB_Label
	{
	public:
		QLabel * name;
		QLabel * progressStatus;
		QLabel * reachTime;
		QLabel * totalTime;
		QLabel * workTime;
		QLabel * currentTime;
		QLabel * currentTimeWithWeight;

	public:
		JCB_Label() {}
		JCB_Label(QLabel * tname, QLabel* tprogressStatus, QLabel*treachTime, QLabel*ttotalTime, 
			QLabel*tworktime, QLabel * tcurrentTime, QLabel * tctww) :
			name(tname), progressStatus(tprogressStatus), reachTime(treachTime), totalTime(ttotalTime),
			workTime(tworktime), currentTime(tcurrentTime), currentTimeWithWeight(tctww) {}
	};

private:
	Ui::osystemExperiment_2_2Class ui;
	QEventLoop m_QEventLoop;
	QTimer * m_pQTimer;
	std::vector<JCB *> m_JCBs;
	std::vector<JCB *> m_WorkJCBs;
	std::vector<JCB_Label>  m_JCBLabels;
	std::vector <JCB * > m_FinishJCB;
	unsigned m_Interval;//Label更新间隔
	unsigned m_JCBInsertIndex;//表示轮到第几个进程插入
	unsigned m_TotalTime;
	unsigned m_LastTime;
	unsigned m_Weight;//权重

public:
	osystemExperiment_2_2(QWidget *parent = Q_NULLPTR);
	~osystemExperiment_2_2();

signals:
	void Tess();

public slots:
	void UpdateLabel();

private:
	void Initialize();

};

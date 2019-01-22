#pragma once

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <qtimezone.h>
#include <vector>
#include <Windows.h>
#include "ui_osystemExperiment_1_1.h"
#include "PCB.h"

#pragma comment( lib,"winmm.lib" )
class osystemExperiment_1_1 : public QMainWindow
{
	Q_OBJECT

private:
	//类内结构体，方便管理Label集合
	struct PCB_Label
	{
	public:
		QLabel * name;
		QLabel * progressStatus;
		QLabel * reachTime;
		QLabel * totalTime;
		QLabel * workTime;

	public:
		PCB_Label() {}
		PCB_Label(QLabel * tname, QLabel* tprogressStatus, QLabel*treachTime, QLabel*ttotalTime, QLabel*tworktime) :
			name(tname), progressStatus(tprogressStatus), reachTime(treachTime), totalTime(ttotalTime), workTime(tworktime) {}
	};

private:
	Ui::osystemExperiment_1_1Class ui;
	QEventLoop m_QEventLoop;
	QTimer * m_pQTimer;
	std::vector<PCB *> m_PCBs;
	std::vector<PCB *> m_WorkPCBs;
	std::vector<PCB_Label>  m_PCBLabels;
	unsigned m_Interval;//Label更新间隔
	unsigned m_PCBInsertIndex;//表示轮到第几个进程插入
	unsigned m_TotalTime;
	unsigned m_LastTime;

public:
	osystemExperiment_1_1(QWidget *parent = Q_NULLPTR);
	~osystemExperiment_1_1();

signals:
	void Tess();

public slots:
	void UpdateLabel();

private:
	void Initialize();

};

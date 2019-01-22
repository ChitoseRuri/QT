#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Blade.h"
#include "Player.h"
#include "qtimer.h"
#include "qtimezone.h"

#define _ACTION_INTERVAL_ 15
#define _MOVE_TIMES_ 10

class Blade : public QMainWindow
{
	Q_OBJECT

public:
	Blade(QWidget *parent = Q_NULLPTR);
	~Blade();

private:
	inline void caculateMoveXY(const QWidget * begin, const QWidget * end) _NOEXCEPT_IN_RELEASE_;//计算两个控件之间的位置差
	inline void moveWidget(QWidget * target) _NOEXCEPT_IN_RELEASE_;//移动特效用按钮
	void roundStart() _NOEXCEPT_IN_RELEASE_;//每个回合开始
	inline void cardButton_click(size_t index) _NOEXCEPT_IN_RELEASE_;//卡牌按钮通用函数
	bool cardResult(const size_t & index) _NOEXCEPT_IN_RELEASE_;//处理卡牌使用的结果
	inline int checkResult() _NOEXCEPT_IN_RELEASE_;//检查出牌结果
	void gameEnd() _NOEXCEPT_IN_RELEASE_;//游戏结束

private slots:
	void gameStart() _NOEXCEPT_IN_RELEASE_;//游戏开始
	void initialCardAnime()_NOEXCEPT_IN_RELEASE_;//发牌动画
	void roundStartAnime()_NOEXCEPT_IN_RELEASE_;//第一轮掀牌动画
	void playerButton0()_NOEXCEPT_IN_RELEASE_;
	void playerButton1()_NOEXCEPT_IN_RELEASE_;
	void playerButton2()_NOEXCEPT_IN_RELEASE_;
	void playerButton3()_NOEXCEPT_IN_RELEASE_;
	void playerButton4()_NOEXCEPT_IN_RELEASE_;
	void playerButton5()_NOEXCEPT_IN_RELEASE_;
	void playerButton6()_NOEXCEPT_IN_RELEASE_;
	void playerButton7()_NOEXCEPT_IN_RELEASE_;
	void playerButton8()_NOEXCEPT_IN_RELEASE_;
	void playerButton9()_NOEXCEPT_IN_RELEASE_;


private:
	Ui::BladeClass ui;
	QPushButton ** m_Buttons[2];//卡牌按键
	QLabel * m_ScoreLabel[2];//分数显示
	QPushButton  * m_Library;//牌库
	QPushButton * m_LastCard[2];//上一张卡
	QPushButton * m_ActCard;//用于特效的卡
	Player m_Player[2];
	QTimer m_Timer1;
	
	//
	int m_Turn;
	int m_Count[3];
	int m_Times;
	int m_MoveX, m_MoveY;
	QRect m_Rect;

};

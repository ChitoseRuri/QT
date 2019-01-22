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
	inline void caculateMoveXY(const QWidget * begin, const QWidget * end) _NOEXCEPT_IN_RELEASE_;//���������ؼ�֮���λ�ò�
	inline void moveWidget(QWidget * target) _NOEXCEPT_IN_RELEASE_;//�ƶ���Ч�ð�ť
	void roundStart() _NOEXCEPT_IN_RELEASE_;//ÿ���غϿ�ʼ
	inline void cardButton_click(size_t index) _NOEXCEPT_IN_RELEASE_;//���ư�ťͨ�ú���
	bool cardResult(const size_t & index) _NOEXCEPT_IN_RELEASE_;//������ʹ�õĽ��
	inline int checkResult() _NOEXCEPT_IN_RELEASE_;//�����ƽ��
	void gameEnd() _NOEXCEPT_IN_RELEASE_;//��Ϸ����

private slots:
	void gameStart() _NOEXCEPT_IN_RELEASE_;//��Ϸ��ʼ
	void initialCardAnime()_NOEXCEPT_IN_RELEASE_;//���ƶ���
	void roundStartAnime()_NOEXCEPT_IN_RELEASE_;//��һ�����ƶ���
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
	QPushButton ** m_Buttons[2];//���ư���
	QLabel * m_ScoreLabel[2];//������ʾ
	QPushButton  * m_Library;//�ƿ�
	QPushButton * m_LastCard[2];//��һ�ſ�
	QPushButton * m_ActCard;//������Ч�Ŀ�
	Player m_Player[2];
	QTimer m_Timer1;
	
	//
	int m_Turn;
	int m_Count[3];
	int m_Times;
	int m_MoveX, m_MoveY;
	QRect m_Rect;

};

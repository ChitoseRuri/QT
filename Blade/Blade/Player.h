#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Blade.h"
#include "qtimer.h"
#include "qtimezone.h"
#include "Card.h"
#include <vector>

struct CardButton
{
	QPushButton* button;
	Card card;
};

class Player:public QMainWindow
{
private:
	int m_Score;//�÷�
	int m_CardCount;//ʣ�࿨������
	CardButton* m_Cards;
	QLabel * m_ScoreLabel;
	CardButton m_LastCard;
	QTimer m_Timer;//˽�˼�ʱ��
	bool m_IsPlayer;//��ť�����Ƿ���濨�����ͱ仯
	
private:
	void setCard(const size_t & index, const Card::Type type) _NOEXCEPT_IN_RELEASE_;

public:
	Player();
	~Player();
	void initialize(QPushButton** & buttons, QPushButton * & lastCard, QLabel * & score, bool isAutoText) _NOEXCEPT_IN_RELEASE_;//��ʼ����ҿ���
	void setFirstCard(const size_t index,const Card::Type type) _NOEXCEPT_IN_RELEASE_;//��ʼ��һ�غϣ���ϵͳ�������һ�ŵõ�����
	void addScore(int score) _NOEXCEPT_IN_RELEASE_;
	void setScore(int score) _NOEXCEPT_IN_RELEASE_;
	const int & getScore() const _NOEXCEPT_IN_RELEASE_;
	size_t comTurn();//�ֵ����Գ�����
	Card::Type useCard(size_t index) _NOEXCEPT_IN_RELEASE_;
	bool isNoneCard() const _NOEXCEPT_IN_RELEASE_;
	bool isLastCardDestoryed() const _NOEXCEPT_IN_RELEASE_;
	void destoryLastCard() _NOEXCEPT_IN_RELEASE_;
	void setLastCard(Card::Type type) _NOEXCEPT_IN_RELEASE_;
	Card::Type getLastCard() const _NOEXCEPT_IN_RELEASE_;
	void recoverLastCard() _NOEXCEPT_IN_RELEASE_;
};
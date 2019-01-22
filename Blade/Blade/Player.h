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
	int m_Score;//得分
	int m_CardCount;//剩余卡牌数量
	CardButton* m_Cards;
	QLabel * m_ScoreLabel;
	CardButton m_LastCard;
	QTimer m_Timer;//私人计时器
	bool m_IsPlayer;//按钮文字是否跟随卡牌类型变化
	
private:
	void setCard(const size_t & index, const Card::Type type) _NOEXCEPT_IN_RELEASE_;

public:
	Player();
	~Player();
	void initialize(QPushButton** & buttons, QPushButton * & lastCard, QLabel * & score, bool isAutoText) _NOEXCEPT_IN_RELEASE_;//初始化玩家控制
	void setFirstCard(const size_t index,const Card::Type type) _NOEXCEPT_IN_RELEASE_;//开始第一回合，即系统发给你第一张得到的牌
	void addScore(int score) _NOEXCEPT_IN_RELEASE_;
	void setScore(int score) _NOEXCEPT_IN_RELEASE_;
	const int & getScore() const _NOEXCEPT_IN_RELEASE_;
	size_t comTurn();//轮到电脑出牌了
	Card::Type useCard(size_t index) _NOEXCEPT_IN_RELEASE_;
	bool isNoneCard() const _NOEXCEPT_IN_RELEASE_;
	bool isLastCardDestoryed() const _NOEXCEPT_IN_RELEASE_;
	void destoryLastCard() _NOEXCEPT_IN_RELEASE_;
	void setLastCard(Card::Type type) _NOEXCEPT_IN_RELEASE_;
	Card::Type getLastCard() const _NOEXCEPT_IN_RELEASE_;
	void recoverLastCard() _NOEXCEPT_IN_RELEASE_;
};
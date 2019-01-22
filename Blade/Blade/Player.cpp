#include "Player.h"
Player::Player():
	m_Cards(nullptr),
	m_CardCount(10),
	m_Score(0)
{
}

void Player::addScore(int score) _NOEXCEPT_IN_RELEASE_
{
	m_Score += score;
	m_ScoreLabel->setText(QString::number(m_Score));
}

void Player::setScore(int score) _NOEXCEPT_IN_RELEASE_
{
	m_Score = score;
	m_ScoreLabel->setText(QString::number(m_Score));
}

const int & Player::getScore() const _NOEXCEPT_IN_RELEASE_
{
	return m_Score;
}

Player::~Player()
{
	delete[] m_Cards;
}

size_t Player::comTurn()
{
	assert(!m_IsPlayer);
	std::vector<size_t> unusedCards;
	//先获取能用的卡牌列表
	for (size_t i = 0; i < 10; i++)
	{
		if (m_Cards[i].button->isVisible())
		{
			unusedCards.push_back(i);
		}
	}
	//机器人打牌逻辑
	if (unusedCards.empty())
	{
		return 10;
	}
	//统计卡牌
	std::vector<size_t> recoverCards = {};
	std::vector<size_t> lightningCards = {};
	std::vector<size_t> normalCards = {};
	std::vector<size_t> mirrorCards = {};
	for (size_t & index : unusedCards)
	{
		switch (m_Cards[index].card.getType())
		{
		case Card::Type::Null:assert(false); break;
		case Card::Type::A1:recoverCards.push_back(index); break;
		case Card::Type::A2:
		case Card::Type::A3:
		case Card::Type::A4:
		case Card::Type::A5:
		case Card::Type::A6:
		case Card::Type::A7:normalCards.push_back(index); break;
		case Card::Type::Mirror:mirrorCards.push_back(index); break;
		case Card::Type::Lightning:lightningCards.push_back(index); break;
		default:assert(false); break;
		}
	}
	if (isLastCardDestoryed() && !recoverCards.empty())//有卡被炸优先恢复
	{
		return recoverCards[0];
	}
	if (!lightningCards.empty() && lightningCards.size() >= normalCards.size())
	{
		return lightningCards[0];
	}
	if (!mirrorCards.empty() && mirrorCards.size() >= normalCards.size())
	{
		return mirrorCards[0];
	}
	if (!normalCards.empty())
	{
		return normalCards[0];
	}
	return 10;
}


void Player::initialize(QPushButton** & buttons, QPushButton * & lastCard, QLabel * & score, bool isPlayer) _NOEXCEPT_IN_RELEASE_
{
	m_IsPlayer = isPlayer;
	m_LastCard.button = lastCard;
	m_LastCard.button->setVisible(false);
	m_Cards = new CardButton[10];
	m_ScoreLabel = score;
	m_ScoreLabel->setVisible(false);
	for (int i = 0; i < 10; i++)
	{
		m_Cards[i].button = buttons[i];
		buttons[i]->setVisible(false);
		//if (!isPlayer)
		//{
		//	buttons[i]->setEnabled(false);
		//}
	}
}

void Player::setCard(const size_t & index, const Card::Type type)  _NOEXCEPT_IN_RELEASE_
{
	m_Cards[index].card = type;
	if (m_IsPlayer)
	{
		m_Cards[index].button->setText(m_Cards[index].card.toString());
	}
}

void Player::setFirstCard(const size_t index, const Card::Type type) _NOEXCEPT_IN_RELEASE_
{
	//assert(m_Cards[index].card == Card::Type::Null);
	setCard(index, type);
	m_Cards[index].button->setVisible(true);
}

Card::Type Player::useCard(size_t index) _NOEXCEPT_IN_RELEASE_
{
	assert(m_Cards[index].button->isVisible());
	m_Cards[index].button->setVisible(false);
	return m_Cards[index].card.getType();
}

bool Player::isNoneCard() const _NOEXCEPT_IN_RELEASE_
{
	for (size_t index = 0; index < 10; index++)
	{
		if (m_Cards[index].button->isVisible())
		{
			return false;
		}
	}
	return true;
}

bool Player::isLastCardDestoryed() const _NOEXCEPT_IN_RELEASE_
{
	return !m_LastCard.button->isEnabled();
}

void Player::destoryLastCard() _NOEXCEPT_IN_RELEASE_
{
	m_LastCard.button->setEnabled(false);
	addScore(-static_cast<int>(m_LastCard.card.getType()));
}

void Player::setLastCard(Card::Type type) _NOEXCEPT_IN_RELEASE_
{	
	m_LastCard.card = type;
	m_LastCard.button->setText(m_LastCard.card.toString());
	m_LastCard.button->setEnabled(true);
	addScore(static_cast<int>(type));
}

Card::Type Player::getLastCard() const _NOEXCEPT_IN_RELEASE_
{
	return m_LastCard.card.getType();
}

void Player::recoverLastCard() _NOEXCEPT_IN_RELEASE_
{
	assert(!m_LastCard.button->isEnabled());
	addScore(static_cast<int>(m_LastCard.card.getType()));
	m_LastCard.button->setEnabled(true);
}

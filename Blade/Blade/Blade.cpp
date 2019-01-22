#include "Blade.h"

Blade::Blade(QWidget *parent)
	: QMainWindow(parent),
	m_Turn(0),
	m_Times(0)
{
	ui.setupUi(this);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));//�����������
	//��ʼ��������ť�Ŀ���
	m_Buttons[0] = new QPushButton *[10]{ ui.ButtonCard_0,ui.ButtonCard_1,ui.ButtonCard_2,ui.ButtonCard_3,
	ui.ButtonCard_4, ui.ButtonCard_5, ui.ButtonCard_6, ui.ButtonCard_7, ui.ButtonCard_8,
	ui.ButtonCard_9 };
	m_Buttons[1] = new QPushButton *[10]{ ui.ButtonCard_10,ui.ButtonCard_11,ui.ButtonCard_12,ui.ButtonCard_13,
		ui.ButtonCard_14, ui.ButtonCard_15, ui.ButtonCard_16, ui.ButtonCard_17, ui.ButtonCard_18,
		ui.ButtonCard_19 };
	m_Library = ui.ButtonCard_20;
	m_Player[0].initialize(m_Buttons[0], ui.ButtonCard_21, ui.label_0, true);//���
	m_Player[1].initialize(m_Buttons[1], ui.ButtonCard_22, ui.label_1, false);//����
	m_LastCard[0] = ui.ButtonCard_21;
	m_LastCard[1] = ui.ButtonCard_22;
	m_ScoreLabel[0] = ui.label_0;
	m_ScoreLabel[1] = ui.label_1;
	m_ActCard = ui.ButtonCard_23;
	//m_Library->setEnabled(false);
	//��ʼ����������
	for (unsigned i = 0; i < 10; i++)
	{
		m_Buttons[1][i]->setText("Blade!");
	}
	m_Library->setText("Blade!");
	m_ActCard->setText("Blade!");
	//�����û���ť
	connect(m_Buttons[0][0], SIGNAL(clicked()), this, SLOT(playerButton0()));
	connect(m_Buttons[0][1], SIGNAL(clicked()), this, SLOT(playerButton1()));
	connect(m_Buttons[0][2], SIGNAL(clicked()), this, SLOT(playerButton2()));
	connect(m_Buttons[0][3], SIGNAL(clicked()), this, SLOT(playerButton3()));
	connect(m_Buttons[0][4], SIGNAL(clicked()), this, SLOT(playerButton4()));
	connect(m_Buttons[0][5], SIGNAL(clicked()), this, SLOT(playerButton5()));
	connect(m_Buttons[0][6], SIGNAL(clicked()), this, SLOT(playerButton6()));
	connect(m_Buttons[0][7], SIGNAL(clicked()), this, SLOT(playerButton7()));
	connect(m_Buttons[0][8], SIGNAL(clicked()), this, SLOT(playerButton8()));
	connect(m_Buttons[0][9], SIGNAL(clicked()), this, SLOT(playerButton9()));
	//������Ϸ���ð�ť
	connect(ui.ButtonCard_24, SIGNAL(clicked()), this, SLOT(gameStart()));
	//��Ϸ��ʼ
	gameStart();
}

Blade::~Blade()
{
	for (QPushButton **& var : m_Buttons)
	{
		delete[] var;
	}
}

inline void Blade::caculateMoveXY(const QWidget * begin, const QWidget * end) _NOEXCEPT_IN_RELEASE_
{
	const QRect & rect1 = begin->geometry();
	const QRect & rect2 = end->geometry();
	m_MoveX = (rect2.x() - rect1.x()) / _MOVE_TIMES_;
	m_MoveY = (rect2.y() - rect1.y()) / _MOVE_TIMES_;
	m_Times = _MOVE_TIMES_;
}

void Blade::gameStart() _NOEXCEPT_IN_RELEASE_
{
	//���ÿؼ���ʾ
	for (QPushButton **& buttons : m_Buttons)
	{
		for (size_t index = 0; index < 10; index++)
		{
			buttons[index]->setVisible(false);
		}
	}
	m_ActCard->setVisible(false);
	m_LastCard[0]->setVisible(false);
	m_LastCard[1]->setVisible(false);
	m_Library->setVisible(true);
	ui.ButtonCard_24->setVisible(false);
	m_ScoreLabel[0]->setVisible(false);
	m_ScoreLabel[1]->setVisible(false);
	ui.label_2->setVisible(false);
	m_ActCard->setGeometry(m_Library->geometry());//����ActCard
	m_Count[0] = m_Count[1] = 9;
	m_Count[2] = 20;
	m_Turn = 0;
	//���Ӷ�������
	connect(&m_Timer1, SIGNAL(timeout()), this, SLOT(initialCardAnime()));
	//�����һ�ε�λ�ñ仯
	caculateMoveXY(m_Library, m_Buttons[m_Turn][m_Count[m_Turn]]);
	m_ActCard->setVisible(true);
	m_Timer1.start(_ACTION_INTERVAL_);
}

inline void Blade::moveWidget(QWidget * target) _NOEXCEPT_IN_RELEASE_
{
	QRect rect = target->geometry();
	rect.adjust(m_MoveX, m_MoveY, m_MoveX, m_MoveY);
	target->setGeometry(rect);
	m_Times--;
}

void Blade::roundStart() _NOEXCEPT_IN_RELEASE_
{
	m_Turn = 0;
	//����˫���÷�
	m_Player[0].setScore(0);
	m_Player[1].setScore(0);
	connect(&m_Timer1, SIGNAL(timeout()), this, SLOT(roundStartAnime()));
	m_Count[2] = 2;
	caculateMoveXY(m_Library, m_LastCard[m_Turn]);
	m_ActCard->setVisible(true);
	m_Timer1.start(_ACTION_INTERVAL_);
}

inline void Blade::cardButton_click(size_t index) _NOEXCEPT_IN_RELEASE_
{ 
	if (cardResult(index))
	{
		cardResult(m_Player[1].comTurn());
	}
	if (m_Player[0].isNoneCard())
	{
		gameEnd();
	}
}

bool Blade::cardResult(const size_t & index)_NOEXCEPT_IN_RELEASE_
{
	if (index >= 10)//û�����ж�ʤ��
	{
		gameEnd();
		return false;
	}
	Card::Type type = m_Player[m_Turn].useCard(index);
	switch (type)
	{
	case Card::Type::Null:assert(false); break;
	case Card::Type::A1:
	{
		if (m_Player[m_Turn].isLastCardDestoryed())//�����һ�ſ����ƻ��ˣ��ظ������������+1
		{
			m_Player[m_Turn].recoverLastCard();
			break;
		}
	}
	case Card::Type::A2:
	case Card::Type::A3:
	case Card::Type::A4:
	case Card::Type::A5:
	case Card::Type::A6:
	case Card::Type::A7:
	{
		m_Player[m_Turn].setLastCard(type);
		break;
	}
	case Card::Type::Mirror:
	{
		int score0 = m_Player[0].getScore();
		int score1 = m_Player[1].getScore();
		Card::Type tempType = m_Player[0].getLastCard();
		m_Player[0].setLastCard(m_Player[1].getLastCard());
		m_Player[1].setLastCard(tempType);
		m_Player[0].setScore(score1);
		m_Player[1].setScore(score0);
		break;
	}
	case Card::Type::Lightning:
	{
		m_Player[m_Turn^1].destoryLastCard();
		break;
	}
	default:assert(false); break;
	}
	//����ղŴ��ƵĽ��
	switch (checkResult())
	{
	case 0:roundStart(); return false; break;//��ȣ��غ����¿�ʼ
	case 1:break;//������������ƺ�ȶ����
	case -1:gameEnd(); return false; break;//�ȶ���С����Ϸ����
	default:assert(false); break;
	}
	m_Turn ^= 1;
	return true;
}

inline int Blade::checkResult() _NOEXCEPT_IN_RELEASE_
{
	const int & score0 = m_Player[m_Turn].getScore();
	const int & score1 = m_Player[m_Turn ^ 1].getScore();
	if (score0 == score1)
	{
		return 0;
	}
	else if (score0 > score1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void Blade::gameEnd()_NOEXCEPT_IN_RELEASE_
{
	//���ÿؼ���ʾ
	for (QPushButton **& buttons : m_Buttons)
	{
		for (size_t index = 0; index < 10; index++)
		{
			buttons[index]->setVisible(false);
		}
	}
	m_ActCard->setVisible(false);
	m_LastCard[0]->setVisible(false);
	m_LastCard[1]->setVisible(false);
	m_Library->setVisible(false);
	ui.ButtonCard_24->setVisible(true);
	ui.label_2->setVisible(true);
	if (m_Turn)
	{
		ui.label_2->setText("You win!");
	}
	else
	{
		ui.label_2->setText("You Lost!");
	}
}

void Blade::roundStartAnime() _NOEXCEPT_IN_RELEASE_
{
	if (m_Times > 0)
	{
		moveWidget(m_ActCard);
	}
	else
	{
		m_ActCard->setGeometry(m_Library->geometry());
		m_Count[2]--;
		m_LastCard[m_Turn]->setVisible(true);
		m_Turn ^= 1;
		caculateMoveXY(m_Library, m_LastCard[m_Turn]);
		m_Player[m_Turn].setLastCard(static_cast<Card::Type>(qrand() % 7 + 1));//��ʾ��һ����
		if (!m_Count[2])//ÿ���˶����˵�һ����
		{
			m_ActCard->setVisible(false);
			m_ScoreLabel[0]->setVisible(true);
			m_ScoreLabel[1]->setVisible(true);
			m_Timer1.stop();
			m_Timer1.disconnect();
			//����С�����ж���������ͬ���¿�ʼ
			m_Turn = 0;
			switch (checkResult())
			{
			case 0:roundStart(); break;
			case 1: cardResult(m_Player[++m_Turn].comTurn()); break;
			case -1:break;
			default:assert(false); break;
			}
		}
	}
}

void Blade::playerButton0()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(0);
}

void Blade::playerButton1()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(1);
}

void Blade::playerButton2()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(2);
}

void Blade::playerButton3()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(3);
}

void Blade::playerButton4()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(4);
}

void Blade::playerButton5()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(5);
}

void Blade::playerButton6()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(6);
}

void Blade::playerButton7()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(7);
}

void Blade::playerButton8()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(8);
}

void Blade::playerButton9()_NOEXCEPT_IN_RELEASE_
{
	cardButton_click(9);
}

void Blade::initialCardAnime()_NOEXCEPT_IN_RELEASE_
{
	if (m_Times > 0)
	{
		moveWidget(m_ActCard);
	}
	else
	{
		m_ActCard->setGeometry(m_Library->geometry());//����ActCard
		//���Ʒ�����Ӧplayer
		m_Player[m_Turn].setFirstCard(m_Count[m_Turn], static_cast<Card::Type>(qrand() % 9 + 1));
		//���������λ�ñ仯
		m_Count[m_Turn]--;
		m_Turn ^= 1;
		m_Count[2]--;
		if (m_Count[2])//�����û����
		{
			caculateMoveXY(m_Library, m_Buttons[m_Turn][m_Count[m_Turn]]);
		}
		else//�Ʒ�����
		{
			m_Timer1.stop();//�ص���ʱ��
			m_Timer1.disconnect();//�����ʱ������
			m_ActCard->setVisible(false);
			roundStart();
		}
	}
}
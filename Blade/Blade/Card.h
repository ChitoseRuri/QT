#pragma once
#include <string>
#include"qstring.h"
#if defined(DEBUG) | defined(_DEBUG)
#define _NOEXCEPT_IN_RELEASE_
#else
#define NDEBUG
#define _NOEXCEPT_IN_RELEASE_ noexcept
#endif


class Card
{
public:
	enum class Type
	{
		Null,
		A1,//�����һ�ſ������磬�򸴻���ڶ��ſ�
		A2,
		A3,
		A4,
		A5,
		A6,
		A7,
		Mirror,//�����ֽ�������
		Lightning//ɱ����һ�ſ�
	};

private:
	Type m_Type;

public:
	Card();
	~Card();

	QString toString() noexcept;

	void operator = (Type type)  noexcept;
	bool operator == (Type type) const noexcept;
	const Type & getType() const noexcept;
};
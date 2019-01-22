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
		A1,//如果上一张卡是闪电，则复活倒数第二张卡
		A2,
		A3,
		A4,
		A5,
		A6,
		A7,
		Mirror,//跟对手交换点数
		Lightning//杀死上一张卡
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
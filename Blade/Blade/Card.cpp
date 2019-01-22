#include "Card.h"

Card::Card():
	m_Type(Type::Null)
{
}

Card::~Card()
{
}

QString Card::toString() noexcept
{
	switch (m_Type)
	{
	case Card::Type::Null:return QString("Null");break;
	case Card::Type::A1:
	case Card::Type::A2:
	case Card::Type::A3:
	case Card::Type::A4:
	case Card::Type::A5:
	case Card::Type::A6:
	case Card::Type::A7:return QString::number(static_cast<int>(m_Type));
	case Card::Type::Mirror:return QString("Mirror"); break;
	case Card::Type::Lightning:return QString("Light\nning");break;
	default:return QString("Bug"); break;
	}
}

void Card::operator=(Type type)  noexcept
{
	m_Type = type;
}

bool Card::operator==(Type type) const noexcept
{
	return m_Type == type;
}

const Card::Type & Card::getType() const noexcept
{
	return m_Type;
}

#include "DynamicAttack.h"


DynamicAttack::DynamicAttack(const Direction& dir, const sf::Vector2f& startPos, const Dynamic_t ObjType, const float dmg, 
							const playerData& owner, const sf::Vector2f& factor, std::shared_ptr<float> score)
	:MovingObject(startPos, ObjType, factor)
	,m_dir(dir), m_startPos(startPos), m_isDone(false), m_dmg(dmg), m_owner(owner),
	m_score(score)
{
}

playerData DynamicAttack::getOwner()
{
	return m_owner;
}

float DynamicAttack::getDmg()
{
	return m_dmg;
}

bool DynamicAttack::isDone()
{
	return m_isDone;
}

void DynamicAttack::addScore(const float score)
{
	*m_score += score;
}
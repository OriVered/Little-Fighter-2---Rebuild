#pragma once
#include "macros.h"
#include "MovingObject.h"

class DynamicAttack : public MovingObject
{
public:
	DynamicAttack(const Direction& dir, const sf::Vector2f& startPos, const Dynamic_t ObjType, const float dmg, 
				const playerData& owner, const sf::Vector2f& factor, std::shared_ptr<float> score);

	/* Accesors */
	virtual void update(const sf::Time& delta) = 0;
	playerData getOwner ();
	float getDmg ();
	bool isDone();
	void moveBack(const sf::Time& delta) = 0;
	void addScore(const float score);
	/* Mutator */
protected:
	Direction m_dir;
	sf::Vector2f m_startPos;
	bool m_isDone;
	sf::Clock m_ClockTime;
	float m_dmg;
	playerData m_owner;
	std::shared_ptr<float> m_score;
};
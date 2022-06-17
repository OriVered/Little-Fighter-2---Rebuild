#pragma once
#include "macros.h"
#include "DynamicAttack.h"

class  FirzenBall : public DynamicAttack
{
public:
	FirzenBall(const Direction& dir, const sf::Vector2f& startPos, const playerData& owner, std::shared_ptr< float > score);
	void moveBack(const sf::Time& delta) override;

	/* Accesors */
	void update(const sf::Time& delta) override;

};
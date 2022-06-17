#pragma once
#include "macros.h"
#include "ResourceManager.h"
#include "Background.h"

class GameBackground : public Background
{
public:
	GameBackground(const sf::Color& bgColor, const Modes& mode);
	
	/* Draw */
	virtual sf::Vector2f getBackGroundSize();
	virtual sf::FloatRect getGlobalBounds() const override;
protected:
	sf::RectangleShape m_ground;
};
#include "GameBackground.h"

GameBackground::GameBackground(const sf::Color & bgColor, const Modes& mode)
	:Background()
{
	m_ground.setSize({ ModesWorldSizeMap.find(mode)->second.width, ModesWorldSizeMap.find(mode)->second.height });
	m_ground.setPosition(GroundStart);
	m_ground.setFillColor(bgColor);
}

sf::FloatRect GameBackground::getGlobalBounds() const
{
	return  m_ground.getGlobalBounds();
}

sf::Vector2f GameBackground::getBackGroundSize()
{
	return m_ground.getSize();
}

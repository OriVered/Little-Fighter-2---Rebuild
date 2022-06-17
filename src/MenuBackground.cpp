#include "MenuBackground.h"

MenuBackground::MenuBackground(const Bg_t background)
	:m_background(std::make_unique<ImageTexture> (startWindow, background, backgroundFactor))
{
	m_background->setSize({ WindowWidth, WindowHeight });
}

void MenuBackground::draw(sf::RenderWindow& window) const
{
	m_background->draw(window);
}

sf::FloatRect MenuBackground::getGlobalBounds() const
{
	return m_background->getGlobalBounds();
}

#include "Help.h"



Help::Help(sf::RenderWindow& window)
:State(window, Bg_t::Help)
{}

void Help::draw()
{
    m_background->draw(m_window);
}
	
void Help::handleClick(const sf::Vector2f& )
{
    m_isRunning = false;
}

void Help::handleKeyReleased(sf::Keyboard::Key )
{
    m_isRunning = false;
}
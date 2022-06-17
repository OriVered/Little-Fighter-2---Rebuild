#pragma once
#include <vector>
#include "macros.h"
#include "MenuBackground.h"
#include "ResourceManager.h"

class State
{
public:
	State(sf::RenderWindow& window);
	State(sf::RenderWindow& window, const Bg_t& background);
	virtual ~State() = default;

	virtual void update();
	virtual void render();
	virtual void run();
	virtual void draw() = 0;
	virtual void pollEvents();
	virtual void handleView() = 0;
	
	void setBackground(const std::shared_ptr< Background>& background);

protected:
	sf::RenderWindow& m_window;
	std::shared_ptr <Background> m_background;
	sf::Clock gameClock;
	bool m_isRunning;
	/* Protected Functions */
	virtual void handleClick(const sf::Vector2f& location) = 0;
	virtual void handleKeyPress(sf::Keyboard::Key key) = 0;
	virtual void handleKeyPress() = 0;
	virtual void handleKeyReleased(sf::Keyboard::Key key) = 0;
	virtual void handleMove(const sf::Vector2f& location) = 0;

};
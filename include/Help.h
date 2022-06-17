#pragma once
#include "State.h"
#include "macros.h"

class Help : public State
{

public:
	Help(sf::RenderWindow& window);

	void handleView() override {}
	void draw() override ;
	
protected:
	void handleClick(const sf::Vector2f& location) override;
	void handleKeyPress(sf::Keyboard::Key ) override {}
	void handleKeyPress() override {}
	void handleKeyReleased(sf::Keyboard::Key key) override;
	void handleMove(const sf::Vector2f& ) override {}
};
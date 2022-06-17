#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include "macros.h"
#include "Menu.h"


class Controller
{
public:
	/*constructor Distructor */
	Controller();
	~Controller();

	/* Window Functions */
	void update();
	void render();
	void pollEvents();
	void run();

private:
	/* Window members */
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::Event m_event;
	sf::Music m_music;

	/* Game members */
	std::unique_ptr<Menu> m_menu;

	/* Private Functions */
	void initWindow();
	void initMenu();
};

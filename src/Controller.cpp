#include "Controller.h"

/* Constructors / Distructors */
Controller::Controller()
	:m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WindowWidth, WindowHeight), "Little Fighters", sf::Style::Default | sf::Style::Titlebar | sf::Style::Close))
{
	initMenu();

	initWindow();
}

Controller::~Controller()
{
}

/* Private Functions */
void Controller::initMenu()
{
	m_menu = std::make_unique < Menu >();
}

void Controller::initWindow()
{
	m_window->setFramerateLimit(60);
}

/* Window Functions */
void Controller::run()
{
	while (m_window->isOpen())
	{
		// Update
		update();

		// Render
		render();
	}
}

void Controller::update()
{
	pollEvents();
}


void Controller::pollEvents()
{
	while (m_window->pollEvent(m_event))
		m_menu->pollEvents(*m_window, m_event);
}

void Controller::render()
{
	m_window->clear();

	/* Draw Menu */
	m_menu->draw(*m_window);

	m_window->display();
}

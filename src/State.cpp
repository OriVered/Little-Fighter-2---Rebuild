#include "State.h"

State::State(sf::RenderWindow& window)
	:m_window(window), m_isRunning(true), 
    gameClock(sf::Clock())
{}
State::State(sf::RenderWindow& window, const Bg_t& background)
    : State(window) 
{
    m_background = std::make_shared<MenuBackground>(background);
}

void State::run()
{
    while (m_window.isOpen() && m_isRunning)
    {
        // Update
        update();

        // Render
        render();
    }
}

void State::update()
{
    pollEvents();
}

void State::render()
{
    m_window.clear();

    /* Draw Menu */
    draw();

    m_window.display();
}

void State::pollEvents()
{
    for (auto event = sf::Event(); m_window.pollEvent(event); )
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            handleClick(location);
            break;
        }
        case sf::Event::MouseMoved:
        {
            auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            handleMove(location);
            break;
        }
        case sf::Event::KeyPressed:
        {
            handleKeyPress(event.key.code);
            break;
        }
        case sf::Event::KeyReleased:
        {
            handleKeyReleased(event.key.code);
            break;
        }
        default:        break;
        }
    }
}

void State::setBackground(const std::shared_ptr< Background>& background)
{
    m_background = background;
}

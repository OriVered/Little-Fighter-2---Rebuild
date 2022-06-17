#include "Menu.h"


Menu::Menu()
    :m_state(createButton()), m_background(Bg_t::bg_menu)
{
    ResourceManager::instance().setSong((int)Type_s::mainTrack);
    srand((unsigned int)time(NULL));
}
Menu::~Menu()
{}



void Menu::pollEvents(sf::RenderWindow& window, const sf::Event& event)
{   
    switch (event.type)
    {
    case sf::Event::Closed:
    {
        window.close();
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        handleClick(location, window);
        break;
    }
    case sf::Event::MouseMoved:
    {
        auto location = window.mapPixelToCoords(
            { event.mouseMove.x, event.mouseMove.y });
        handleMove(location);
        break;
    }
    default: break;
    }
}

void Menu::handleMove(const sf::Vector2f& location)
{
    for (auto& state : m_state)
    {
        if (state.m_button->getGlobalBounds().contains(location))
        {
            state.m_button->setOutlineThickness(boldSize);
            state.m_button->setOutlineColor(sf::Color::Black);
        }
        else
            state.m_button->setOutlineThickness(0.f);
    }
}

void Menu::handleClick(const sf::Vector2f& location, sf::RenderWindow & window)
{
    for (auto& state : m_state)
        if (state.m_button->getGlobalBounds().contains(location))
            handleClick(state.type, window);//create object of state             
}

void Menu::handleClick(State_t StateClicked, sf::RenderWindow& window)
{
    switch (StateClicked)
    {
        default: ;       break;
        case State_t::AllVsAll:         AllVsAllMode(window).run();               break;   
        case State_t::TwoPlayerMode:    TwoPlayerMode(window).run();              break;
        case State_t::StageMode:        StageMode(window).run();                  break;
        case State_t::Help:             Help (window).run();                      break;
        case State_t::Exit:             window.close() ;                          break;
    }
    sf::View view = window.getView();
    view.reset(sf::FloatRect(0, 0, float(WindowWidth), float(WindowHeight)));
	window.setView(view);

    if (ResourceManager::instance().getSong((int)Type_s::mainTrack).getStatus() == sf::Sound::Status::Stopped)
        ResourceManager::instance().setSong((int)Type_s::mainTrack);
}


void Menu::draw(sf::RenderWindow& window)
{
    //deaw background
    m_background.draw(window);
    //draw Buttons
    for (auto& state : m_state)
        state.m_button->draw(window);
}

Menu::StateMap Menu::createButton()
{
    return StateMap
    {
        {
            std::make_shared <ImageText>("All Vs All Mode", AllVsAll_B),
            State_t::AllVsAll,
        },
        {
            std::make_shared <ImageText>("Two Players Mode", TwoPlayerMode_B),
            State_t::TwoPlayerMode,
        },
        {
            std::make_shared <ImageText>("Stage Mode", StageMode_B),
            State_t::StageMode,
        },
        {
            std::make_shared <ImageText>("Help", Help_B),
            State_t::Help,
        },
        {
            std::make_shared <ImageText>("Exit", Exit_B),
            State_t::Exit,
        }
    };
}
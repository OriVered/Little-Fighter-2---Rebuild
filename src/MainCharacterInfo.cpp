#include "MainCharacterInfo.h"


MainCharacterInfo::MainCharacterInfo (const playerData& data)
    :CharacterInfo(data, fighterLife.find(data.m_fighter)->second) , m_mana(characterInfoWidth),
    m_score(std::make_shared<float>(0.f))

{
    initializeShapes(m_healthShape, isHealth);
    initializeShapes(m_manaShape, isMana);
    m_icon = std::make_shared<ImageTexture>(sf::Vector2f{firstIconPosition.x + m_data.playerNum  * (characterInfoWidth + characterInfoSpace ) , firstIconPosition.y}, (FighterIcon_f)m_data.m_fighter, iconFactor);
}


void MainCharacterInfo::initializeShapes(std::pair <sf::RectangleShape , sf::RectangleShape>& rectangles, const bool manaOrHealth)
{
    sf::Color color = manaColor;
    sf::Color colorBack = manaBackColor;
    float offSet = yAxisOffset;
    if (manaOrHealth == isHealth) 
    {
        color = healthColor;
        colorBack = healthBackColor;
        offSet += characterInfoHeight;
    }

    rectangles.first.setSize({ characterInfoWidth, characterInfoHeight });
    rectangles.first.setFillColor(color);
    rectangles.first.setOutlineColor(color); //shdow
    rectangles.first.setOutlineThickness(shadowThickness); //shdow
    rectangles.first.setPosition({0 , firstInfoPosition.y + offSet + characterInfoHeight * (m_data.playerNum / 4) });

    rectangles.second.setSize({ characterInfoWidth, characterInfoHeight });
    rectangles.second.setFillColor(colorBack);
    rectangles.second.setPosition({0 , firstInfoPosition.y + offSet + characterInfoHeight * (m_data.playerNum / 4) });
    rectangles.second.setOutlineColor(colorBack);
	rectangles.second.setOutlineThickness(shadowThickness); //shdow

}

void MainCharacterInfo::update(const sf::Time& delta)
{
    if (m_infoClock.getElapsedTime().asSeconds() > 0.5f)
    {
        m_mana +=  manaUnity;
        m_infoClock.restart();
    }

    if (m_health < 0)
        m_health = 0;

    else if (m_health > fighterLife.find(m_data.m_fighter)->second)
        m_health = fighterLife.find(m_data.m_fighter)->second;

    if (m_mana < 0)
        m_mana = 0;

    else if (m_mana> characterInfoWidth)
        m_mana = characterInfoWidth;

    if (!(abs(m_health - m_healthShape.first.getSize().x) < smallDifference))
        m_healthShape.first.setSize({m_healthShape.first.getSize().x + sgn (m_health - m_healthShape.first.getSize().x) * delta.asMilliseconds() * smallMovement ,  m_healthShape.first.getSize().y });
    
    if (!(abs(m_mana - m_manaShape.first.getSize().x) < smallDifference))
        m_manaShape.first.setSize({m_manaShape.first.getSize().x + sgn(m_mana - m_manaShape.first.getSize().x) * delta.asMilliseconds() * smallMovement ,  m_manaShape.first.getSize().y});
    
}


void MainCharacterInfo::draw(sf::RenderWindow& window) const
{   

    m_icon->draw(window);
    window.draw(m_healthShape.second);
    window.draw(m_healthShape.first);
    window.draw(m_manaShape.second);
    window.draw(m_manaShape.first);
    
}

void MainCharacterInfo::addMana(const float power)
{
    m_mana += power;
}

void MainCharacterInfo::addScore(const float score)
{
    *m_score += score;
}

std::shared_ptr <float> MainCharacterInfo::getScore() const
{
    return m_score;
}

float MainCharacterInfo::getMana() const
{
    return m_mana;
}

void MainCharacterInfo::moveInfo(const float xPosition, const float )
{
    m_icon->setPosition({xPosition + m_data.playerNum  * (characterInfoWidth + characterInfoSpace ) + characterInfoWidth/ 1.2f , m_icon->getPosition().y});
    m_healthShape.first.setPosition({xPosition + (m_data.playerNum% numOfBars)   * (characterInfoWidth + characterInfoSpace ) + characterInfoWidth , m_healthShape.first.getPosition().y});
    m_healthShape.second.setPosition({xPosition + (m_data.playerNum % numOfBars) * (characterInfoWidth + characterInfoSpace ) + characterInfoWidth, m_healthShape.second.getPosition().y});
    
    m_manaShape.first.setPosition({xPosition + (m_data.playerNum % numOfBars) * (characterInfoWidth + characterInfoSpace ) + characterInfoWidth, m_manaShape.first.getPosition().y});
    m_manaShape.second.setPosition({xPosition + (m_data.playerNum % numOfBars) * (characterInfoWidth + characterInfoSpace ) + characterInfoWidth , m_manaShape.second.getPosition().y});
}


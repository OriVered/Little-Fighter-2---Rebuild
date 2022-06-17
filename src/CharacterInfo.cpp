#include "CharacterInfo.h"



CharacterInfo::CharacterInfo(const playerData& data, const float health)
    :m_data(data), m_health(health)
{
    initializeShapes(m_healthShape, isHealth);
}

CharacterInfo::CharacterInfo (const playerData& data)
:m_data(data), m_health(maxLife)
{
    initializeShapes(m_healthShape, isHealth);
}


void CharacterInfo::initializeShapes(std::pair <sf::RectangleShape , sf::RectangleShape>& rectangles, const bool )
{
    sf::Color color = healthColor;
    sf::Color colorBack = healthBackColor;

    rectangles.first.setSize({infoWidth, infoHeight});
    rectangles.first.setFillColor(color);
    rectangles.first.setOutlineColor(color); //shdow
}

void CharacterInfo::update(const sf::Time& delta)
{


    if (m_health < noLife)
        m_health = noLife;

    else if (m_health > maxLife)
        m_health = maxLife;

    if (!(abs(m_health - m_healthShape.first.getSize().x) < smallDifference))
        m_healthShape.first.setSize({ m_healthShape.first.getSize().x + sgn(m_health - m_healthShape.first.getSize().x) * delta.asMilliseconds() * smallMovement ,  m_healthShape.first.getSize().y });
}


void CharacterInfo::draw(sf::RenderWindow& window) const
{   
    window.draw(m_healthShape.first);
}

void CharacterInfo::addHealth(const float power)
{
    m_health += power;
}


playerData CharacterInfo::getData() const
{
    return m_data;
}

float CharacterInfo::getHealth() const
{
    return m_health;
}


void CharacterInfo::moveInfo(const float xPosition, const float yPosition)
{
    m_healthShape.first.setPosition({xPosition-fixX, yPosition-fixY});
}
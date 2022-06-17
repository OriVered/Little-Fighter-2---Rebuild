#include "LifeGift.h"


LifeGift::LifeGift(const sf::Vector2f& pos )
:GameObject(pos, lifeGiftFactor),
m_isDone(false),
m_life(rand() %lifeRange + minimumLife)
{

    m_sprite.setTexture(*ResourceManager::instance().getTexture(Bg_t::lifeGift));
	// for correct rotation, setting origin at center
	m_sprite.setOrigin(m_sprite.getLocalBounds().height / 2,
		m_sprite.getLocalBounds().width / 2); 
}


void LifeGift::setDone()
{
    m_isDone = true;
}

bool LifeGift::isDone() const 
{
    return m_isDone;
}

int LifeGift::getLife() const
{
    return m_life;
}
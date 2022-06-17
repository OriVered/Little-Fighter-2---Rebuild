#include "FireAttack.h"


FireAttack::FireAttack(const sf::Vector2f& pos, const playerData& owner, std::shared_ptr <float> score)
:DynamicAttack(Direction::Stay, pos, Dynamic_t::FireAttack_t, fireAttackDamage, owner, fireFactor, score)
{
    setActionType(ActionType::Explosion);
    setActiveDelay(true);
	ResourceManager::instance().playSFX(Type_s::fireExplosionSound);
}



void FireAttack::update(const sf::Time& delta)
{
    if (m_activeDelayClock.getElapsedTime().asSeconds() > m_activeDelayTime)
		setActiveDelay(false);

	if (getAction() == ActionType::Explosion && !m_isActiveDelayed)
		m_isDone = true;

	MovingObject::update(delta);
}


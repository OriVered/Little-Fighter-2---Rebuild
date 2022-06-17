#include "IceAttack.h"


IceAttack::IceAttack(const sf::Vector2f& pos, const playerData& owner, std::shared_ptr< float > score)
:DynamicAttack(Direction::Stay, pos, Dynamic_t::IceAttack_t, iceAttackDamage, owner, iceFactor, score)
{
    setActionType(ActionType::Explosion);
    setActiveDelay(true);
	ResourceManager::instance().playSFX(Type_s::iceAttackSound);
}



void IceAttack::update(const sf::Time& delta)
{
    if (m_activeDelayClock.getElapsedTime().asSeconds() > m_activeDelayTime)
		setActiveDelay(false);

	if (getAction() == ActionType::Explosion && !m_isActiveDelayed)
		m_isDone = true;

	MovingObject::update(delta);
}
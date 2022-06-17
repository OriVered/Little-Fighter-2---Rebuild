#include "DennisBall.h"

DennisBall::DennisBall(const Direction& dir, const sf::Vector2f& startPos, const playerData& ownerNum, std::shared_ptr< float > score)
	:DynamicAttack(dir, startPos, Dynamic_t::dennisBall_t, dennisBallDmg, ownerNum, ballFactor, score),
	m_dir(dir)
{
	m_speed = dennisBallSpeed;
	MovingObject::setAction({ ActionType::CreateBall, Direction::Stay });
	ResourceManager::instance().playSFX(Type_s::dennisCreateBall);
	setActiveDelay(true);
}

void DennisBall::update(const sf::Time& delta)
{
	if (m_activeDelayClock.getElapsedTime().asSeconds() > m_activeDelayTime)
		setActiveDelay(false);

	if (getAction() == ActionType::Explosion && !m_isActiveDelayed)
		m_isDone = true;
	
	if(!m_isActiveDelayed && getAction() != ActionType::Explosion)	
		MovingObject::setAction({ ActionType::ShotBall, m_dir });


	
	
	MovingObject::update(delta);
}


void DennisBall::moveBack(const sf::Time& )
{
	if (getAction() != ActionType::Explosion)
	{
		MovingObject::setAction({ ActionType::Explosion, Direction::Stay });
		setActiveDelay(true);
	}
}

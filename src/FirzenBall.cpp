#include "FirzenBall.h"

FirzenBall::FirzenBall(const Direction& dir, const sf::Vector2f& startPos, const playerData& owner, std::shared_ptr< float > score)
	:DynamicAttack(dir, startPos, Dynamic_t::FirzenBall_t, firzenBallDmg, owner, ballFactor, score)
{
	m_speed = dennisBallSpeed;
	MovingObject::setAction({ ActionType::CreateBall, Direction::Stay });
	if (dir == Direction::Left)
		m_sprite.scale(mirrorFactor);

	ResourceManager::instance().playSFX(Type_s::firzenCreateBall);
	setActiveDelay(true);
}

void FirzenBall::update(const sf::Time& delta)
{
	if (m_activeDelayClock.getElapsedTime().asSeconds() > m_activeDelayTime)
		setActiveDelay(false);

	if (getAction() == ActionType::Explosion && !m_isActiveDelayed)
		m_isDone = true;

	if (!m_isActiveDelayed && getAction() != ActionType::Explosion)
		MovingObject::setAction({ ActionType::ShotBall, m_dir });


	MovingObject::update(delta);
}

void FirzenBall::moveBack(const sf::Time& )
{
	if (getAction() != ActionType::Explosion)
	{
		MovingObject::setAction({ ActionType::Explosion, Direction::Stay });
		setActiveDelay(true);
	}
}
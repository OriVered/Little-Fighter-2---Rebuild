#pragma once
#include "macros.h"
#include "Animation.h"
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	MovingObject();
	MovingObject(const sf::Vector2f& CenterPos, const Bg_t& objectTex, const sf::Vector2f& factor);
	MovingObject( const sf::Vector2f& CenterPos, const Fighter_f& objectTex, const sf::Vector2f& factor);
	MovingObject(const sf::Vector2f& CenterPos, const Dynamic_t& objectTex, const sf::Vector2f& factor);
	void move(const sf::Time& deltaTime);
	virtual void moveBack(const sf::Time& deltaTime);
	virtual void update(const sf::Time& deltaTime);

	/* Mutator */
	void setDirection(sf::Keyboard::Key key);
	void setDirection(const Direction& dir);
	void setAction(const Action& action);
	void setActionType(const ActionType& action);

	void direction(const Direction dir);
	void setActiveDelay(const bool delay);
	void setPasiveDelay(const bool delay);

	/* Accesors */
	sf::Vector2f getDirection() const;
	ActionType getAction() const ;
	sf::Vector2f getBotLeft() const;
	sf::Vector2f getBotRight() const;
	sf::Vector2f getTopLeft() const;
	sf::Vector2f getTopRight() const;
protected:
	sf::Vector2f m_direction;
    Direction m_dir = Direction::Stay;
	Animation m_animation;
	Action m_action;
	float m_speed;
	sf::Clock m_moveClock;
	sf::Clock m_activeDelayClock;
	sf::Clock m_pasiveDelayClock;
	float m_activeDelayTime;
	float m_pasiveDelayTime;
	bool m_isPasiveDelayed;
	bool m_isActiveDelayed;
};
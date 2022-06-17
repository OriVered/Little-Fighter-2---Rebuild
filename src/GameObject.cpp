#include "GameObject.h"



bool GameObject::collidWith(const GameObject& obj) const
{
	return (abs(y() - obj.y()) < minYDistance) &&
		(abs(x() - obj.x()) < minXDistance);
}

float GameObject::x() const
{
	return m_sprite.getPosition().x; 
}

float GameObject::y() const
{
	return m_sprite.getPosition().y; 
}
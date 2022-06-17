 #pragma once

 #include "macros.h"
 #include "ImageTexture.h"

class GameObject : public ImageTexture
{
public:
	GameObject();
	GameObject(const sf::Vector2f& CenterPos, const sf::Vector2f& factor) : ImageTexture(CenterPos, factor)  {}
	bool collidWith(const GameObject& obj) const;
	float x() const ;
	float y() const;
};
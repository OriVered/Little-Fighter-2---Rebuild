#pragma once
#include "AnimationData.h"
#include "ResourceManager.h"
#include "macros.h"
#include "Utilities.h"

class Animation
{
public:
	Animation(const AnimationData&, sf::Sprite&, Direction dir);
	~Animation();

	bool update(sf::Time, Action); //returns true if finished animation

private:
	void update(Action action);			
	const AnimationData& m_data;
	sf::Time m_elapsed = {};
	Direction m_dir = Direction::Up;
	int m_index = 0;			//index in AnimationData
	sf::Sprite& m_sprite;		//The sprite of the gameObject
	bool fade;
};

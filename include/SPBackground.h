#pragma once
#include "GameBackground.h"
#include "macros.h"
#include "ImageTexture.h"
#include "MovingObject.h"

class SPBackground : public GameBackground
{
public:
	SPBackground(const Modes& mode);
	~SPBackground() = default;
	void draw(sf::RenderWindow& window) const override;
	void update(sf::Time delta) override;
private:
	using wallObj = std::shared_ptr<ImageTexture>;
	using fireObj = std::shared_ptr<MovingObject>;
	struct Wall
	{
		wallObj wall_1;
		wallObj wall_2;
		wallObj wall_3;
		wallObj wall_4;
	};
	std::vector<Wall> m_wall;
	std::vector <fireObj> m_fire;

	void createWall();
	sf::Vector2f getImagePos(Bg_t tex, int index);
};
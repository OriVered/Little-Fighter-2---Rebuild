#pragma once
#include "GameBackground.h"
#include "macros.h"
#include "ImageTexture.h"
#include "MovingObject.h"

class CWBackground : public GameBackground
{
public:
	CWBackground(const Modes& mode);
	~CWBackground() = default;
	void draw(sf::RenderWindow& window) const override;
	void update(sf::Time delta) override;
private:
	using CWObj = std::shared_ptr<ImageTexture>;
	struct Road
	{
		std::vector < CWObj> up_rd;
		std::vector < CWObj> down_rd;
	};
	struct bg
	{
		CWObj hill1;
		CWObj sky;
	};
	struct border
	{
		CWObj hill2Start;
		CWObj hill2End;
		CWObj roadStart;
		CWObj roadEnd;
	};
	Road m_road;
	std::vector <bg >m_background;
	border m_border;

	void createWall();
	sf::Vector2f getImagePos(Bg_t tex, int index);
};
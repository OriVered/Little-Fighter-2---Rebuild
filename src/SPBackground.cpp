#include"SPBackground.h"

SPBackground::SPBackground(const Modes& mode)
	: GameBackground(sp_bg_color, mode)
{
	createWall();
}

void SPBackground::draw(sf::RenderWindow& window) const
{
	/* draw ground */
	window.draw(m_ground);
	
	/* draw wall bojectd */
	for (auto& wall : m_wall)
	{
		wall.wall_1->draw(window);
		wall.wall_2->draw(window);
		wall.wall_3->draw(window);
		wall.wall_4->draw(window);
	}

	/* draw wall animation */
	for (auto& fire : m_fire)
		fire->draw(window);
	
}

void SPBackground::update(sf::Time delta)
{
	for(auto & fire : m_fire)
		fire->update(delta);
}

void SPBackground::createWall()
{

	for (int i = 0; i < bg_numOfCopy; i++)
	{
		m_wall.push_back
		({
				std::make_shared<ImageTexture>(getImagePos(Bg_t::wall_1, i),Bg_t::wall_1, sp_bg_wall_1_factor),
				std::make_shared<ImageTexture>(getImagePos(Bg_t::wall_2, i), Bg_t::wall_2, sp_bg_wall_2_factor),
				std::make_shared<ImageTexture>(getImagePos(Bg_t::wall_3, i), Bg_t::wall_3, sp_bg_wall_3_factor),
				std::make_shared<ImageTexture>(getImagePos(Bg_t::wall_4, i), Bg_t::wall_4, sp_bg_wall_4_factor)
		});
		m_fire.push_back({ std::make_shared<MovingObject>(getImagePos(Bg_t::fire, i), Bg_t::fire, sp_bg_fire_factor)});
	}
}

sf::Vector2f SPBackground::getImagePos(Bg_t tex, int i)
{
	switch(tex)
	{
	case Bg_t::wall_1: return sf::Vector2f(sp_bg_wall_1_start.x + i* sp_bg_width.x, sp_bg_wall_1_start.y);
	case Bg_t::wall_2: return sf::Vector2f(sp_bg_wall_2_start.x + i * sp_bg_width.x, sp_bg_wall_2_start.y);
	case Bg_t::wall_3: return sf::Vector2f(sp_bg_wall_3_start.x + i * sp_bg_width.x, sp_bg_wall_3_start.y);
	case Bg_t::wall_4: return sf::Vector2f(sp_bg_wall_4_start.x + i * sp_bg_width.x, sp_bg_wall_4_start.y);
	case Bg_t::fire: return sf::Vector2f(sp_bg_fire_start.x + i * sp_bg_width.x, sp_bg_fire_start.y);
	default: return sf::Vector2f();
	}
}


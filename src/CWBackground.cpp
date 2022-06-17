#include"CWBackground.h"

CWBackground::CWBackground(const Modes& mode)
	:GameBackground(cw_bg_color, mode)
{
	createWall();
}

void CWBackground::draw(sf::RenderWindow& window) const
{
	/* draw ground */
	window.draw(m_ground);

	/* draw road bojectd */

	for (auto& sky : m_background)
		sky.sky->draw(window);
	for (auto& hill1 : m_background)
		hill1.hill1->draw(window);

	m_border.hill2Start->draw(window);
	m_border.hill2End->draw(window);
	
	/* draw road bojectd */
	for (auto& rd : m_road.up_rd)
		rd->draw(window);
	for (auto& rd : m_road.down_rd)
		rd->draw(window);
	
	m_border.roadStart->draw(window);
	m_border.roadEnd->draw(window);

}

void CWBackground::update(sf::Time )
{
}

void CWBackground::createWall()
{
	/* create border objects */
	m_border.hill2Start = std::make_shared<ImageTexture> (wc_bg_hill2Start_pos, Bg_t::hill2, wc_bg_hill2Start_factor);
	m_border.hill2End = std::make_shared<ImageTexture> (wc_bg_hill2End_pos, Bg_t::hill2, wc_bg_hill2End_factor);
	m_border.roadStart = std::make_shared<ImageTexture>(wc_bg_roadStart_pos, Bg_t::road1, wc_bg_roadStart_factor);
	m_border.roadEnd = std::make_shared<ImageTexture>(wc_bg_roadEnd_pos, Bg_t::road1, wc_bg_roadStart_factor);
	m_border.roadEnd->setScale(wc_bg_roadEnd_factor.x, wc_bg_roadEnd_factor.y);
	m_border.hill2Start->setScale(wc_bg_roadEnd_factor.y, wc_bg_roadEnd_factor.y);
	m_border.hill2End->setScale(wc_bg_roadEnd_factor.x, wc_bg_roadEnd_factor.y);

	
	/* create background objects */

	for (int i = 0; i < cw_bg_numBgOfCopy; i++)
		m_background.push_back({
		std::make_shared<ImageTexture>(getImagePos(Bg_t::hill1, i), Bg_t::hill1, wc_bg_hill1_factor),
		std::make_shared<ImageTexture>(getImagePos(Bg_t::sky, i), Bg_t::sky, wc_bg_sky_factor) });

	/* create road objects */
	for (int i = 0; i < cw_bg_numOfRoad2fCopy; i++)
		m_road.up_rd.push_back({ std::make_shared<ImageTexture>(getImagePos(Bg_t::road2, i), Bg_t::road2, wc_bg_road2_factor) });
	for (int i = 0; i < cw_bg_numOfRoad3fCopy; i++)
		m_road.down_rd.push_back({ std::make_shared<ImageTexture>(getImagePos(Bg_t::road3, i), Bg_t::road3, wc_bg_road3_factor) });

}

sf::Vector2f CWBackground::getImagePos(Bg_t tex, int i)
{
	switch (tex)
	{
	case Bg_t::road2: return sf::Vector2f(wc_bg_road2Start_pos.x + i * sp_wc_rd2_bg_width.x, wc_bg_road2Start_pos.y);
	case Bg_t::road3: return sf::Vector2f(wc_bg_road3Start_pos.x + i * sp_wc_rd3_bg_width.x, wc_bg_road3Start_pos.y);
	case Bg_t::hill1: return sf::Vector2f(wc_bg_hill1_pos.x + i * sp_wc_hill1_bg_width.x, wc_bg_hill1_pos.y);
	case Bg_t::sky: return sf::Vector2f(wc_bg_road3Start_pos.x + i * sp_wc_sky_bg_width.x, wc_bg_hill1_pos.y);
	default: return sf::Vector2f();
	}
}



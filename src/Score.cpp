#include "Score.h"


Score::Score(sf::RenderWindow& window, std::vector < std::shared_ptr < CharacterInfo > >info, bool &isRunning)
    :State(window, Bg_t::GameScore), m_hartersDataMap(getPlayerDataMap(info))
{
  
    isRunning = false;
    sf::View view = m_window.getView();
    view.reset(sf::FloatRect(0, 0, float(WindowWidth), float(WindowHeight)));
	m_window.setView(view);

}

void Score::draw()
{
    /* Draw Background*/
    m_background->draw(m_window);

    /* Draw Player Data Map*/
    for (auto& player : m_hartersDataMap)
    {
        player.m_fighter->draw(m_window);
        player.m_commanderType->draw(m_window);
        player.m_score->draw(m_window);
        player.m_team->draw(m_window);
    }
}

void Score::handleClick(const sf::Vector2f&)
{
    m_isRunning = false;
}

void Score::handleKeyReleased(sf::Keyboard::Key )
{
    m_isRunning = false;
}

Score::ChartersDataMap Score::getPlayerDataMap(const std::vector < std::shared_ptr < CharacterInfo > >info)
{
    Score::ChartersDataMap chartersdatamap;
    auto it = info;
    std::sort(it.begin(), it.end(), [](const std::shared_ptr<CharacterInfo>& first, const std::shared_ptr<CharacterInfo>& second) { return first->getScore() > second->getScore(); });
    for (auto& player : it)
    {
        auto i = player->getData().playerNum;
        chartersdatamap.emplace_back(PlayerDataMap
            {
                {
                    std::make_shared <ImageTexture>(getImagePlayerPostion(selectType::fighter, i),  (FighterIcon_f)player->getData().m_fighter, Select_Factor)
                },
                {
                    std::make_shared <ImageText>(teamStrings[(int)player->getData().team], getImagePlayerPostion(selectType::team, i), ScorecharacterSize)
                },
                {
                    std::make_shared <ImageText>(userString[(int)player->getData().m_commander], getImagePlayerPostion(selectType::Commander, i), ScorecharacterSize)
                },
                {
                    std::make_shared <ImageText>(std::to_string(int (*player->getScore())), getImagePlayerPostion(selectType::num, i), ScorecharacterSize)
                }

            });
        }
    return chartersdatamap;
 }


sf::Vector2f Score::getImagePlayerPostion(const selectType type, int i)
{
    switch (type)
    {
    case selectType::Commander:
        return sf::Vector2f(Score_User_Image_Start_Pos.x + (i % SelectImageInRow) * Score_User_Image_Space.x,
            Score_User_Image_Start_Pos.y + (i / SelectImageInRow) * Score_User_Image_Space.y);
    case selectType::fighter:
        return sf::Vector2f(Score_Fighter_Image_Start_Pos.x + (i % SelectImageInRow) * Select_Fighter_Image_Space.x,
            Score_Fighter_Image_Start_Pos.y + (i / SelectImageInRow) * Score_Fighter_Image_Space.y);
    case selectType::team:
        return sf::Vector2f(Score_team_Image_Start_Pos.x + (i % SelectImageInRow) * Score_team_Image_space_Pos.x,
            Score_team_Image_Start_Pos.y + (i / SelectImageInRow) * Select_team_Image_space_Pos.y);
    case selectType::num:
        return sf::Vector2f(Score_Score_Image_Start_Pos.x + (i % SelectImageInRow) * Score_Score_Image_space_Pos.x,
            Score_Score_Image_Start_Pos.y + (i / SelectImageInRow) * Score_Score_Image_space_Pos.y);
    default: return sf::Vector2f(0, 0);
    }

}
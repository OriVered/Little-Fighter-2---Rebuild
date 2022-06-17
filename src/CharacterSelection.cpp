#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(sf::RenderWindow& window, unsigned int numOfPlayers, unsigned int numOfCommander)
    :State(window, Bg_t::CharacterSelection), m_numOfPlayers(numOfPlayers), m_numOfCommander(numOfCommander),
    m_commanders(createCommanders()), m_fighters(createFighters()), m_teams(createTeams())
{
    srand((unsigned)time(NULL));
}

sf::Vector2f CharacterSelection::getImagePlayerPostion(const selectType type, int i)
{
    switch (type)
    {
    case selectType::Commander:
        return sf::Vector2f(Select_User_Image_Start_Pos.x + (i % SelectImageInRow) * Select_User_Image_Space.x,
            Select_User_Image_Start_Pos.y + (i / SelectImageInRow) * Select_User_Image_Space.y);
    case selectType::fighter:
        return sf::Vector2f(Select_Fighter_Image_Start_Pos.x + (i % SelectImageInRow) * Select_Fighter_Image_Space.x,
            Select_Fighter_Image_Start_Pos.y + (i / SelectImageInRow) * Select_Fighter_Image_Space.y);
    case selectType::team:
        return sf::Vector2f(Select_team_Image_Start_Pos.x + (i % SelectImageInRow) * Select_team_Image_space_Pos.x,
            Select_team_Image_Start_Pos.y + (i / SelectImageInRow) * Select_team_Image_space_Pos.y);
    default: return startWindow;
    }

}

std::vector <playerData> CharacterSelection::choose()
{
    createPlayerSelect(0);
    m_chooseIter = m_fighters.end()-1;
    resetFighterSelectPos(0);
     run();
    std::vector <playerData> loadChoosed;

    for (auto& player : m_playerData)
        loadChoosed.push_back(getPlayerData(player));

    return loadChoosed;
}
void CharacterSelection::draw()
{
    m_background->draw(m_window);
    /* Draw Menu */
    for (auto& player : m_playerData)
    {
        if (auto &image = player.m_commanderType.first) image->draw(m_window);
        if (auto& image = player.m_fighter.first) image->draw(m_window);
        if (auto& image = player.team.first)image->draw(m_window);
    }
    m_chooseIter->get()->draw(m_window);
}

void CharacterSelection::handleKeyPress(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:   handleLeftKey(); break;
    case sf::Keyboard::Right:  handleRightKey();  break;
    case sf::Keyboard::Enter:  handleEnterKey();   break;
    case sf::Keyboard::RShift: handleShiftKey();   break;
    default:                                       break;
    }
}

void CharacterSelection::resetFighterSelectPos(unsigned int i)
{
    for (auto& fighter : m_fighters)
        fighter->setPosition(getImagePlayerPostion(selectType::fighter, i));
}

void CharacterSelection::resetTeamSelectPos(unsigned int i)
{
    for (auto& team : m_teams)
        team->setPosition(getImagePlayerPostion(selectType::team, i));
}

void CharacterSelection::handleShiftKey()
{
    auto currPlayer = m_playerData.end() - 1;
    //handle choose fighter and move iterator to choose last player team
     if (auto choseiter = dynamic_cast<ImageTexture*>(m_chooseIter->get()))
    {

        resetTeamSelectPos(currPlayer->playerNum.second-1);    //reset position to last teams
        m_playerData.pop_back(); 
        if (m_playerData.empty())
        {
            m_isRunning = false;//pop last choosen
            return;
        }
        auto currPlayer1 = m_playerData.end() - 1;
        currPlayer1->team.first = nullptr;//assigment last choosed team image
        m_chooseIter = m_teams.begin();
    }
    //handle choose team and move iterator to choose fighter to current character
    else if (auto choseite1r = dynamic_cast<ImageText*>(m_chooseIter->get()))
    {
        currPlayer->m_fighter.first = nullptr;//assigment last choosed team image
        currPlayer->team.second = Team(m_chooseIter - m_teams.begin());//assigment last choosed Team

        resetFighterSelectPos(currPlayer->playerNum.second);//reset position to crrent Fighters
        m_chooseIter = m_fighters.end() - 1;
    }
}

void CharacterSelection::handleEnterKey()
{
    auto currPlayer = m_playerData.end() - 1;

    //handle choose fighter and move iterator to choose team
    if (auto choseiter = dynamic_cast<ImageTexture*>(m_chooseIter->get()))
    {
        currPlayer->m_fighter.second = Fighter_f(m_chooseIter - m_fighters.begin());//assigment last choosed Fighter_f
        currPlayer->m_fighter.first = std::make_shared<ImageTexture>(*(choseiter));//assigment last choosed fighter image
        resetTeamSelectPos(currPlayer->playerNum.second);    //reset position to crrent teams
        m_chooseIter = m_teams.end() - 1;
    }
    //handle choose team and move iterator to choose fighter to next character
    else if (auto choseiter2 = dynamic_cast<ImageText*>(m_chooseIter->get()))
    {
        currPlayer->team.first = std::make_shared<ImageText>(*(choseiter2));//assigment last choosed team image
        currPlayer->team.second = Team(m_chooseIter - m_teams.begin());//assigment last choosed Team
        resetFighterSelectPos(currPlayer->playerNum.second + 1);//reset position to current Fighters
        createPlayerSelect(currPlayer->playerNum.second + 1);//add new player
        m_chooseIter = m_fighters.end() - 1;//change choose iterator
        if (m_playerData.size()-1 == m_numOfPlayers)
        {
            m_isRunning = false;
            m_playerData.pop_back();
        }
    }

}

void CharacterSelection::handleRightKey()
{

    if (auto choseiter = dynamic_cast<ImageTexture*>(m_chooseIter->get()))
    {
        m_chooseIter++;
        if (m_chooseIter == m_fighters.end()) m_chooseIter = m_fighters.begin();
    }
    else if (auto choseiter2 = dynamic_cast<ImageText*>(m_chooseIter->get()))
    {
        m_chooseIter++;
        if (m_chooseIter == m_teams.end()) m_chooseIter = m_teams.begin();
    }
}

void CharacterSelection::handleLeftKey()
{

    if (auto choseiter = dynamic_cast<ImageTexture*>(m_chooseIter->get()))
    {
        if (m_chooseIter == m_fighters.begin()) m_chooseIter = m_fighters.end() - 1;
        else m_chooseIter--;
    }
    else if (auto choseiter2 = dynamic_cast<ImageText*>(m_chooseIter->get()))
    {
        if (m_chooseIter == m_teams.begin()) m_chooseIter = m_teams.end() - 1;
        else m_chooseIter--;
    }
}


void  CharacterSelection::createPlayerSelect(unsigned int PlayerNum)
{
    m_playerData.emplace_back(PlayerDataMap
            {
                {
                    std::make_pair(std::make_shared <ImageText>(userString[(int)CommandType::Computer], getImagePlayerPostion(selectType::Commander, PlayerNum), SelectioncharacterSize), CommandType::Computer)
                },{},
                {
                    std::make_pair(std::make_shared <ImageText>(std::to_string(PlayerNum), getImagePlayerPostion(selectType::num, PlayerNum)),  PlayerNum)
                },}); 


    //init first players with users commander
    if (PlayerNum < m_numOfCommander)
    {
        auto player = m_playerData.begin() + PlayerNum;
        if (auto choseiter = dynamic_cast<ImageText*>(m_commanders[PlayerNum].get()))
        {
            player->m_commanderType.second = (CommandType)PlayerNum;
            player->m_commanderType.first = std::make_shared<ImageText>(*(choseiter));
            player->m_commanderType.first->setPosition(getImagePlayerPostion(selectType::Commander, PlayerNum));
        }
    }
}

playerData CharacterSelection::getPlayerData(PlayerDataMap player)
{
    if (player.m_fighter.second == Fighter_f::random_f) player.m_fighter.second = (Fighter_f)numGenRand(numOfCharacters);
    if (player.team.second == Team::Random) player.team.second = (Team)numGenRand(maxOfTeams-1);

    return playerData{ player.m_commanderType.second, player.m_fighter.second, player.playerNum.second, player.team.second };
}



std::vector <std::shared_ptr<Image>> CharacterSelection::createCommanders()
{
    return
    {
        {std::make_shared<ImageText>(userString[(int)CommandType::ArrowUser], startWindow, SelectioncharacterSize) },
        {std::make_shared<ImageText>(userString[(int)CommandType::WASDUser], startWindow, SelectioncharacterSize) },
        {std::make_shared<ImageText>(userString[(int)CommandType::Computer], startWindow, SelectioncharacterSize) }
    };
}

std::vector <std::shared_ptr<Image>> CharacterSelection::createFighters()
{
    return
    {
        {std::make_shared<ImageTexture>(startWindow,  FighterIcon_f::dennis_f, Select_Factor) },
        {std::make_shared<ImageTexture>(startWindow,  FighterIcon_f::firzen_f, Select_Factor) },
        {std::make_shared<ImageTexture>(startWindow,  FighterIcon_f::firen_f, Select_Factor) },
        {std::make_shared<ImageTexture>(startWindow,  FighterIcon_f::freeze_f, Select_Factor) },
        {std::make_shared<ImageTexture>(startWindow,  FighterIcon_f::random_f, Select_Factor) }
    };
}

std::vector <std::shared_ptr<Image>> CharacterSelection::createTeams()
{
    return
    {
        {std::make_shared<ImageText>(teamStrings[(int)Team::Team_A], startWindow, SelectioncharacterSize)},
        {std::make_shared<ImageText>(teamStrings[(int)Team::Team_B], startWindow, SelectioncharacterSize)},
        {std::make_shared<ImageText>(teamStrings[(int)Team::Team_C], startWindow, SelectioncharacterSize)},
        {std::make_shared<ImageText>(teamStrings[(int)Team::Team_D], startWindow, SelectioncharacterSize)},
        {std::make_shared<ImageText>(teamStrings[(int)Team::Independent], startWindow, SelectioncharacterSize) },
        {std::make_shared<ImageText>(teamStrings[(int)Team::Random], startWindow, SelectioncharacterSize) }
    };
}
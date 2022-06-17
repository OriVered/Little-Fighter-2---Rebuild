#include "GameMode.h"

GameMode::GameMode(sf::RenderWindow& window, const Modes& mode)
    :State(window), m_mode(mode), m_timeToAddGift(rangeTimeToAddGift)
{}


void GameMode::createPlayers(std::vector < playerData > players)
{
	int i = 0;
	for(auto& player: players)
	{
		m_characters.emplace_back(std::make_shared <Fighter>(player, getStartPos(i)));

		if (player.m_fighter != Fighter_f::bandit_f)
			m_charactersInfo.emplace_back (m_characters[i]->getInfo());
			
		i++;
	}
	for (auto& player: m_characters)
	{
		player->setActionType(ActionType::DelayWalk);
		player->setActiveDelay(true);
	}
	
}


void GameMode::update()
{
	handleView();

	manageComputerAlgorithm();

	setAction();

	getDynamicAttacks();

	pollEvents();//get action from events

	auto delta = gameClock.restart();

	updateCharacters(delta);
     
	handleCollison();

	m_background->update(delta);

	checkAddGifts();

	std::erase_if(m_characters, [](const auto& plasyer) { return plasyer->isDead(); });
	std::erase_if(m_dynamicAttack, [](const auto& attack) { return attack->isDone(); });
	std::erase_if(m_gifts, [](const auto& gift) { return gift->isDone(); });

	if (endGame())
		Score(m_window, m_charactersInfo, m_isRunning).run();

	if (ResourceManager::instance().getSong((int)Type_s::gameTrack).getStatus() == sf::Sound::Status::Stopped)
        ResourceManager::instance().setSong((int)Type_s::gameTrack);
}

void GameMode::getDynamicAttacks()
{
	for (auto& player : m_characters)
	{
		auto attack = player->getDynamicAttacks();
		if (attack)
			m_dynamicAttack.push_back(attack);
	} 
}
void GameMode::updateCharacters(const sf::Time & delta)
{
	for (auto& player : m_characters)
	{
		player->move(delta);
		if(!isInsideBoard(player->getBotRight(), player->getBotLeft()))
			player->moveBack(delta);
		player->update(delta);
		
	}
	for (auto& dynamicAttack : m_dynamicAttack)
	{
		dynamicAttack->move(delta);
		if (!isInsideBoard(dynamicAttack->getBotRight(), dynamicAttack->getBotLeft()))
			dynamicAttack->moveBack(delta);
		dynamicAttack->update(delta);
	}
}

void GameMode::manageComputerAlgorithm()
{
	for (auto& player : m_characters)
	{
		if (player->getPlayerData().m_commander == CommandType::Computer)
		{
			auto target = minimumDistanceFighterTo(player);
			if (target)
				player->setTarget(target);
		}
	}
}

std::shared_ptr <Fighter> GameMode::minimumDistanceFighterTo(const std::shared_ptr <Fighter> fighter)
{
	sf::Vector2f closestPos;
	std::shared_ptr <Fighter> closestFighter;
	float closestDistance = WorldSize;

	for (auto& player : m_characters)
	{
		if ((player->getPlayerData().team != fighter->getPlayerData().team || player->getPlayerData().team == Team::Independent) &&
			 !player->isPasiveDelayed())
		{
			float distance = calcDistance(player->getPosition(), fighter->getPosition());
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestFighter = player;
			}

		}

	}
	return closestFighter;
}


void GameMode::handleCollison()
{
	//check and handle all pairs in characters
	for_each_pair(m_characters.begin(), m_characters.end(), [](auto& a, auto& b) { if (collide(*a, *b))	processCollision(*a, *b); });

	for (auto& attack : m_dynamicAttack)
		for (auto& character : m_characters)
			if (collide(*attack, *character))
				processCollision(*attack, *character);

	for (auto& gift : m_gifts)
		for (auto& character : m_characters)
			if (collide (*gift, *character))
				processCollision(*gift, *character);

}

void GameMode::setAction()
{
	for (auto& character : m_characters)
		if(!character->isPasiveDelayed() && !character->isActiveDelayed())
			character->setNextAction();
}

void GameMode::pollEvents()
{
    for (auto event = sf::Event(); m_window.pollEvent(event); )
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            handleClick(location);
            break;
        }
        case sf::Event::MouseMoved:
        {
            auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
            handleMove(location);
            break;
        }
           
        case sf::Event::KeyReleased:
        {
            handleKeyReleased(event.key.code);
            break;
        }
        default:        break;
        }
		
    }
}

void GameMode::handleKeyReleased(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
		m_isRunning = false;

	for (auto& player : m_characters)
	{
		if (player->getPlayerData().m_commander != CommandType::Computer)
			player->getActionFromKeyReleased(key);
	}
}


void GameMode::handleView()
{
	sf::View view = m_window.getView();
	sf::Vector2f pos = {0,0};
	auto Playerfocus = m_characters[0]->getPosition();//player position
	Playerfocus.y = WindowHeight / 2.f;

	/* left border scan */
	if (Playerfocus.x < WindowWidth / 4.f)
		view.setCenter(WindowWidth / 2, Playerfocus.y);
		

	/* right border scan */
	else if (WorldSize - Playerfocus.x < WindowWidth / 4.f)
		view.setCenter(ModesWorldSizeMap.find(m_mode)->second.width - WindowWidth / 2, Playerfocus.y);

	//normalize player focus 
	else if (Playerfocus.x < view.getCenter().x - WindowWidth /4 )
		view.setCenter(Playerfocus.x + WindowWidth / 4, Playerfocus.y);

	else if (Playerfocus.x > view.getCenter().x + WindowWidth / 4)
		view.setCenter(Playerfocus.x - WindowWidth / 4, Playerfocus.y);


	m_window.setView(view);


	for (auto& player : m_characters)
		player->setInfoView(view.getCenter().x - WindowWidth / 2.f);
}

void GameMode::draw()
{
	/* draw here */
	m_background->draw(m_window);
	
	//local sort by Y, to print in 3D, no change private member order
	auto it = m_characters;
	std::sort(it.begin(), it.end(), [](const std::shared_ptr<Fighter>& first, const std::shared_ptr<Fighter>& second) { return first->y() < second->y(); });

	for (const auto& character: it)
		character->draw(m_window);

	for (const auto& dynamicAttack : m_dynamicAttack)
		dynamicAttack->draw(m_window);

	for (const auto& gift : m_gifts)
		gift->draw(m_window);	


}



sf::Vector2f GameMode::getStartPos(const int character) const
{
	return sf::Vector2f(firstPos.x + character* xSpace, firstPos.y + character* ySpace);
}

bool GameMode::isInsideBoard(const sf::Vector2f& spriteBotleft, const sf::Vector2f& spriteBotright) const
{	
	auto ground = m_background->getGlobalBounds();
	return ground.contains(spriteBotleft) && ground.contains(spriteBotright);
}

bool GameMode::oneTeamRemaining() const
{
	auto team = m_characters.front()->getPlayerData().team;
	for (auto& character : m_characters)
	{
		if (character->getPlayerData().team != team)
			return false;
	}

	//checking if all of them are independent
	if (team == Team::Independent && m_characters.size() > 1)
		return false;
		
	return true;
}

void GameMode::checkAddGifts()
{
	
	if (m_clock.getElapsedTime().asSeconds() > m_timeToAddGift)
	{
		m_clock.restart();
		m_timeToAddGift = (float)(rand() % rangeTimeToAddGift) + mimimumTimeToAddGift;
		addGift();
		//ResourceManager::instance().playSFX(giftShowSound);
	}

}

void GameMode::addGift()
{
	auto &loc = m_window.getView().getCenter();
	int x = rand() % xRange - xStart;
	int y = rand() % yRange - yStart;

	sf::Vector2f finalLoc = {loc.x + x, loc.y + y};
	m_gifts.push_back(std::make_shared < LifeGift > (finalLoc));
}


bool GameMode::endGame()
{
	return oneTeamRemaining();
}

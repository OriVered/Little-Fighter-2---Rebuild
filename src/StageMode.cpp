#include "StageMode.h"



StageMode::StageMode(sf::RenderWindow& window)
	:GameMode(window, Modes::Stage),
	m_timeToDropEnemies(dropEnemyTime),
	m_enemiesDropped(0)
{
	createMode();
}

void StageMode::createMode()
{
	selection();

	setBackground(std::make_shared< SPBackground>(Modes::Stage));
}

void StageMode::selection()
{
	auto choosen = CharacterSelection(m_window, 1).choose();
	
	if (choosen.empty()) m_isRunning = false;
	
	for (unsigned int i = firstEnemy; i < startingLimit; i++)
		choosen.push_back(playerData{ CommandType::Computer, Fighter_f::bandit_f, i, Team::EnemyTeam });

	createPlayers(choosen);

}



void StageMode::updateCharacters(const sf::Time& delta)
{
	if (m_dropEnemiesClock.getElapsedTime().asSeconds() > m_timeToDropEnemies && m_enemiesDropped < maxEnemyDrops)
	{
		m_dropEnemiesClock.restart();
		addTwoEnemies();
		m_enemiesDropped++;
	}
	GameMode::updateCharacters(delta);
}



bool StageMode::endGame()
{
	return ( maxEnemyDrops <= m_enemiesDropped  && oneTeamRemaining());
}

void StageMode::addTwoEnemies()
{
	

	int sign = sgn (WorldSize/2 - m_characters[0]->getPosition().x );
	m_characters.emplace_back(std::make_shared <Fighter> (enemyData , sf::Vector2f{m_characters[0]->getPosition().x + sign * OffsetEnmeyPos.x, m_characters[0]->getPosition().y}));
	m_characters.emplace_back(std::make_shared <Fighter> (enemyData , sf::Vector2f{m_characters[0]->getPosition().x + sign * 1.5f * OffsetEnmeyPos.x	, m_characters[0]->getPosition().y - OffsetEnmeyPos.y}));
}


#pragma once

#include "GameMode.h"

class StageMode : public GameMode
{
public:
	StageMode(sf::RenderWindow& window);
	void createMode();
	void selection();
protected:
	void updateCharacters(const sf::Time& delta) override;
	void addTwoEnemies();
	bool endGame() override;
	sf::Clock m_dropEnemiesClock;
	int m_timeToDropEnemies;
	int m_enemiesDropped;
};

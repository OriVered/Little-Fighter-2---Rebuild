#pragma once

#include "macros.h"
#include "State.h"
#include "ImageTexture.h"
#include "ImageText.h"
#include "Utilities.h"

class CharacterSelection : public State
{ 
public:
	CharacterSelection(sf::RenderWindow& window, unsigned int numOfPlayers = 1, unsigned int numOfCommander = 1);

	/* draw */
	void draw() override;
	std::vector <playerData> choose();
	void handleView() override {};
	void handleClick(const sf::Vector2f& ) override {}
	void handleKeyPress(sf::Keyboard::Key key) override;
	void handleKeyPress() override {}
	void handleKeyReleased(sf::Keyboard::Key ) override {}
	void handleMove(const sf::Vector2f& ) override {}
private:
	using chooseIterator = std::vector<std::shared_ptr<Image>>::iterator;
	struct PlayerDataMap
	{
		std::pair<std::shared_ptr<Image>, CommandType> m_commanderType;
		std::pair<std::shared_ptr<Image>, Fighter_f> m_fighter;
		std::pair<std::shared_ptr<Image>, unsigned int >playerNum;
		std::pair<std::shared_ptr<Image>, Team >team;
	};

	std::vector < std::shared_ptr<Image>> m_commanders;
	std::vector < std::shared_ptr<Image>> m_fighters;
	std::vector < std::shared_ptr<Image>> m_teams;
	chooseIterator m_chooseIter;

	std::vector<PlayerDataMap >m_playerData;

	unsigned int m_numOfPlayers;
	unsigned int m_numOfCommander;

	/* Private Functions */
	sf::Vector2f getImagePlayerPostion(const selectType index, int i);
	void handleLeftKey();
	void handleRightKey();
	void handleEnterKey();
	void handleShiftKey();
	playerData getPlayerData(PlayerDataMap player);
	void createPlayerSelect(unsigned int numOfPlayers);
	void resetFighterSelectPos(unsigned int i);
	void resetTeamSelectPos(unsigned int i);
	std::vector < std::shared_ptr<Image>> createCommanders();
	std::vector < std::shared_ptr<Image>> createTeams();
	std::vector < std::shared_ptr<Image>> createFighters();
};


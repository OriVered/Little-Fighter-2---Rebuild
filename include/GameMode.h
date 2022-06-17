#pragma once

#include "macros.h"
#include "State.h"
#include "Score.h"
#include "CharacterSelection.h"
#include "Fighter.h"
#include "DennisBall.h"
#include "Collision.h"
#include "SPBackground.h"
#include "CWBackground.h"
#include "LifeGift.h"


class GameMode: public State
{
public:
	GameMode(sf::RenderWindow& window,const Modes& mode);
	void update() override;
	void draw() override;
	void handleView() override;

	void handleMove(const sf::Vector2f& ) override {}
	void pollEvents() override;

	void setAction();
	void manageComputerAlgorithm();
	void getDynamicAttacks();

protected:

	virtual sf::Vector2f getStartPos(const int character) const ;
	void addGift();
 	void createPlayers(std::vector < playerData > players);
	void checkAddGifts();
	bool isInsideBoard(const sf::Vector2f& spriteBotleft, const sf::Vector2f& spriteBotright) const;
	void handleClick(const sf::Vector2f& ) override {}
	void handleCollison();
	void handleKeyPress(sf::Keyboard::Key ) override {}
	void handleKeyPress() override {}
	void handleKeyReleased(sf::Keyboard::Key key) override;
	bool oneTeamRemaining() const;
	virtual void updateCharacters(const sf::Time& delta);
	virtual bool endGame();
	std::shared_ptr <Fighter> minimumDistanceFighterTo(const std::shared_ptr <Fighter> fighter);
	//CharacterSelection m_selection;
	using Players = std::vector<std::shared_ptr<Fighter>>;
	using DynamicAttacks = std::vector<std::shared_ptr<DynamicAttack>>;

	Players m_characters;
	DynamicAttacks m_dynamicAttack;
	Modes m_mode;
	std::vector < std::shared_ptr < CharacterInfo >> m_charactersInfo;
	std::vector < std::shared_ptr < LifeGift >> m_gifts;
	sf::Clock m_clock;
	float m_timeToAddGift;


};
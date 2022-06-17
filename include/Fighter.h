#pragma once
#include "macros.h"
#include "UserCommander.h"
#include "ComputerCommander.h"
#include "MovingObject.h"
#include "MainCharacterInfo.h"
#include "CharacterInfo.h"
#include "DennisBall.h"
#include "FirzenBall.h"
#include "FireAttack.h"
#include "IceAttack.h"

class Fighter : public MovingObject
{
public:
	Fighter(const playerData& PlayerData, const sf::Vector2f& pos);

	/* Draw */
	void draw(sf::RenderWindow& window) const override;

	/* Mutator */
	void update(const sf::Time& delta) override;

	void setNextAction();
	void setAction(const std::vector<Action>& actionsPressed);

	Direction setDir(const std::vector <Direction>& directionsPressed) const;
	void setCombo(const ActionType combo);
	void setTarget(const std::shared_ptr <Fighter> fighter) ;

	ActionType setActionTypeFromKeyboard(std::vector <ActionType>& actionsPressed, Direction& dir) const;
	void setInfoView(const float xPosition);
	void addHealth(const float health);
	void addScore(const float score);
	void decHealth(const float health);

	/* Accesors */
	playerData getPlayerData() const;
	bool isActiveDelayed() const;
	bool isPasiveDelayed() const;
	bool isDead() const;
	bool isGoingToDie() const;

	void getActionFromKeyReleased(const sf::Keyboard::Key& keyReleased);
	std::shared_ptr <DynamicAttack> getDynamicAttacks();
	std::shared_ptr <CharacterInfo> getInfo() const;
	
protected:
	const playerData m_playerData;
	ActionType m_combo;
	std::shared_ptr <Commander> m_commander;
	std::shared_ptr <CharacterInfo> m_info;
	std::shared_ptr <DynamicAttack> m_dynamicAttack;
	std::shared_ptr <Fighter> m_target;
	bool m_isDead;
	const float m_fighterSpeed;
	void setSpeed();
	
	void setComputerAction(ActionType& actionType, Direction& dir);
	void setUserAction(ActionType& actionType, Direction& dir);
	void setActionByCombo(ActionType& actionType, Direction& dir);
	void deathProcess();
	void activateCombo();
	void startCommander(const playerData& playerData);
	void startInfo(const playerData& playerData);
};
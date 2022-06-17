#pragma once
#include "macros.h"
#include "State.h"
#include "CharacterInfo.h"
#include "ImageText.h"
#include "MenuBackground.h"


class Score : public State
{
public:
	Score(sf::RenderWindow& window, std::vector < std::shared_ptr < CharacterInfo > >info, bool& isRunning);

	void handleView() override {}
	void draw() override;

protected:
	void handleClick(const sf::Vector2f& location) override;
	void handleKeyPress(sf::Keyboard::Key ) override {}
	void handleKeyPress() override {}
	void handleKeyReleased(sf::Keyboard::Key key) override;
	void handleMove(const sf::Vector2f& ) override {}

private:
	struct PlayerDataMap
	{
		std::shared_ptr<Image>m_fighter;
		std::shared_ptr<Image>m_team;
		std::shared_ptr<Image>m_commanderType;
		std::shared_ptr<Image>m_score;
	};
	using ChartersDataMap = std::vector<PlayerDataMap>;
	ChartersDataMap m_hartersDataMap;
	ChartersDataMap getPlayerDataMap(const std::vector < std::shared_ptr < CharacterInfo > >info);
	sf::Vector2f getImagePlayerPostion(const selectType type, int i);
};


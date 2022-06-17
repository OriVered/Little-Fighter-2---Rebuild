#pragma once

#include "macros.h"
#include "Commander.h"

class UserCommander: public Commander
{
public:
    UserCommander(const playerData& playerdata);
    std::pair< std::vector<ActionType>, std::vector<Direction> > getAction() const override;
    void getActionFromKeyReleased(const sf::Keyboard::Key& keyReleased);
    std::optional<ActionType> searchCombo();
    void update() override;
private:
    std::vector<sf::Keyboard::Key> m_possibleCombo;
	sf::Clock m_comboClock;

};
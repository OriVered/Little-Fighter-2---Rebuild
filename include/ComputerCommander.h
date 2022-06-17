#pragma once

#include "macros.h"
#include "Utilities.h"
#include "Commander.h"

class ComputerCommander : public Commander
{
public:
    ComputerCommander(const playerData& playerData);
    
    Action getActionFromAlgo(const sf::Vector2f& myPos, const sf::Vector2f& targetPos) override;
    void setComputerCombo(const sf::Vector2f& myPos, const sf::Vector2f& targetPos) override;
    Action setRandomAction() override;
    ActionType getRandomCombo() const;
    void update() override;

private:
    
    sf::Clock m_commanderClock;
    sf::Clock m_commanderComboClock;
    float m_timeFromComboToCombo;
    Action m_lastAction;
};
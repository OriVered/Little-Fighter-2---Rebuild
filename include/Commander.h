#pragma once
#include "macros.h"



class Commander
{
public:
    Commander(const playerData& playerData);
    virtual std::pair< std::vector<ActionType>, std::vector<Direction> > getAction() const { return {}; }
    virtual Action getActionFromAlgo(const sf::Vector2f& , const sf::Vector2f& ) { return {}; }
    virtual void setComputerCombo(const sf::Vector2f& , const sf::Vector2f& ) {}
    ActionType getCombo() const;
    virtual void update() = 0;

    void setCombo(ActionType combo);
    virtual Action setRandomAction() { return {}; }

protected:
    playerData m_playerData;
    ActionType m_combo;
};
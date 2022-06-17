#include "Commander.h"

Commander::Commander(const playerData& playerdata)
:m_playerData(playerdata), m_combo(ActionType::Standing)
{}


ActionType Commander::getCombo() const 
{
    return m_combo;
}

void Commander::setCombo(ActionType combo)
{
    m_combo = combo;
}
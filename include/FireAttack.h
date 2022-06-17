#pragma once

#include "macros.h"
#include "DynamicAttack.h"

class FireAttack: public DynamicAttack
{

public:
    FireAttack(const sf::Vector2f& pos, const playerData& ownerNum, std::shared_ptr<float> score);

    void update(const sf::Time& ) override;
    void moveBack(const sf::Time& ) override {};
};



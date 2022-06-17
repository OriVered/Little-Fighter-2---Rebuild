#pragma once

#include "macros.h"
#include "Fighter.h"
#include "LifeGift.h"

// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(GameObject& obj1, GameObject& obj2);
void punchCollision(Fighter& fighter, Fighter& enemy);

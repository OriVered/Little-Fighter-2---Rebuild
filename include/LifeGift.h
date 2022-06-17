#pragma once

#include "macros.h"
#include "GameObject.h"

class LifeGift: public GameObject
{

public:
    LifeGift(const sf::Vector2f& pos );

    void setDone();
    bool isDone() const;
    int getLife() const;
private:
    bool m_isDone;
    const int m_life;


};

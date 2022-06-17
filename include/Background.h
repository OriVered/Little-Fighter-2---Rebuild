#pragma once
#include "macros.h"
#include "ImageTexture.h"

class Background
{
public:
    /* Constructor / Distructor */
    Background() = default;
    virtual ~Background() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(sf::Time delta) = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
private:
};
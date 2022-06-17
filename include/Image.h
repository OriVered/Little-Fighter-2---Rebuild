#pragma once
#include "macros.h"

class Image
{
public:
    /* Constructor / Distructor */
    Image() = default;
    virtual ~Image() = default;

    /* draw */
    virtual void draw(sf::RenderWindow& window) const = 0;
    /* Accesors */
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual float getFactor() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;

    /* Mutator */
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual void setScale(const float x, const float y) = 0;
    virtual void setOrigin(const float x, const float y) = 0;
    virtual void setSize(const sf::Vector2u size) = 0;

private:
};

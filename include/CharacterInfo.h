#pragma once
#include "macros.h"
#include "Utilities.h"
#include "ImageTexture.h"


class CharacterInfo
{
public:
    CharacterInfo(const playerData& data, const float health);
    CharacterInfo(const playerData& data);

    void addHealth(const float power);
    virtual void addMana(const float) {}
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(const sf::Time& delta);
    virtual void initializeShapes(std::pair <sf::RectangleShape, sf::RectangleShape>& rectangles, const bool manaOrHealth);
    virtual void moveInfo(const float xPosition = 0, const float yPosition = 0);

    float getHealth() const;
    virtual float getMana() const { return 0; }
    playerData getData() const;
    virtual void addScore(const float ) {}
    virtual std::shared_ptr <float> getScore() const {return nullptr;}
    

protected:
    const playerData m_data;
    std::pair <sf::RectangleShape, sf::RectangleShape> m_healthShape;
    float m_health;

    sf::Clock m_infoClock;
};
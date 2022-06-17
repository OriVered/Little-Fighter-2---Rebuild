#pragma once
#include "CharacterInfo.h"


class MainCharacterInfo :public CharacterInfo
{
public:
    MainCharacterInfo (const playerData& data);

    void addMana(const float) override;
    void draw(sf::RenderWindow& window) const override;
    void update(const sf::Time& delta) override;
    void initializeShapes(std::pair <sf::RectangleShape , sf::RectangleShape>& rectangles, const bool manaOrHealth) override;
    void moveInfo(const float xPosition = 0, const float yPosition = 0) override;
    void addScore(const float score) override;
    std::shared_ptr <float> getScore() const override ;
    float getMana() const override;

private:
    std::pair <sf::RectangleShape, sf::RectangleShape> m_manaShape;
    float m_mana;
    sf::Clock m_infoClock;
    std::shared_ptr<float> m_score;
    std::shared_ptr <ImageTexture> m_icon;
};
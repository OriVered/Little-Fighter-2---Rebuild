#pragma once
#include "macros.h"
#include "Background.h"
#include "ImageTexture.h"

class MenuBackground : public Background
{
public:
    /* Constructor / Distructor */
    MenuBackground() = default;
    MenuBackground(const Bg_t objectTex);
    virtual ~MenuBackground() = default;
    void draw(sf::RenderWindow& window) const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    void update(sf::Time ) override{}
private:
    std::unique_ptr<ImageTexture> m_background;
};
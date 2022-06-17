#include "Animation.h"





Animation::Animation(const AnimationData& data, sf::Sprite& sprite, Direction dir)
    :m_data(data), m_sprite(sprite), m_dir(dir)
{
    update(Action { ActionType::Standing, Direction::Right } ); //initial state
}

Animation::~Animation()
{
}

// update for character
bool Animation::update (sf::Time delta, Action action)
{
    m_elapsed += delta;
    
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;

        m_index %= m_data.m_data.find(action.first) ->second.size();
        update(action);
    }
    return false;
}

void Animation::update(Action action)
{
    if (action.first == ActionType::DieBack)
    {
        const static sf::Color originalColor = m_sprite.getColor();

        fade ? m_sprite.setColor(transparentColor) : m_sprite.setColor(originalColor);
        fade = !fade;
        
    }

    m_sprite.setTextureRect(m_data.m_data.find(action.first)->second[m_index]);
    
    correctDir(m_sprite, action.second);
}

#pragma once
#include"macros.h"
#include"GameObject.h"


template <typename T1, typename T2>
struct ButtonDetails
{
	std::shared_ptr<T1> m_button;
	T2 type;
};



template <typename T> int sgn(T val)
{
    return int(T(0) < val) - (val < T(0));
}

template <typename FwdIt, typename Fn>
void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
{
    for (; begin != end; ++begin)
        for (auto second = begin + 1; second != end; ++second)
            fn(*begin, *second);
}

bool collide(GameObject& a, GameObject& b);
void correctDir(sf::Sprite&, Direction);
sf::Vector2f toVector(Direction dir = Direction::Stay);
Direction toDirection (const sf::Vector2f& victor);
Direction oppositeDir(Direction dir);
sf::Vector2f OpposideVector(Direction dir);
float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);
Direction TextureFacing(sf::Sprite& pic);
int numGenRand(const int maxRand);

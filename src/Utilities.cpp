#include "Utilities.h"



//if received direction left and looking right or received direction right and looking left
void correctDir(sf::Sprite& pic, Direction dir)
{
	if ((dir == Direction::Left && pic.getScale().x > 0) ||
        (dir == Direction::LeftUp && pic.getScale().x > 0) ||
        (dir == Direction::LeftDown && pic.getScale().x > 0) ||
        (dir == Direction::Right && pic.getScale().x < 0) ||
        (dir == Direction::RightUp && pic.getScale().x < 0) ||
		(dir == Direction::RightDown && pic.getScale().x < 0))
		pic.scale(-1, 1);
}



inline sf::Vector2f toVector(Direction dir)
{
    static const
        std::unordered_map<Direction, sf::Vector2f>
        dirToVector =
    {
        { Direction::Right     , { 1, 0 }  },
        { Direction::Left      , { -1, 0 } },
        { Direction::Up        , { 0, -1 } },
        { Direction::Down      , { 0, 1 }  },
        { Direction::Stay      , { 0, 0 }  },
        { Direction::LeftUp    , {-1, -1}  },
        { Direction::LeftDown  , {-1, 1}   },
        { Direction::RightUp   , {1, -1}   },
        { Direction::RightDown , {1, 1}    },
        { Direction::Stay      , {0, 0}    },
    };
    return dirToVector.at(dir);
}


//receiving only Vector2f from {-1,0,1}^2 (9 places)
Direction toDirection (const sf::Vector2f& vector)
{
    int vectorForMap = int(vector.x) * 3 + int(vector.y);

    static const
    std::unordered_map < int, Direction > vectorToDir = 
    {
    { -4,              Direction::LeftUp     },
    { -3,              Direction::Left       },
    { -2,              Direction::LeftDown   },
    { -1,              Direction::Up         },
    {  0,              Direction::Stay       },
    {  1,              Direction::Down       },
    {  2,              Direction::RightUp    },
    {  3,              Direction::Right      },
    {  4,              Direction::RightDown  },
    };

    return vectorToDir.at(vectorForMap);

}


 Direction oppositeDir(Direction dir)
{
    auto dirToVector = toVector(dir);
    return toDirection(sf::Vector2f(dirToVector.y, dirToVector.x));
}

 sf::Vector2f OpposideVector(Direction dir)
{
    auto dirToVector = toVector(dir);
    return -dirToVector;
}

 bool collide(GameObject& a, GameObject& b)
 {
     return a.collidWith(b);
 }

 float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
 {
     return float(sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2)));
 }

 Direction TextureFacing(sf::Sprite& pic) 
 {
     if (pic.getScale().x < 0 )
         return Direction::Left;
     return Direction::Right;
 }

 int numGenRand(const int maxRand)
 {
     auto random = (rand() % maxRand);
     return random;
 }
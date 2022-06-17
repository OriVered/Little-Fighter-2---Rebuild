#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <exception>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <ranges>
#include <utility>
#include <sstream>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include<format>
#include <sstream>
#include <map>
#include <typeinfo>
#include <typeindex>

/* Controller Consts */
const auto WindowColor =  sf::Color(249, 231, 159);
const unsigned int WorldSize = 3500;
const unsigned int WindowHeight = 1100;
const unsigned int WindowWidth = 1550;
const auto endScreen = sf::Vector2i(WindowWidth, WindowHeight);
const auto backgroundPos = sf::Vector2f(WindowWidth, WindowHeight);
const auto sizeScreen = sf::Vector2u(WindowWidth, WindowHeight);
const auto centerScreen = sf::Vector2i(WindowWidth/2, WindowHeight/2);
const auto backgroundFactor = sf::Vector2f(1.f, 1.f);
const auto mirrorFactor = sf::Vector2f(-1.f, 1.f);
const auto startWindow = sf::Vector2f(0.f, 0.f);
const float musicVolume = 20;
const float mute = 0;

enum class ActiveSelectType
{
    start, fighter, team, end
};

enum class selectType
{
    Commander, fighter, num, team
};


enum class Team
{
    Team_A, Team_B, Team_C, Team_D, Independent, Random, EnemyTeam
};
const unsigned int maxOfTeams = 6;
const std::string teamStrings[maxOfTeams] = { "Team_A", "Team_B", "Team_C", "Team_D","Independent", "Random"};

/* Background*/

const auto GroundStart = sf::Vector2f(0.f, 500.f);
const auto GroundWorld = sf::Vector2f(WorldSize, 400.f);
const auto GroundWindow = sf::Vector2f(WindowWidth, 400.f);
const int xRange = WindowWidth;
const int xStart = int(WindowWidth/2);
const int yRange = int(WindowHeight/2.5);
const int yStart = int(WindowHeight/9);


/* China Wall Background*/
const auto sp_wc_rd2_bg_width = sf::Vector2f(90.f, 155.f);
const auto sp_wc_rd3_bg_width = sf::Vector2f(100.f, 155.f);
const auto sp_wc_hill1_bg_width = sf::Vector2f(505.f, 300.f);
const auto sp_wc_sky_bg_width = sf::Vector2f(595.f, 300.f);
const auto wc_bg_roadStart_factor = sf::Vector2f(330.f, 145.f);
const auto wc_bg_roadEnd_factor = sf::Vector2f(-1.f, 1.f);
const auto wc_bg_road2_factor = sf::Vector2f(90.f, 65.f);
const auto wc_bg_road3_factor = sf::Vector2f(100.f, 35.f);
const auto wc_bg_hill1_factor = sf::Vector2f(600.f, 300.f);
const auto wc_bg_hill2Start_factor = sf::Vector2f(300.f, 200.f);
const auto wc_bg_hill2End_factor = sf::Vector2f(300.f, 200.f);
const auto wc_bg_sky_factor = sf::Vector2f(600.f, 300.f);

const auto wc_bg_roadStart_pos = sf::Vector2f(0.f, 360.f);
const auto wc_bg_roadEnd_pos = sf::Vector2f(WorldSize, 355.f);
const auto wc_bg_road2Start_pos = sf::Vector2f(150.f, 440.f);
const auto wc_bg_road3Start_pos = sf::Vector2f(0.f, 870.f);
const auto wc_bg_hill1_pos = sf::Vector2f(0.f, 180.f);
const auto wc_bg_hill2Start_pos = sf::Vector2f(50.f, 330.f);
const auto wc_bg_hill2End_pos = sf::Vector2f(WorldSize-50, 330.f);
const auto wc_bg_sky_pos = sf::Vector2f(330.f, 100.f);
const auto cw_bg_color = sf::Color(154, 110, 90);
const auto cw_bg_numOfRoad2fCopy = 35;
const auto cw_bg_numOfRoad3fCopy = 40;
const auto cw_bg_numBgOfCopy = 9;





/* Stanley Prison Background*/
const auto sp_bg_width = sf::Vector2f(600, 400);
const auto sp_bg_wall_1_factor = sf::Vector2f(600.f, 400.f);
const auto sp_bg_wall_2_factor = sf::Vector2f(285.f, 100.f);
const auto sp_bg_wall_3_factor = sf::Vector2f(285.f, 100.f);
const auto sp_bg_wall_4_factor = sf::Vector2f(223.f, 215.f);
const auto sp_bg_fire_factor = sf::Vector2f(2.f, 2.f);
const auto sp_bg_wall_1_start = sf::Vector2f(0, 150);
const auto sp_bg_wall_2_start = sf::Vector2f(-125.f, 460.f);//start and check size height
const auto sp_bg_wall_3_start = sf::Vector2f(-125.f, 460.f);//same as 2
const auto sp_bg_wall_4_start = sf::Vector2f(-89.f, 150);//check size end and check size height
const auto sp_bg_fire_start = sf::Vector2f(77.f, 183);//check size end and check size height
const auto bg_numOfCopy = 6;
const auto sp_bg_color = sf::Color(90, 78, 75, 255);

/* Textures  */
enum class Bg_t
{
    bg_menu, wall_1, wall_2, wall_3, wall_4, fire, road1, road2, road3, hill1, hill2, sky, lifeGift, CharacterSelection, GameScore, Help
};
const int numOfBgTextures = 16;

enum class Dynamic_t
{
    dennisBall_t, FirzenBall_t, FireAttack_t, IceAttack_t,
};
const unsigned int numOfDynamicAttack = 4;

enum class FighterIcon_f
{
    dennis_f, firzen_f, firen_f, freeze_f, random_f, bandit_f
};

enum class Fighter_f
{
	dennis_f, firzen_f, firen_f, freeze_f, random_f, bandit_f
};
const unsigned int numOfFighters = 6;
const unsigned int numOfCharacters = 4;


enum class CommandType
{
    ArrowUser, WASDUser, Computer
};
const std::string userString[3] = { "ArrowUser" ,"WASDUser", "Computer" };

struct playerData
{
	CommandType m_commander;
	Fighter_f m_fighter;
	unsigned int playerNum;
  Team team;
};

//Enemy consts
const auto dropEnemyTime = 12;
const auto OffsetEnmeyPos = sf::Vector2f(200.f,80.f);
static const playerData enemyData  = { CommandType::Computer, Fighter_f::bandit_f ,9, Team::EnemyTeam };

/* Fonts */
enum class Type_f
{
	algertxt, watchmen
};
const int numOfFonts = 2;
const std::string FontFiles[numOfFonts] = { "ALGER.TTF", "WATCHMEN.ttf" };


/* Sounds  */
const int mediumVol = 56;
const int volStep = 14;
const int volMax = 100;
const int volMin = 0;
enum class Type_s
{
    mainTrack,
    gameTrack,
	 giftDeleteSound,
     punchHitSound,
     iceAttackSound,
     fireExplosionSound,
     firzenCreateBall,
     firenBallExplosion,
     burningMan,
     dennisCreateBall
};
const int numOfSounds = 10;
const std::string SoundFiles[numOfSounds] = {"mainTrack.ogg", "gameTrack.ogg", "giftDeleteSound.ogg", "punch-hit.wav", "iceAttack.wav",
                                             "fireExplosion.wav", "firzenCreateBall.wav", "firenBallExplosion.wav", "burningMan.wav", "createDennisBall.wav" };

/* MovingObject Consts */
const float explosionSpeed = 100.f;
const float CharacterSpeed = 200.f;
const float sprintSpeed = 450.f;
const float jumpSpeed = 300.f;
const float fallSpeed = 100.f;
const float dwarfSpeed = 90.f;
const float dennisBallSpeed = 300.f;
const float scaleRatioY = 10.f;
const float scaleRatioX = 20.f;


/* Menu consts */
const int numOfButton = 3;
const int firstButton = 12;
const auto spaceButtons = 150.f;
const auto startButtons = 435.f;
const auto menuFactor = sf::Vector2f(1.f, 1.f);
const auto menuImagePosition = (sf::Vector2f)centerScreen;
const auto menuSize = sf::Vector2u(700, 950);
const auto buttonSize = sf::Vector2u(400, 150);

/* Character Selection */

const auto Select_Fighter_Image_Start_Pos = sf::Vector2f(463.f, 240.f);
const auto Select_Fighter_Image_Space = sf::Vector2f(383.f, 485.f);
const auto Select_team_Image_Start_Pos = sf::Vector2f(372.f, 370.f);
const auto Select_team_Image_space_Pos = sf::Vector2f(385.f, 485.f);
const auto Select_User_Image_Start_Pos = sf::Vector2f(372.f, 485.f);
const auto Select_User_Image_Space = sf::Vector2f(385.f, 485.f);
const auto Select_Score_Image_Start_Pos = sf::Vector2f(372.f, 500.f);
const auto Select_Score_Image_space_Pos = sf::Vector2f(385.f, 485.f);
const unsigned int SelectioncharacterSize = 27;
const auto SelectImageInRow = 3;
const auto TwoPlayers = 2;
const auto TwoCommanders = 2;


/* Score Consts */
const auto Score_Fighter_Image_Start_Pos = sf::Vector2f(410.f, 225.f);
const auto Score_Fighter_Image_Space = sf::Vector2f(383.f, 485.f);
const auto Score_team_Image_Start_Pos = sf::Vector2f(320.f, 360.f);
const auto Score_team_Image_space_Pos = sf::Vector2f(385.f, 485.f);
const auto Score_User_Image_Start_Pos = sf::Vector2f(320.f, 440.f);
const auto Score_User_Image_Space = sf::Vector2f(385.f, 485.f);
const auto Score_Score_Image_Start_Pos = sf::Vector2f(320.f, 510.f);
const auto Score_Score_Image_space_Pos = sf::Vector2f(385.f, 485.f);
const unsigned int ScorecharacterSize = 27;


/* Menu Select Button */
const auto Select_start_pos = sf::Vector2f(400.f, 400.f);
const auto Select_Factor = sf::Vector2f(1.58f, 1.58f);
const auto Select_Space = 100;


/* Menu Buttons const*/
const unsigned int menuCharacterSize =  40;
const auto AllVsAll_B = sf::Vector2f(600.f, 400);
const auto TwoPlayerMode_B = sf::Vector2f(580.f, 480);
const auto StageMode_B = sf::Vector2f(650.f, 560.f);
const auto Help_B = sf::Vector2f(720.f, 640.f);
const auto Exit_B = sf::Vector2f(720.f, 720.f);
const auto boldSize = 10.f;
const auto buttonColor = sf::Color::White;
const auto buttonThinkerColor = sf::Color::Black;

 /* info consts */
const auto infoWidth = 80.f;
const auto infoHeight = 10.f;
const auto healthColor = sf::Color(190, 65, 65, 220);
const auto healthBackColor = sf::Color(190, 65, 65, 100);
const auto manaColor = sf::Color(39, 95, 245);
const auto manaBackColor = sf::Color(39, 95, 245, 100);
const auto firstIconPosition = sf::Vector2(0.f, 43.f);
const auto firstInfoPosition = sf::Vector2(0.f, -30.f);
const auto iconFactor = sf::Vector2(0.5f, 0.5f);
const auto characterInfoWidth = 200.f;
const auto characterInfoHeight = 30.f;
const auto characterInfoSpace = 100.f;
const auto yAxisOffset = 43.f;
const auto shadowThickness = 2.f;
const bool isHealth = false;
const bool isMana = true;
const float noLife = 0.f;
const float maxLife = 80.f;
const float smallDifference = 1.f;
const float smallMovement = 0.1f;
const float fixX = 30.f;
const float fixY = 55.f;
const int manaUnity = 5;
const int numOfBars = 4;

/*Life consts*/
const auto lifeGiftFactor = sf::Vector2(0.5f, 0.5f);
const auto lifeRange = 30;
const auto minimumLife = 10;
const int mimimumTimeToAddGift = 8;
const int rangeTimeToAddGift = 5;


/*  Commander consts*/
const int comboTimeRange = 6;
const int minimumWaitForCombo = 4;
const float smallDistance = 8.f;
const float firstTime = 8.f;
const float smallXDistance = 35.f;
const float smallYDistance = 15.f;
const int numOfDirections = 7;
const float determinedTime = 1.f;
const float enoughDistanceToCombo = 50.f;
const float maxTimeToEnterCombo = 0.5;

/*  Fighter consts*/
const float yOffsetDennisBall = 14.f;
const float xOffsetDennisBall = 60.f;
const float yOffsetFirzenBall = 18.f;
const float xOffsetFirzenBall = 40.f;
const float yOffsetIceAttack = 55.f;
const float xOffsetIceAttack = 45.f;
const float ballRemoveMana = -150.f;
const float explosionRemoveMana = -100.f;
const float minXDistance = 80.f;
const float minYDistance = 50.f;


/* Mode Const */
enum class Modes
{
    AllVsAll, Stage, Practice
};
const int maxEnemyDrops = 3;
const int numOfPlayersAllVsAll = 4;
const auto xSpace = 100;
const auto ySpace = 40;

static const std::unordered_map < Modes, sf::FloatRect >
ModesWorldSizeMap =
{
  {   Modes::AllVsAll   ,      sf::FloatRect(GroundStart, GroundWindow)    },
  {   Modes::Stage      ,      sf::FloatRect(GroundStart, GroundWorld)     },
  {   Modes::Practice   ,      sf::FloatRect(GroundStart, GroundWindow)    }
};

/* Player const*/
const auto playerFactor = sf::Vector2f(2.f, 2.f);
const auto EnemyFactor = sf::Vector2f(1.7f, 1.7f);
const auto ballFactor = sf::Vector2f(0.73f, 0.73f);
const auto fireFactor = sf::Vector2f(2.5f, 2.f);
const auto iceFactor = sf::Vector2f(3.3f, 2.8f);
const auto playerSpeed = 1.f;
const auto enemySpeed = 0.3f;
const unsigned int firstEnemy = 1;
const unsigned int startingLimit = 3;

static const std::unordered_map < Fighter_f , float >
fighterSpeedData = 
{
  {   Fighter_f::dennis_f ,     playerSpeed},
  {   Fighter_f::firzen_f ,     playerSpeed},
  {   Fighter_f::firen_f ,     playerSpeed},
  {   Fighter_f::freeze_f ,     playerSpeed},
  {   Fighter_f::bandit_f ,     enemySpeed}

};

static const std::unordered_map < Fighter_f , sf::Vector2f >
fighterFactorData = 
{
  {   Fighter_f::dennis_f ,     playerFactor},
  {   Fighter_f::firzen_f ,     playerFactor},
  {   Fighter_f::firen_f ,     playerFactor},
  {   Fighter_f::freeze_f ,     playerFactor},
  {   Fighter_f::bandit_f ,     EnemyFactor}

};


enum class State_t
{
	AllVsAll,
	TwoPlayerMode,
	StageMode,
	Help,
  Exit,
};
 
enum class ActionType
{
    Beated, Bend, Burning, ComboA, ComboB, ComboC, Defend, DieBack, DieFront, Fading,
    Freezing, FallBack, FallFront, hit, Jump, MovingJump, Lift, OnFire, Punching,
    Roll, Smacked, SpecialDynamic, SpecialStatic, Sprinting, Standing,
    Walking, DelayWalk, CreateBall, CreateIce, ShotBall, Explosion, ShootBall, Wait,
};

enum class Direction
{
	Start, Right, Down, Left, Up, Stay, End, LeftUp, LeftDown, RightUp, RightDown,
};
using Action = std::pair <ActionType, Direction>;

//Animation
const auto AnimationTime = sf::seconds(0.1f);
const auto firstPos = sf::Vector2f(600.f, 600.f);
const auto transparentColor = sf::Color(1, 1, 1, 0);

/* Actions */
const auto ComboTime = sf::seconds(2.f);
const auto numOfCombos = 3;
const auto firstComboNum = 3;

//---------------------------------------------------------------------------------------------------
static const
std::vector < std::vector < std::pair < std::vector <sf::Keyboard::Key>, ActionType  >>> comboData =
{
    //Arrows commander combos
    {
      {{sf::Keyboard::Key::O ,sf::Keyboard::Key::P, sf::Keyboard::Key::O, sf::Keyboard::Key::P, sf::Keyboard::Key::P }, ActionType::ComboA},
      {{sf::Keyboard::Key::K, sf::Keyboard::Key::I, sf::Keyboard::Key::I, sf::Keyboard::Key::I                       }, ActionType::ComboB},
      {{sf::Keyboard::Key::J, sf::Keyboard::Key::K, sf::Keyboard::Key::I, sf::Keyboard::Key::O                       }, ActionType::ComboC}



    },
    //WASD commander combos
    {
      {{sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::G }, ActionType::ComboA},
      {{sf::Keyboard::Key::C, sf::Keyboard::Key::V, sf::Keyboard::Key::V, sf::Keyboard::Key::V                       }, ActionType::ComboB},
      {{sf::Keyboard::Key::V, sf::Keyboard::Key::B, sf::Keyboard::Key::F, sf::Keyboard::Key::F                       }, ActionType::ComboC}
    }
};

//---------------------------------------------------------------------------------------------------
static const
std::vector<std::vector<std::pair < sf::Keyboard::Key, Direction >>>
mapKeyboardToDir =
{
  {
      {sf::Keyboard::Key::Right    ,  Direction::Right  },
      {sf::Keyboard::Key::Left     ,  Direction::Left   },
      {sf::Keyboard::Key::Up       ,  Direction::Up     },
      {sf::Keyboard::Key::Down     ,  Direction::Down   }
  },

  {
      { sf::Keyboard::Key::D       ,  Direction::Right  },
      { sf::Keyboard::Key::A       ,  Direction::Left   },
      { sf::Keyboard::Key::W       ,  Direction::Up     },
      { sf::Keyboard::Key::S       ,  Direction::Down   }

  }
};

//---------------------------------------------------------------------------------------------------
static const
std::vector < std::pair < std::vector < Direction >, Direction > >
finalDirection =
{
  { { Direction::Right                  },              Direction::Right      },
  { { Direction::Right, Direction::Down },              Direction::RightDown  },
  { { Direction::Right, Direction::Up   },              Direction::RightUp    },
  { { Direction::Left                   },              Direction::Left       },
  { { Direction::Left, Direction::Up    },              Direction::LeftUp     },
  { { Direction::Left, Direction::Down  },              Direction::LeftDown   },
  { { Direction::Up                     },              Direction::Up         },
  { { Direction::Down                   },              Direction::Down       }
};

//---------------------------------------------------------------------------------------------------
static const
std::vector<std::vector < std::pair < sf::Keyboard::Key, ActionType>>>
mapKeyboardToActionType =
{
  {
    { sf::Keyboard::Key::Enter     ,  ActionType::Punching   },
    { sf::Keyboard::Key::L         ,  ActionType::Defend     },
    { sf::Keyboard::Key::RShift    ,  ActionType::Jump       },
    { sf::Keyboard::Key::Space     ,  ActionType::Sprinting  },
    { sf::Keyboard::Key::Delete    ,  ActionType::Standing   }
  },
  {
    { sf::Keyboard::Key::T         ,  ActionType::Punching   },
    { sf::Keyboard::Key::Y         ,  ActionType::Defend     },
    { sf::Keyboard::Key::U         ,  ActionType::Jump       },
    { sf::Keyboard::Key::R       ,  ActionType::Sprinting  },
    { sf::Keyboard::Key::Delete    ,  ActionType::Standing   },

  }
};

//---------------------------------------------------------------------------------------------------
static const
std::vector<std::unordered_set < sf::Keyboard::Key >>
possibleComboKeys =
{
  //arrows possible keys to combo
  { sf::Keyboard::Key::I, sf::Keyboard::Key::O, sf::Keyboard::Key::P, sf::Keyboard::Key::K,
    sf::Keyboard::Key::N, sf::Keyboard::Key::M, sf::Keyboard::Key::J},

  //WASD possible keys to combo
  { sf::Keyboard::Key::Z, sf::Keyboard::Key::X, sf::Keyboard::Key::C, sf::Keyboard::Key::V,
    sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::B                        },
};

//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < ActionType, float >
delayOfAction =
{
  {   ActionType::Beated,             0.5f  },
  {   ActionType::Bend,               0.9f  },
  {   ActionType::Burning,            1.6f  },
  {   ActionType::ComboA,             0.3f  },
  {   ActionType::ComboB,             0.3f  },
  {   ActionType::Defend,             0.7f  },
  {   ActionType::DieBack,            2.f   },
  {   ActionType::DieFront,           0.6f  },
  {   ActionType::Fading,             0.6f  },
  {   ActionType::Freezing,           2.f  },
  {   ActionType::FallBack,           0.3f  },
  {   ActionType::FallFront,          0.6f  },
  {   ActionType::hit,                0.02f },
  {   ActionType::Jump,               0.6f  },
  {   ActionType::Lift,               0.6f  },
  {   ActionType::OnFire,             0.6f  },
  {   ActionType::Punching,           0.4f  },
  {   ActionType::Roll,               0.6f  },
  {   ActionType::Smacked,            0.4f  },
  {   ActionType::SpecialDynamic,     0.6f  },
  {   ActionType::SpecialStatic,      0.6f  },
  {   ActionType::CreateBall,         0.7f  },
  {   ActionType::CreateIce,          0.7f  },
  {   ActionType::Explosion,          1.5f  },
  {   ActionType::ShootBall,          1.5f  },
  {   ActionType::Wait,               0.8f  },
  {   ActionType::DelayWalk,          5.f  },
};

//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < ActionType, float >
speedOfAction =
{
  {   ActionType::Standing,           CharacterSpeed  },
  {   ActionType::Walking,            CharacterSpeed  },
  {   ActionType::DelayWalk,            CharacterSpeed  },
  {   ActionType::Beated,             CharacterSpeed  },
  {   ActionType::Bend,               CharacterSpeed  },
  {   ActionType::Burning,            CharacterSpeed  },
  {   ActionType::ComboA,             CharacterSpeed  },
  {   ActionType::Defend,             CharacterSpeed  },
  {   ActionType::DieBack,            CharacterSpeed  },
  {   ActionType::DieFront,           CharacterSpeed  },
  {   ActionType::Fading,             CharacterSpeed  },
  {   ActionType::Freezing,           CharacterSpeed  },
  {   ActionType::FallBack,           fallSpeed       },
  {   ActionType::FallFront,          fallSpeed       },
  {   ActionType::hit,                CharacterSpeed  },
  {   ActionType::Jump,               jumpSpeed       },
  {   ActionType::Lift,               CharacterSpeed  },
  {   ActionType::OnFire,             CharacterSpeed  },
  {   ActionType::Punching,           CharacterSpeed  },
  {   ActionType::Roll,               CharacterSpeed  },
  {   ActionType::Smacked,            CharacterSpeed  },
  {   ActionType::SpecialDynamic,     CharacterSpeed  },
  {   ActionType::Sprinting,          sprintSpeed     },
  {   ActionType::SpecialStatic,      CharacterSpeed  },
  {   ActionType::CreateBall,         CharacterSpeed  },
  {   ActionType::CreateIce,          CharacterSpeed  },
  {   ActionType::Explosion,          explosionSpeed  },
  {   ActionType::Wait,               explosionSpeed  },
};

//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < ActionType, ActionType > nextActionMap =
{
  {   ActionType::Beated,            ActionType::FallBack    },
  {   ActionType::Bend,              ActionType::FallBack    },
  {   ActionType::Burning,           ActionType::DieBack     },
  {   ActionType::CreateIce,         ActionType::FallBack    },
  {   ActionType::ComboA,            ActionType::FallBack    },
  {   ActionType::ComboB,            ActionType::FallBack    },
  {   ActionType::ComboC,            ActionType::FallBack    },
  {   ActionType::Defend,            ActionType::FallBack    },
  {   ActionType::DieBack,           ActionType::DieBack     },
  {   ActionType::DieFront,          ActionType::DieFront    },
  {   ActionType::Fading,            ActionType::FallBack    },
  {   ActionType::Freezing,          ActionType::DieBack     },
  {   ActionType::FallBack,          ActionType::DieBack     },
  {   ActionType::FallFront,         ActionType::DieFront    },
  {   ActionType::hit,               ActionType::FallBack    },
  {   ActionType::Jump,              ActionType::FallBack    },
  {   ActionType::Lift,              ActionType::FallBack    },
  {   ActionType::OnFire,            ActionType::FallBack    },
  {   ActionType::Punching,          ActionType::FallBack    },
  {   ActionType::Roll,              ActionType::FallBack    },
  {   ActionType::Smacked,           ActionType::FallBack    },
  {   ActionType::SpecialDynamic,    ActionType::FallBack    },
  {   ActionType::SpecialStatic,     ActionType::FallBack    },
};

static const
std::unordered_map <ActionType, ActionType> nextActionComboMap =
{
  {   ActionType::ComboA,             ActionType::CreateBall    },
  {   ActionType::ComboB,             ActionType::Bend          },
  {   ActionType::ComboC,             ActionType::CreateIce     },
  {   ActionType::CreateBall,         ActionType::ShootBall     },




};
//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < Direction, Direction >
firstStageJumpMap =
{
  { Direction::Right,         Direction::RightUp      },
  { Direction::RightUp,       Direction::RightUp      },
  { Direction::RightDown,     Direction::RightUp      },
  { Direction::Left,          Direction::LeftUp       },
  { Direction::LeftUp,        Direction::LeftUp       },
  { Direction::LeftDown,      Direction::LeftUp       },
  { Direction::Up,            Direction::Up           },
  { Direction::Down,          Direction::Up           },
  { Direction::Stay,          Direction::Up           },
};

//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < Direction, Direction >
secondStageJumpMap =
{
  { Direction::Right,         Direction::RightDown    },
  { Direction::RightUp,       Direction::RightDown    },
  { Direction::RightDown,     Direction::RightDown    },
  { Direction::Left,          Direction::LeftDown     },
  { Direction::LeftUp,        Direction::LeftDown     },
  { Direction::LeftDown,      Direction::LeftDown     },
  { Direction::Up,            Direction::Down         },
  { Direction::Down,          Direction::Down         },
  { Direction::Stay,          Direction::Down         },
};

//---------------------------------------------------------------------------------------------------
static const
std::unordered_set <ActionType >
canReapeatActionType = { ActionType::Sprinting, ActionType::Walking, ActionType::Jump, ActionType::Standing};
//---------------------------------------------------------------------------------------------------

static const
std::unordered_map < int, Direction >
randomMapDirection =
{
  { 0,              Direction::Right      },
  { 1,              Direction::RightDown  },
  { 2,              Direction::RightUp    },
  { 3,              Direction::Left       },
  { 4,              Direction::LeftUp     },
  { 5,              Direction::LeftDown   },
  { 6,              Direction::Up         },
  { 7,              Direction::Down       }
};
//---------------------------------------------------------------------------------------------------
static const
std::unordered_map < ActionType, float >
minimumManaMap = 
{
  { ActionType::ComboA    ,   170.f       },
  { ActionType::ComboB    ,   150.f       },
  { ActionType::ComboC    ,   100.f       },
  { ActionType::Standing  ,   0.f         }
};
//---------------------------------------------------------------------------------------------------
/* fighter Life Map */
const std::unordered_map < Fighter_f, float > fighterLife =
{
    {   Fighter_f::dennis_f,    200.f   },
    {   Fighter_f::firzen_f,    200.f   },
    {   Fighter_f::firen_f,     200.f   },
    {   Fighter_f::freeze_f,    200.f   },
    {   Fighter_f::bandit_f,   100.f    }
};
//---------------------------------------------------------------------------------------------------
const std::unordered_map < Fighter_f, float > punchPower =
{
    {   Fighter_f::dennis_f,    12.f   },
    {   Fighter_f::firzen_f,    8.f   },
    {   Fighter_f::firen_f,     10.f   },
    {   Fighter_f::freeze_f,    10.f   },
    {   Fighter_f::bandit_f,   7.f    }
};

/* Damage and mana consts */
const auto PunchDmg = 10.f;
const auto dennisBallDmg = 100.f;
const auto firzenBallDmg = 100.f;
const auto fireAttackDamage = 80.f;
const auto iceAttackDamage = 70.f;
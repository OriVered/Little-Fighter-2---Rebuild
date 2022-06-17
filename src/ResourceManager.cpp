#include "ResourceManager.h"

AnimationData ResourceManager::BgData() const
{
	const auto size = sf::Vector2i(20, 75);
	const auto initSpace = sf::Vector2i(2, 0);

	auto bgObj = AnimationData{};
	auto currentStart = sf::Vector2i(0, 0);;

	auto nextStart = [&]()
	{
		(currentStart.x += size.x + initSpace.x) %= (size.x + initSpace.x) * 7;
		return currentStart;
	};
	for (int repeat = 0; repeat < 7; repeat++)  bgObj.m_data[ActionType::Standing].emplace_back(nextStart(), size);

	return bgObj;
}

AnimationData ResourceManager::dennisBallData() const
{
	const auto size = sf::Vector2i(100, 100);
	const auto initSpace = sf::Vector2i(40, 40);

	auto Ball = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart.x += (size.x + initSpace.x);
		if (currentStart.x > (size.x + initSpace.x)  * 4)
		{
			(currentStart.x) %= (size.x + initSpace.x) * 4;
			(currentStart.y += size.y + initSpace.y) %= (size.y + initSpace.y) * 4;

		}

		return currentStart;
	};

	Ball.m_data[ActionType::CreateBall].emplace_back(currentStart, size);											//1

	for (int repeat = 0; repeat < 3; repeat++)  Ball.m_data[ActionType::ShotBall].emplace_back(nextStart(), size);//4

	for (int repeat = 0; repeat < 4; repeat++)  Ball.m_data[ActionType::Explosion].emplace_back(nextStart(), size);//8
	Ball.m_data[ActionType::Standing].emplace_back(currentStart, size);

	return Ball;
}


AnimationData ResourceManager::firzenBallData() const
{
	const auto size = sf::Vector2i(174, 90);
	const auto initSpace = sf::Vector2i(6, 10);

	auto Ball = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart.x += (size.x + initSpace.x);
		if (currentStart.x > (size.x + initSpace.x) * 4)
		{
			(currentStart.x) %= (size.x + initSpace.x) * 4;
			(currentStart.y += size.y + initSpace.y) %= (size.y + initSpace.y) * 4;

		}

		return currentStart;
	};

	Ball.m_data[ActionType::CreateBall].emplace_back(currentStart, size);											//1
	for (int repeat = 0; repeat < 1; repeat++)  Ball.m_data[ActionType::CreateBall].emplace_back(nextStart(), size);	//2

	for (int repeat = 0; repeat < 2; repeat++)  Ball.m_data[ActionType::ShotBall].emplace_back(nextStart(), size);//4

	for (int repeat = 0; repeat < 3; repeat++)  Ball.m_data[ActionType::Explosion].emplace_back(nextStart(), size);//8

	Ball.m_data[ActionType::Standing].emplace_back(currentStart, size);

	return Ball;
}

AnimationData ResourceManager::fireAttackData() const
{
	const auto size = sf::Vector2i(125, 125);
	const auto initSpace = sf::Vector2i(5, 5);

	auto explosion = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart.x += (size.x + initSpace.x);
		if (currentStart.x > (size.x + initSpace.x) * 5)
		{
			(currentStart.x) %= (size.x + initSpace.x) * 5;
			(currentStart.y += size.y + initSpace.y) %= (size.y + initSpace.y) * 5;

		}

		return currentStart;
	};

	explosion.m_data[ActionType::Explosion].emplace_back(currentStart, size);											//1
	for (int repeat = 0; repeat < 9; repeat++)  
	{
		explosion.m_data[ActionType::Explosion].emplace_back(currentStart, size);
		explosion.m_data[ActionType::Explosion].emplace_back(nextStart(), size);	//2	
	}
	explosion.m_data[ActionType::Standing].emplace_back(currentStart, size);

	return explosion;
}

AnimationData ResourceManager::iceAttackData() const
{
	const auto size = sf::Vector2i(60, 85);
	const auto initSpace = sf::Vector2i(7, 7);

	auto ice = AnimationData{};
	auto currentStart = initSpace;

	auto nextStart = [&]()
	{
		currentStart.x += (size.x + initSpace.x);
		if (currentStart.x > (size.x + initSpace.x) * 8)
		{
			(currentStart.x) %= (size.x + initSpace.x) * 8;
			(currentStart.y += size.y + initSpace.y) %= (size.y + initSpace.y) * 8;

		}

		return currentStart;
	};

	ice.m_data[ActionType::Explosion].emplace_back(currentStart, size);											//1
	for (int repeat = 0; repeat < 16; repeat++)  ice.m_data[ActionType::Explosion].emplace_back(nextStart(), size);
	
	ice.m_data[ActionType::Standing].emplace_back(currentStart, size);

	return ice;
}

AnimationData ResourceManager::dennisData() const
{
    const auto size = sf::Vector2i(59, 60);
    const auto initSpace = sf::Vector2i(1, 2);

    auto player = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 10)
        {
            currentStart.x %= size.x * 10;
            currentStart.y += size.y;
        }
        
        return currentStart;
    };

    player.m_data[ActionType::Standing].emplace_back(currentStart, size);												//0 1
    player.m_data[ActionType::Wait].emplace_back(currentStart, size);													//0 1
    
    for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Standing].emplace_back(nextStart(), size);	//0 3

    for (int repeat = 0; repeat < 5; repeat++) 
	{
		player.m_data[ActionType::Walking].emplace_back(nextStart(), size);		//0 8
		player.m_data[ActionType::DelayWalk].emplace_back(currentStart, size);		//0 8
	}

    for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::Punching].emplace_back(nextStart(), size);	//1 3

	for (int repeat = 0; repeat < 6; repeat++)  player.m_data[ActionType::CreateBall].emplace_back(nextStart(), size);	//1	9

	nextStart();																										//1 10
	
	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);	//2 3

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::CreateIce].emplace_back(nextStart(), size);		//2 6

	for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::ShootBall].emplace_back(nextStart(), size);	//2 10

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallBack].emplace_back(nextStart(), size);	//3 5
	
	player.m_data[ActionType::DieBack].emplace_back(nextStart(), size);													//3 6

	for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::OnFire].emplace_back(nextStart(), size);		//3 10

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallFront].emplace_back(nextStart(), size);	//4 5
	
	player.m_data[ActionType::DieFront].emplace_back(nextStart(), size);												//4 6

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Beated].emplace_back(nextStart(), size);		//4 9

	nextStart();																										//4 10

	for (int repeat = 0; repeat < 3; repeat++)  nextStart();															//5 3

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Beated].emplace_back(nextStart(), size);		//5 5

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Defend].emplace_back(nextStart(), size);		//5 8

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Roll].emplace_back(nextStart(), size);		//5 10

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Bend].emplace_back(nextStart(), size);		//6 2

	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Jump].emplace_back(nextStart(), size);		//6 3
	
	for (int repeat = 0; repeat < 4; repeat++)	nextStart();															//6 7

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Freezing].emplace_back(nextStart(), size);	//6 9


    return player;
}
AnimationData ResourceManager::banditData() const
{
    const auto size = sf::Vector2i(59, 60);
    const auto initSpace = sf::Vector2i(1, 12);

    auto player = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 11)
        {
            currentStart.x %= size.x * 11;
            currentStart.y += size.y;
        }
        
        return currentStart;
    };

    player.m_data[ActionType::Standing].emplace_back(currentStart, size);												//0	1
    player.m_data[ActionType::Wait].emplace_back(currentStart, size);													//0 1

    for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Standing].emplace_back(nextStart(), size);	//0 3

    for (int repeat = 0; repeat < 4; repeat++)
	{
		player.m_data[ActionType::Walking].emplace_back(nextStart(), size);
		player.m_data[ActionType::DelayWalk].emplace_back(currentStart, size);											//0 7
	}

    for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::Punching].emplace_back(nextStart(), size);	//0 11

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);	//1 3

	for (int repeat = 0; repeat < 8; repeat++)	nextStart();															//1 11

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallBack].emplace_back(nextStart(), size);	//2 5

	player.m_data[ActionType::DieBack].emplace_back(nextStart(), size);													//2 6

	for (int repeat = 0; repeat < 5; repeat++) nextStart();																//2 11

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallFront].emplace_back(nextStart(), size);	//3 5
	
	player.m_data[ActionType::DieFront].emplace_back(nextStart(), size);												//3 6

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Beated].emplace_back(nextStart(), size);		//3 9

	for (int repeat = 0; repeat < 2; repeat++) nextStart();																//3 11

	for (int repeat = 0; repeat < 6; repeat++) nextStart();																//4 6
	
	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Defend].emplace_back(nextStart(), size);		//4 8

	for (int repeat = 0; repeat < 3; repeat++) nextStart();																//4 11

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Bend].emplace_back(nextStart(), size);		//5 2

	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Jump].emplace_back(nextStart(), size);		//5 3

	for (int repeat = 0; repeat < 8; repeat++)  nextStart();															//5 11

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::OnFire].emplace_back(nextStart(), size);		//6 2
	
	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Freezing].emplace_back(nextStart(), size);	//6 3
	
	for (int repeat = 0; repeat < 8; repeat++)  nextStart();															//6 11
	
	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::OnFire].emplace_back(nextStart(), size);		//6 2
	
	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Freezing].emplace_back(nextStart(), size);	//6 3


    return player;
}

AnimationData ResourceManager::firzenData() const
{
    const auto size = sf::Vector2i(59, 60);
    const auto initSpace = sf::Vector2i(2, 2);
	

    auto player = AnimationData{};
    auto currentStart = initSpace;

    auto nextStart = [&]()
    {
        currentStart.x += size.x;
        if (currentStart.x > size.x * 10)
        {
            currentStart.x %= size.x * 10;
            currentStart.y += size.y;
        }
        
        return currentStart;
    };

    player.m_data[ActionType::Standing].emplace_back(currentStart, size);
    player.m_data[ActionType::Wait].emplace_back(currentStart, size);													//0 1

    for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Standing].emplace_back(nextStart(), size);	//0 3

    for (int repeat = 0; repeat < 5; repeat++)
	{
		player.m_data[ActionType::Walking].emplace_back(nextStart(), size);
		player.m_data[ActionType::DelayWalk].emplace_back(currentStart, size);											//0 7
	}


    for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Freezing].emplace_back(nextStart(), size);	//0 10

    for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::Punching].emplace_back(nextStart(), size);	//1 4
    
	for (int repeat = 0; repeat < 1; repeat++)	player.m_data[ActionType::CreateBall].emplace_back(nextStart(), size);	//1 5

	for (int repeat = 0; repeat < 1; repeat++)
	{
		player.m_data[ActionType::CreateBall].emplace_back(currentStart, size);	
		player.m_data[ActionType::CreateIce].emplace_back(currentStart, size);	
		player.m_data[ActionType::CreateIce].emplace_back(nextStart(), size);											//1 6
	}	
	
	for (int repeat = 0; repeat < 1; repeat++)
	{
		player.m_data[ActionType::CreateIce].emplace_back(currentStart, size);
		player.m_data[ActionType::CreateIce].emplace_back(currentStart, size);											//1 7	
		player.m_data[ActionType::CreateBall].emplace_back(nextStart(), size);	
	}
	for (int repeat = 0; repeat < 3; repeat++)	player.m_data[ActionType::CreateIce].emplace_back(nextStart(), size);	//1 10

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);	//2 3

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::Lift].emplace_back(nextStart(), size);		//2 8

	player.m_data[ActionType::Sprinting].emplace_back(nextStart(), size);												//2 9

	nextStart();																										//2 10

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallBack].emplace_back(nextStart(), size);	//3 5
	
	player.m_data[ActionType::DieBack].emplace_back(nextStart(), size);													//3 6
	
	nextStart();												 //the first picture of lifting (we dont wanna show )	//3 7

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::OnFire].emplace_back(nextStart(), size);		//3 9

	nextStart();																										//3 10

	for (int repeat = 0; repeat < 5; repeat++)  player.m_data[ActionType::FallFront].emplace_back(nextStart(), size);	//4 5

	player.m_data[ActionType::DieFront].emplace_back(nextStart(), size);												//4 6

	for (int repeat = 0; repeat < 3; repeat++)  player.m_data[ActionType::Beated].emplace_back(nextStart(), size);		//4 9

	for (int repeat = 0; repeat < 3; repeat++)	player.m_data[ActionType::CreateBall].emplace_back(nextStart(), size);	//5 2

	for (int repeat = 0; repeat < 4; repeat++)  player.m_data[ActionType::Smacked].emplace_back(nextStart(), size);		//5 6

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Defend].emplace_back(nextStart(), size);		//5 8
	
	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Roll].emplace_back(nextStart(), size);		//5 10

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::Bend].emplace_back(nextStart(), size);		//6 2
	
	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Jump].emplace_back(nextStart(), size);		//6 3
	
	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::ShootBall].emplace_back(nextStart(), size);	//6 5

	for (int repeat = 0; repeat < 2; repeat++)  nextStart();															//6 7

	for (int repeat = 0; repeat < 2; repeat++)  player.m_data[ActionType::OnFire].emplace_back(nextStart(), size);		//6 9
	
	for (int repeat = 0; repeat < 1; repeat++)  player.m_data[ActionType::Roll].emplace_back(nextStart(), size);		//6 10



    return player;
}


//makes an instance and is created only once
ResourceManager& ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}

sf::Texture* ResourceManager::getTexture(const Bg_t name)
{
	return &(m_bg_texture[name]);
}

sf::Texture* ResourceManager::getTexture(const Dynamic_t name)
{
	return &(m_dynamicAttack_texture[name]);
}


sf::Texture* ResourceManager::getTexture(const Fighter_f name)
{
	return &(m_fighters[name]);
}

sf::Texture* ResourceManager::getTexture(const FighterIcon_f name)
{
	return &(m_fighterIcon[name]);
}

sf::Font* ResourceManager::getFont(const Type_f name)
{
	return &(m_fonts[name]);
}

sf::Sound& ResourceManager::getSong(int name)
{
	return m_sounds[name];
}

sf::SoundBuffer& ResourceManager::getSound(const Type_s name)
{
	return m_soundBuff[name];
}

//Constructor
ResourceManager::ResourceManager()
	:m_fighters(numOfFighters), m_fighterIcon(numOfFighters),m_bg_texture(numOfBgTextures), m_fighterAnimationData(numOfFighters),
	m_attackAnimationData(numOfDynamicAttack), m_bgAnimationData(numOfBgTextures)
{
	/* Load Fonts */
	for (int i = 0; i < numOfFonts; i++)
		loadFont(FontFiles[i], (Type_f)i);

	/* load Sounds */
	for (int i = 0; i < numOfSounds; i++)
		loadSound(SoundFiles[i], (Type_s)i);

	/* Load Fighters Icon Textures */
	loadTexture("dennis_f.jpg", FighterIcon_f::dennis_f);
	loadTexture("firzen_f.jpg", FighterIcon_f::firzen_f);
	loadTexture("firen_f.jpg", FighterIcon_f::firen_f);
	loadTexture("freeze_f.jpg", FighterIcon_f::freeze_f);
	loadTexture("bandit_f.jpg", FighterIcon_f::bandit_f);
	loadTexture("random_f.jpg", FighterIcon_f::random_f);

	/* Load FIghters Textures */
	loadTexture("dennis_3.png", Fighter_f::dennis_f);
	loadTexture("firzen_4.png", Fighter_f::firzen_f);
	loadTexture("firen_0.png", Fighter_f::firen_f);
	loadTexture("freeze_1.png", Fighter_f::freeze_f);
	loadTexture("bandit_0.png", Fighter_f::bandit_f);
	loadTexture("random_f.jpg", Fighter_f::random_f);

	/* Load BacKground Textures */
	loadTexture("bg_main_menu.jpg", Bg_t::bg_menu);
	loadTexture("CharacterSelection.png", Bg_t::CharacterSelection);
	loadTexture("fire.png", Bg_t::fire);
	loadTexture("hill1.png", Bg_t::hill1);
	loadTexture("hill2.png", Bg_t::hill2);
	loadTexture("road1.png", Bg_t::road1);
	loadTexture("road2.png", Bg_t::road2);
	loadTexture("road3.jpg", Bg_t::road3);
	loadTexture("sky.jpg", Bg_t::sky);
	loadTexture("wall.jpg", Bg_t::wall_1);
	loadTexture("wall2.jpg", Bg_t::wall_2);
	loadTexture("wall3.jpg", Bg_t::wall_3);
	loadTexture("gift.png", Bg_t::lifeGift);
	loadTexture("GameScores.png", Bg_t::GameScore);
	loadTexture("Help.png", Bg_t::Help);
	


	/* Load Dynamic Attack Textures */
	loadTexture("dennis_chase.png", Dynamic_t::dennisBall_t);
	loadTexture("firzen_ball.png", Dynamic_t::FirzenBall_t);
	loadTexture("fire_explosion.png", Dynamic_t::FireAttack_t);
	loadTexture("IceAttack4.png", Dynamic_t::IceAttack_t);

	/* Load Fighters Animaitons */
	m_fighterAnimationData[int(Fighter_f::dennis_f)] = dennisData();	//0
	m_fighterAnimationData[int(Fighter_f::firzen_f)] = firzenData();	//1
	m_fighterAnimationData[int(Fighter_f::firen_f)] = firzenData();		//2
	m_fighterAnimationData[int(Fighter_f::freeze_f)] = firzenData();	//3
	m_fighterAnimationData[int(Fighter_f::bandit_f)] = banditData();	//4

	/* Load Background Animaitons */
	m_bgAnimationData[(int)Bg_t::fire] = BgData();	/* BG SP FIRE ANOMATION DATA*/

	/* Load Dynamic Attack Animaitons */
	m_attackAnimationData[(int)Dynamic_t::dennisBall_t] = dennisBallData();	/* Dennis ball ANIMATION DATA*/
	m_attackAnimationData[(int)Dynamic_t::FirzenBall_t] = firzenBallData();	/* Firzen ball ANIMATION DATA*/
	m_attackAnimationData[(int)Dynamic_t::FireAttack_t] = fireAttackData();	/* Fire Attack ANIMATION DATA*/
	m_attackAnimationData[(int)Dynamic_t::IceAttack_t] = iceAttackData();	/* Ice Attack ANIMATION DATA*/
	
																			
	setSounds();
}

void ResourceManager::loadTexture(const std::string& path, const FighterIcon_f name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	if (!temp.loadFromFile(path))
		throw std::runtime_error("Can't load file");
	m_fighterIcon[name] = temp;
}

void ResourceManager::loadTexture(const std::string& path, Fighter_f name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	if (!temp.loadFromFile(path))
		throw std::runtime_error("Can't load file");
	m_fighters[name] = temp;
	m_fighters[name].setSmooth(true);
}

void ResourceManager::loadTexture(const std::string& path, const Dynamic_t name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	if (!temp.loadFromFile(path))	
		throw std::runtime_error("Can't load file");
	
	m_dynamicAttack_texture[name] = temp;
	m_dynamicAttack_texture[name].setSmooth(true);
}

void ResourceManager::loadTexture(const std::string& path, const Bg_t name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	if (!temp.loadFromFile(path))
		throw std::runtime_error("Can't load file");
	m_bg_texture[name] = temp;
}

void ResourceManager::loadFont(const std::string& path, const Type_f name)
{
	sf::Font temp;
	temp.loadFromFile(path);
	m_fonts[name] = temp;
}

void ResourceManager::loadSound(const std::string& path, const Type_s name)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(path);
	m_soundBuff[name] = temp;
}

void ResourceManager::setSounds()
{
	for(int i = 0; i < numOfSounds; i++)
	{
		m_sounds.push_back(sf::Sound(getSound(Type_s(i))));
		m_sounds[i].setVolume(m_volume);
	}
}

void ResourceManager::stopAllSongs()
{
	for (auto& sound:m_sounds)
		sound.stop();
}

void ResourceManager::playSFX(Type_s sound)
{
	m_sounds[int(sound)].play();
}

void ResourceManager::playSong()
{
	stopAllSongs();
	m_sounds[int(m_playing)].play();
	m_sounds[int(m_playing)].setVolume(30);
}

void ResourceManager::setSong(const int song)
{
	m_playing = (Type_s)song;
	playSong();
}

void ResourceManager::volUp()
{
	if(m_volume+ volStep <volMax)
		m_volume += volStep;
	setVolumeAll();
}

void ResourceManager::volDown()
{
	if(m_volume-volStep >= volMin)
		m_volume -= volStep;
	setVolumeAll();
}

void ResourceManager::setVolumeAll()
{
	for (auto& sound:m_sounds)
		sound.setVolume(m_volume);
}

void ResourceManager::setVolumeSong(const Type_s , const float volume)
{
	m_sounds[int(m_playing)].setVolume(volume);
}
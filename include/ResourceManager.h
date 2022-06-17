//this class is singleton class
#pragma once

#include <unordered_map>
#include <string>
#include "macros.h"
#include "AnimationData.h"

class ResourceManager
{
public:
	//make the static event so we wont load the textures multiple times
	static ResourceManager& instance();
	sf::Texture* getTexture(const Bg_t);
	sf::Texture* getTexture(const Dynamic_t);
	sf::Texture* getTexture(const Fighter_f);
	sf::Texture* getTexture(const FighterIcon_f);
	sf::Font* getFont (const Type_f name);
	sf::Sound& getSong (const int name);
	void setSong(const int);
	void volUp();
	void volDown();
	void playSFX(Type_s sound);
	sf::SoundBuffer& getSound(const Type_s name);
	void setVolumeSong(const Type_s name, const float volume);
	const AnimationData& animationData(Fighter_f fighter) { return m_fighterAnimationData[(int)fighter]; }
	const AnimationData& animationData(Bg_t bg) { return m_bgAnimationData[(int)bg]; }
	const AnimationData& animationData(Dynamic_t attack) { return m_attackAnimationData[(int)attack]; }
private:

	ResourceManager(); //private ctor for singleton
	void loadTexture(const std::string& path, const Dynamic_t name);
	void loadTexture(const std::string& path, const Bg_t);
	void loadTexture(const std::string& path, const Fighter_f);
	void loadTexture(const std::string& path, const FighterIcon_f);
	void loadFont(const std::string& path, const Type_f name);
	void loadSound(const std::string& path, const Type_s name);
	void setSounds();
	void stopAllSongs();
	void playSong();
	void setVolumeAll();

	AnimationData dennisData() const;
	AnimationData firzenData() const;
	AnimationData banditData() const;
	AnimationData BgData() const;
	AnimationData dennisBallData() const;
	AnimationData firzenBallData() const;
	AnimationData fireAttackData() const;
	AnimationData iceAttackData() const;

	std::unordered_map<Bg_t, sf::Texture> m_bg_texture;
	std::unordered_map<Dynamic_t, sf::Texture> m_dynamicAttack_texture;
	std::unordered_map< FighterIcon_f, sf::Texture> m_fighterIcon;
	std::unordered_map<Fighter_f, sf::Texture> m_fighters;
	std::unordered_map<Type_f, sf::Font> m_fonts;
	std::unordered_map<Type_s, sf::SoundBuffer> m_soundBuff;
	
	std::vector <sf::Sound> m_sounds;
	std::vector <AnimationData> m_fighterAnimationData;
	std::vector <AnimationData> m_bgAnimationData;
	std::vector <AnimationData> m_attackAnimationData;
	Type_s m_playing;
	float m_volume = mediumVol;
};
#pragma once

class Game
{
public:
	Game();
	~Game() { };
	void setMusic(std::string path);
	void loadSounds();
	void playSound(int name);
	void animate(sf::Time time);
	void run();
	void initSprites();

private:
	void processEvents();
	void render();
	void handle_player_input(sf::Keyboard::Key key, bool cond);

private:
	static const sf::Time	globalTimer;
	
	sf::RenderWindow	mWindow;
	
	sf::Texture			mTBackground;
	sf::Sprite			mBackground;
	
	sf::Texture			mTShip;
	sf::Sprite			mShip;
	
	sf::Texture			mTShot;
	sf::Sprite			mShot;

	sf::Music			mMusic;
	
	sf::Sound			mSound;
	sf::SoundBuffer		shot1;
	sf::SoundBuffer		shot2;
	sf::SoundBuffer		engine;
	sf::SoundBuffer		win;
	sf::SoundBuffer		defeat;
};
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
	void pause();
	void render();
	void handle_player_input(sf::Keyboard::Key key, bool cond);

private:
	static const float		PlayerSpeed;
	static const sf::Time	GlobalTimer;
	
	sf::RenderWindow	mWindow;

	bool mIsPaused;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	
	sf::Texture			mTBackground;
	sf::Sprite			mBackground;
	
	sf::Texture			mTPause;
	sf::Sprite			mPause;
	
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
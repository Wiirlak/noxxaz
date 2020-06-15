#pragma once


#define WAVES 6
#define SIZENEMY 20

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void setMusic(std::string path);
	void loadSounds();
	void animate();
	void initSprites();
	void ResetSprites();
	void processEvents();
	void pause();
	void gameOver();
	void render();
	void handle_player_input(sf::Keyboard::Key key, bool cond);
	void handlePauseClick();
	void handleCollisions();
	void handleCollisionPlayer();
	void DisplayTexts();
	void pauseExit();
	void setPlayer();
	void setWaves(int waves = WAVES);
	void setBoss();
	void setWave(int wavex, int enemy);
	

private:
	static const float		PlayerSpeed;
	static const float		BackgroundSpeed;
	static const float		EnemySpeed;
	static const float		ProjectileSpeed;
	
	sf::RenderWindow		mWindow;

	bool mPlayerWin;
	bool mIsGameOver;
	bool mIsPaused;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	bool _IsPlayerWeaponFired = false;
	bool _IsSoundOn = false;
	bool _clickIsPressed = false;
	
	sf::Texture			mTBackground;
	sf::Sprite			mBackground;
	sf::Texture			mTPause;
	sf::Sprite			mPause;
	sf::Texture			mTVolumeOff;
	sf::Sprite			mVolumeOff;
	sf::Texture			mTVolumeOn;
	sf::Sprite			mVolumeOn;
	sf::Texture			mTVolumeText;
	sf::Sprite			mVolumeText;
	sf::Texture			mTPlayAgain;
	sf::Sprite			mPlayAgain;
	sf::Texture			mTLeave;
	sf::Sprite			mLeave;
	sf::Texture			mTLoose;
	sf::Sprite			mLoose;
	sf::Texture			mTVictory;
	sf::Sprite			mVictory;

	sf::Texture			mTShip;
	sf::Sprite			mShip;
	
	sf::Texture			mTShot;
	sf::Sprite			mShot;

	sf::Texture			_TextureEnemy;
	sf::Sprite			_Enemy[SIZENEMY];
	
	sf::Texture			mTBoss;
	sf::Sprite			mBoss;
	
	sf::Music			mMusic;
	
	sf::Sound			mSoundShot;
	sf::Sound			mSoundHit;
	sf::SoundBuffer		shot1;
	sf::SoundBuffer		shot2;
	sf::SoundBuffer		explode;
	sf::SoundBuffer		win;
	sf::SoundBuffer		defeat;
	sf::SoundBuffer		hitPlayer;
	sf::SoundBuffer		hitEnnemy;

	sf::Text 			lifeText;
	sf::Font			mFont;
};
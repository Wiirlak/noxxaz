#pragma once


#define WAVES 9
#define SIZENEMY 12
#define MINSIZENEMY 5 

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void setMusic(std::string path);
	void loadSounds();
	void render();
	void animate();
	void initSprites();
	void launchBossFireSequences();
	void ResetSprites();
	void processEvents();
	void pause();
	void gameOver();
	void pauseSwitch();
	void handle_player_input(sf::Keyboard::Key key, bool cond);
	void handlePauseClick();
	void handleCollisions();
	void DisplayTexts();
	void setPlayer();
	void setWaves(int waves = WAVES);
	void setBoss();
	void setWave(int wavex, int enemy);
	

private:
	static const float		PlayerSpeed;
	static const float		BackgroundSpeed;
	static const float		EnemySpeed;
	static const float		ProjectileSpeed;
	static const int		EnemyMissiles;

	sf::RenderWindow		mWindow;

	bool mPlayerWin;
	bool mIsGameOver;
	bool mIsPaused;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	bool _IsPlayerWeaponFired = false;
	bool _IsBossWeaponFired = false;
	bool _IsSoundOn = false;
	bool _IsMusicBossOn = false;
	bool _clickIsPressed = false;

	int  _currentOffScreenEnemyWeapon = 0;

	int _playerScore = 0;
	int _scorePerHit = 1000;
	int _scorePerHitEnemy = 500;
	int _scorePerDeathEnemy = 2250;
	int _scorePerDeathBoss = 4500;
	
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
	sf::Sprite			_Enemy[SIZENEMY+ MINSIZENEMY];
	
	sf::Texture			mTBoss;
	sf::Sprite			mBoss;

	sf::Texture			mTBossShot;
	sf::Sprite			mBossShot;
	
	sf::Music			mMusic;
	sf::Music			mMusicLoose;
	sf::Music			mMusicWin;
	sf::Music			mMusicBoss;
	
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

	sf::Text 			scoreText;

	sf::Image			icon;

	int					colorArray[8][3];
};
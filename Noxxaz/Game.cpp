﻿#include "pch.h"
#include "Game.h"

const float Game::PlayerSpeed = 5.0f;
const float Game::BackgroundSpeed = .1f;
const float Game::EnemySpeed = 0.5f;
const float Game::ProjectileSpeed = 0.5f;
const int Game::EnemyMissiles = 14;



Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "Noxxaz - Best Game ever")
	, mIsPaused(false)
	, mIsGameOver(false)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);
	mTBackground.loadFromFile("Media/Back/retro.png");
	mTPause.loadFromFile("Media/Sprites/pause.png");
	mTVolumeOn.loadFromFile("Media/Sprites/carre_checked.png");
	mTVolumeOff.loadFromFile("Media/Sprites/carre_not_checked.png");
	mTLeave.loadFromFile("Media/Sprites/leave.png");
	mTPlayAgain.loadFromFile("Media/Sprites/play_again.png");
	mTVolumeText.loadFromFile("Media/Sprites/music.png");
	mTShip.loadFromFile("Media/Sprites/spaceship.png");
	mTBoss.loadFromFile("Media/Sprites/Boss/boss.png");
	_TextureEnemy.loadFromFile("Media/Sprites/enemy.png");
	mFont.loadFromFile("Media/Fonts/MonsterFriendFore.otf");
	mTLoose.loadFromFile("Media/Sprites/loose.png");
	mTVictory.loadFromFile("Media/Sprites/victory.png");
	mTBossShot.loadFromFile("Media/Sprites/Missiles/shot_poulpi.png");

	initSprites();
	loadSounds();
	setMusic("Media/Music/Monkey Island 2020.ogg");

	if (!mMusicLoose.openFromFile("Media/Music/defeat.ogg"))
		std::cout << "FAILED TO PLAY THE MUSIC";
	mMusicLoose.setLoop(true);
	mMusicLoose.setVolume(100);

	if (!mMusicWin.openFromFile("Media/Music/victory.ogg"))
		std::cout << "FAILED TO PLAY THE MUSIC";
	mMusicWin.setLoop(true);
	mMusicWin.setVolume(100);

	if (!mMusicBoss.openFromFile("Media/Music/boss.ogg"))
		std::cout << "FAILED TO PLAY THE MUSIC";
	mMusicBoss.setLoop(true);
	mMusicBoss.setVolume(100);
}

void Game::setMusic(std::string path)
{
	if (!mMusic.openFromFile(path))
		std::cout << "FAILED TO PLAY THE MUSIC";
	mMusic.play();
	mMusic.setLoop(true);
}


void Game::loadSounds()
{
	shot1.loadFromFile("Media/Sounds/iceball.wav");
	shot2.loadFromFile("Media/Sounds/iceball.wav");
	hitPlayer.loadFromFile("Media/Sounds/rlaunch.wav");
	hitEnnemy.loadFromFile("Media/Sounds/Hitmarker_sound.wav");
	explode.loadFromFile("Media/Sounds/8bit_bomb_explosion.wav");
}

void Game::ResetSprites()
{
	_IsPlayerWeaponFired = false;
	_IsBossWeaponFired = false;
	_currentOffScreenEnemyWeapon = 0;
	_IsMusicBossOn = false;

	_playerScore = 0;

	EntityManager::m_Entities.clear();
	setPlayer();
	setWaves();
	setBoss();
	mBackground.setPosition(mBackground.getOrigin());
}

void Game::initSprites()
{
	_IsPlayerWeaponFired = false;
	_IsSoundOn = true;

	_currentOffScreenEnemyWeapon = 0;

	mBackground.setTexture(mTBackground);
	mBackground.scale(2, 2);

	mPause.setTexture(mTPause);
	mPause.setPosition((mWindow.getSize().x / 2) - mTPause.getSize().x /2, (mWindow.getSize().y / 4) - mTPause.getSize().y / 2 );

	mVictory.setTexture(mTVictory);
	mVictory.setPosition((mWindow.getSize().x / 2) - mTVictory.getSize().x / 2, (mWindow.getSize().y / 4) - mTVictory.getSize().y / 2 );
	
	mLoose.setTexture(mTLoose);
	mLoose.setPosition((mWindow.getSize().x / 2) - mTLoose.getSize().x / 2, (mWindow.getSize().y / 4) - mTLoose.getSize().y / 2);

	mVolumeText.setTexture(mTVolumeText);
	mVolumeText.setPosition(mPause.getPosition().x + mTPause.getSize().x / 2 - mTVolumeText.getSize().x / 2, mPause.getPosition().y + mTPause.getSize().y + 50);
	
	mVolumeOn.setTexture(mTVolumeOn);
	mVolumeOn.setPosition(mVolumeText.getPosition().x * 2, mVolumeText.getPosition().y - mTVolumeOn.getSize().y / 2);
	mVolumeText.setScale(0.5, 0.5);

	mVolumeOff.setTexture(mTVolumeOff);
	mVolumeOff.setPosition(mVolumeText.getPosition().x * 2, mVolumeText.getPosition().y - mTVolumeOff.getSize().y / 2);

	mPlayAgain.setTexture(mTPlayAgain);
	mPlayAgain.setPosition(mPause.getPosition().x + mTPause.getSize().x / 2 - mTVolumeText.getSize().x / 2, mVolumeText.getPosition().y + mTVolumeText.getSize().y);
	mPlayAgain.setScale(0.5, 0.5);

	mLeave.setTexture(mTLeave);
	mLeave.setPosition(mPause.getPosition().x + mTPause.getSize().x / 2 + 50, mVolumeText.getPosition().y + mTVolumeText.getSize().y);
	mLeave.setScale(0.5, 0.5);

	mShip.setTexture(mTShip);
	mShip.setPosition((mTShip.getSize().x / 2) * 0.3, mWindow.getSize().y / 2 - (mTShip.getSize().y / 2) * 0.1);
	mShip.scale(0.1, 0.1);
	mShip.rotate(90.0);

	mBoss.setTexture(mTBoss);
	mBoss.setPosition((mWindow.getSize().x * 2) - mTBoss.getSize().x, mWindow.getSize().y / 2 - mTBoss.getSize().y / 2);

	setPlayer();
	setWaves();
	setBoss();

	mBossShot.setTexture(mTBossShot);
	mBossShot.setScale(0.2, 0.2);

	lifeText.setFont(mFont);
	lifeText.setCharacterSize(70);
	lifeText.setPosition(0,mWindow.getSize().y - lifeText.getCharacterSize());

	scoreText.setFont(mFont);
	scoreText.setCharacterSize(35);
	scoreText.setPosition(mWindow.getSize().x / 2 - scoreText.getCharacterSize(), 0);


	icon.loadFromFile("Media/ico.png");
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::launchBossFireSequences()
{
	float angle = -( Game::EnemyMissiles / 5);
	for (int i = 0; i < Game::EnemyMissiles; i++) {
		mBossShot.setPosition(
			EntityManager::GetBoss()->m_sprite.getPosition().x + EntityManager::GetBoss()->m_sprite.getTexture()->getSize().x / 2,
			EntityManager::GetBoss()->m_sprite.getPosition().y + EntityManager::GetBoss()->m_sprite.getTexture()->getSize().y / 2);

		std::shared_ptr<Entity> enemyMasterWeapon = std::make_shared<Entity>();
		enemyMasterWeapon->m_sprite = mBossShot;
		enemyMasterWeapon->m_type = EntityType::enemyMasterWeapon;
		enemyMasterWeapon->damage = 10;
		enemyMasterWeapon->m_size = mTBossShot.getSize();
		enemyMasterWeapon->m_position = mBossShot.getPosition();
		enemyMasterWeapon->life = 15;
		enemyMasterWeapon->movement_x = 3;
		enemyMasterWeapon->movement_y = angle;
		if (std::rand() % 2 == 0)
			enemyMasterWeapon->rotate = 3;
		else
			enemyMasterWeapon->rotate = -3;
		
		angle += .43;
		EntityManager::m_Entities.push_back(enemyMasterWeapon);
	}
}

void Game::setBoss()
{
	std::shared_ptr<Entity> boss = std::make_shared<Entity>();
	boss->m_sprite = mBoss;
	boss->m_type = EntityType::boss;
	boss->damage = 15;
	boss->m_size = mTBoss.getSize();
	boss->m_position = mBoss.getPosition();
	boss->life = 500;
	EntityManager::m_Entities.push_back(boss);
}

void Game::setPlayer()
{
	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	player->m_sprite = mShip;
	player->m_type = EntityType::player;
	player->m_size = mTShip.getSize();
	player->m_position = mShip.getPosition();
	player->damage = 10;
	player->life = 50;
	EntityManager::m_Entities.push_back(player);
}

void Game::setWaves(int waves)
{
	float ecart = mWindow.getSize().x / waves;
	std::srand(time(0));
	for (int i = 0; i < waves; i++) {
		setWave(mWindow.getSize().x + (ecart * i), std::rand() % SIZENEMY + MINSIZENEMY) ;
	}
}

void Game::setWave(int wavex, int enemy)
{
	for (int i = 0; i < enemy; i++)
	{
		_Enemy[i].setTexture(_TextureEnemy);
		_Enemy[i].setScale(0.3, 0.3);
		_Enemy[i].setPosition(
			wavex + std::rand() % 50,
			std::rand() % int(mWindow.getSize().y - _Enemy[i].getTexture()->getSize().y * _Enemy[i].getScale().y)
		);
		std::shared_ptr<Entity> se = std::make_shared<Entity>();
		se->m_sprite = _Enemy[i];
		se->m_type = EntityType::enemy;
		se->m_size = _TextureEnemy.getSize();
		se->m_position = _Enemy[i].getPosition();
		se->damage = 10;
		se->life = 20;
		EntityManager::m_Entities.push_back(se);
	}
}

void Game::run()
{
    while (mWindow.isOpen())
    {
		processEvents();
    	if(!mIsPaused && !mIsGameOver)
    	{
			animate();
			handleCollisions();
    	}
		render();
		DisplayTexts();
    }
}

void Game::DisplayTexts() {
	int life =  EntityManager::GetPlayer()->life;
	std::string life_str = "";
	for (int i = 0; i < life / 10; i++) {
		life_str += "+";
	}
	if (life > 0) {
		if (life <= 10) {
			lifeText.setFillColor(sf::Color(235, 52, 83));
		}else if (life < 40) {
			lifeText.setFillColor(sf::Color(235, 52, 186));
		}
		else {
			lifeText.setFillColor(sf::Color(52, 235, 116));

		}
		lifeText.setString(life_str);
	}
	else {
		lifeText.setString("");
	}


	std::srand(std::time(nullptr));

	scoreText.setFillColor(sf::Color(52, 235, 116));

	scoreText.setString(std::to_string(_playerScore));
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
		mWindow.draw(entity->m_sprite);
	}
	if (mIsPaused) 
	{
		pause();
		handlePauseClick();
	}
	else if (mIsGameOver)
	{
		gameOver();
		handlePauseClick();
	}
	mWindow.draw(lifeText);
	mWindow.draw(scoreText);
	mWindow.display();
}

void Game::animate()
{
	float bgMove = mBackground.getPosition().x <= - float(mTBackground.getSize().x - 10) ? 0 : BackgroundSpeed;

	

	if (EntityManager::GetBoss()->m_sprite.getPosition().x <= mWindow.getSize().x 
		&& mMusicBoss.getStatus() != sf::SoundSource::Playing && _IsSoundOn)
	{
		mMusic.stop();
		mMusicBoss.play();
	}

	if (EntityManager::GetBoss()->m_sprite.getPosition().x <= mWindow.getSize().x
		&& !_IsBossWeaponFired) {
		launchBossFireSequences();
		_IsBossWeaponFired = true;
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		sf::Vector2f movement(.0f, .0f);
		if (entity->m_enabled == false)
		{
			continue;
		}
		else if (entity->m_type == EntityType::weapon)
		{
			movement.x = ProjectileSpeed;
			movement.x += 15;
			_IsPlayerWeaponFired = false;
		}
		else if (entity->m_type == EntityType::enemy)
		{
			if (entity->m_sprite.getPosition().x > mWindow.getSize().x) {
				movement.x = -BackgroundSpeed;
			}
			else {
				movement.x = -((double)std::rand() / (RAND_MAX)+2) * EnemySpeed;
			}
		}
		else if (entity->m_type == EntityType::boss)
		{
			movement.x = -bgMove;
		}
		else if (entity->m_type == EntityType::player)
		{
			if (mIsMovingUp && entity->m_sprite.getPosition().y > 0)
				movement.y -= PlayerSpeed;
			if (mIsMovingDown && entity->m_sprite.getPosition().y < mWindow.getSize().y - (mTShip.getSize().y * entity->m_sprite.getScale().y))
				movement.y += PlayerSpeed;
			if (mIsMovingRight && entity->m_sprite.getPosition().x < mWindow.getSize().x)
				movement.x += PlayerSpeed;
			if (mIsMovingLeft && entity->m_sprite.getPosition().x > 0 + (mTShip.getSize().x * entity->m_sprite.getScale().x))
				movement.x -= PlayerSpeed;
		}
		else if (entity->m_type == EntityType::enemyMasterWeapon) {
				movement.x -= entity->movement_x;
				movement.y -= entity->movement_y;
				entity->m_sprite.rotate(entity->rotate);
		}
		entity->m_sprite.move(movement);
	}
	mBackground.move(-bgMove, 0);
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handle_player_input(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handle_player_input(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::pause()
{
	mWindow.draw(mPause);
	if(_IsSoundOn)
		mWindow.draw(mVolumeOn);
	else
		mWindow.draw(mVolumeOff);

	mWindow.draw(mVolumeText);
	mWindow.draw(mPlayAgain);
	mWindow.draw(mLeave);
}

void Game::gameOver()
{
	mMusic.stop();
	mMusicBoss.stop();
	if (mPlayerWin) {
		mWindow.draw(mVictory);
		if(mMusicWin.getStatus() != sf::SoundSource::Playing)
			mMusicWin.play();
	}
	else {
		mWindow.draw(mLoose);
		if(mMusicLoose.getStatus() != sf::SoundSource::Playing)
			mMusicLoose.play();
	}
	mWindow.draw(mPlayAgain);
	mWindow.draw(mLeave);
}

void Game::handle_player_input(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::Z)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::Left || key == sf::Keyboard::Q)
	{
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
	{
		mIsMovingRight = isPressed;
	}
	if (key == sf::Keyboard::Space)
	{
		if (!isPressed) return;
		if (_IsPlayerWeaponFired)return;

		std::shared_ptr<Entity> sw = std::make_shared<Entity>();
		mTShot.loadFromFile("Media/Sprites/Missiles/pixel.png");

		sw->m_sprite.setTexture(mTShot);
		sw->m_sprite.setRotation(90);
		sw->m_sprite.setScale(0.2,0.2);
		sw->m_size = mTShot.getSize();
		sw->m_sprite.setPosition(
			EntityManager::GetPlayer()->m_sprite.getPosition().x,
			EntityManager::GetPlayer()->m_sprite.getPosition().y + EntityManager::GetPlayer()->m_sprite.getTexture()->getSize().x * 0.04);
		sw->m_type = EntityType::weapon;
		sw->damage = 5;
		EntityManager::m_Entities.push_back(sw);
		mSoundShot.setBuffer(shot1);
		mSoundShot.setVolume(50);
		mSoundShot.play();
		_IsPlayerWeaponFired = true;
	}
	if(key == sf::Keyboard::Escape)
	{
		if (!isPressed) return;
		if (mIsGameOver) mWindow.close();
		pauseSwitch();
	}
}

void Game::pauseSwitch()
{
	mIsPaused = !mIsPaused;
	mIsGameOver = false;
	if (mIsPaused)
	{
		mMusic.pause();
	}
	else
	{
		if (_IsMusicBossOn) {
			mMusicBoss.play();
		}
		else {
			mMusic.play();
		}
		_clickIsPressed = false;
	}
}

void Game::handlePauseClick()
{
	auto mouse_pos = sf::Mouse::getPosition(mWindow); // Mouse position relative to the window
	auto translated_pos = mWindow.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_clickIsPressed)
	{
		if (mVolumeOn.getGlobalBounds().contains(translated_pos) && _IsSoundOn) // Bouton volume On
		{
			// Rectangle-contains-point check
			// Mouse is inside the sprite.
			_IsSoundOn = false;
			_clickIsPressed = true;
			mMusic.setVolume(0);
			mMusic.pause();
			mMusicBoss.pause();
		}
		else if (mVolumeOff.getGlobalBounds().contains(translated_pos) && !_IsSoundOn) // Bouton volume Off
		{
			_IsSoundOn = true;
			mMusic.setVolume(100);
			_clickIsPressed = true;
			//mMusic.play();

		}
		else if (mLeave.getGlobalBounds().contains(translated_pos)) // Bouton quitter
		{
			mWindow.close();
		}
		else if (mPlayAgain.getGlobalBounds().contains(translated_pos)) // Bouton play again
		{
			ResetSprites();
			mMusic.stop();
			mMusicWin.stop();
			mMusicLoose.stop();
			pauseSwitch();
		}
	}else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_clickIsPressed = false;
	}
}

void Game::handleCollisions()
{
	std::shared_ptr<Entity> player = EntityManager::GetPlayer();
	sf::FloatRect boundPlayer = player->m_sprite.getGlobalBounds();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
		sf::FloatRect boundWeapon;
		boundWeapon = entity->m_sprite.getGlobalBounds();
		if (entity->m_type == EntityType::enemyMasterWeapon || // Enemy hit player
			entity->m_type == EntityType::enemy ||
			entity->m_type == EntityType::boss)
		{
			if (entity->m_type == EntityType::enemy)
			{
				if (entity->m_sprite.getPosition().x < 0 - (entity->m_sprite.getTexture()->getSize().x * entity->m_sprite.getScale().x))
				{
					player->life = player->life - entity->damage;
					_playerScore -= _scorePerHitEnemy;
					entity->m_enabled = false;
					break;
				}
			}
			if (boundWeapon.intersects(boundPlayer) == true)
			{
				mSoundHit.setBuffer(hitPlayer);
				mSoundHit.play();
				player->life = player->life - entity->damage;
				_playerScore -= _scorePerHitEnemy;
				if(entity->m_type != EntityType::boss) // Can't OS the boss
					entity->m_enabled = false;
				if (entity->m_type == EntityType::enemyMasterWeapon)
					_currentOffScreenEnemyWeapon++;
				break;
			}
			if (player->life <= 0) {
				mSoundHit.setBuffer(explode);
				mSoundHit.play();
				mPlayerWin = false;
				mIsGameOver = true;
			}
		}
		if (entity->m_type == EntityType::weapon) // Player shot enemy
		{
			if (entity->m_sprite.getPosition().x > mWindow.getSize().x)
			{
				entity->m_enabled = false;
			}
			for (std::shared_ptr<Entity> enemy : EntityManager::m_Entities)
			{
				if (enemy->m_enabled == false)
				{
					continue;
				}
				else if (enemy->m_type == EntityType::enemy || enemy->m_type == EntityType::boss)
				{
					sf::FloatRect boundEnemy;
					boundEnemy = enemy->m_sprite.getGlobalBounds();
					if(boundEnemy.intersects(boundWeapon) == true)
					{
						mSoundHit.setBuffer(hitEnnemy);
						mSoundHit.play();
						enemy->life = enemy->life - player->damage;
						if (enemy->life <= 0)
						{
							if (player->life < 70)
								player->life += 10;
							mSoundHit.setBuffer(explode);
							mSoundHit.play();
							enemy->m_enabled = false;
							if (enemy->m_type == EntityType::boss) {
								_playerScore += _scorePerDeathBoss;
								mPlayerWin = true;
								mIsGameOver = true;
							}
							else {
								_playerScore += _scorePerDeathEnemy;
							}
						}
						entity->m_enabled = false;
						_playerScore += _scorePerHit;
						break;
					}
				}

				else if(enemy->m_type == EntityType::enemyMasterWeapon)
				{
					sf::FloatRect boundMasterWeapon;
					boundMasterWeapon = enemy->m_sprite.getGlobalBounds();
					if (boundMasterWeapon.intersects(boundWeapon) == true)
					{
						mSoundHit.setBuffer(hitEnnemy);
						mSoundHit.play();
						enemy->life -= player->damage;
						if (enemy->life <= 0)
						{
							mSoundHit.setBuffer(explode);
							mSoundHit.play();
							enemy->m_enabled = false;
							_currentOffScreenEnemyWeapon++;
						}
						_playerScore -= _scorePerHitEnemy;
						entity->m_enabled = false;
						break;
					}
				}
			}
		}
		if (entity->m_type == EntityType::enemyMasterWeapon)
		{
			if (entity->m_sprite.getPosition().x < 0
				|| entity->m_sprite.getPosition().y <= - (entity->m_sprite.getTexture()->getSize().x * entity->m_sprite.getScale().x))
			{
				_currentOffScreenEnemyWeapon++;
				entity->m_enabled = false;
				_playerScore += _scorePerHit;
			}
		}
	}

	if (_currentOffScreenEnemyWeapon == Game::EnemyMissiles) {
		_IsBossWeaponFired = false;
		_currentOffScreenEnemyWeapon = 0;
	}

}
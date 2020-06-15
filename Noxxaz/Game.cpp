#include "pch.h"
#include "Game.h"

const float Game::PlayerSpeed = 5.0f;
const float Game::BackgroundSpeed = 0.1f;
const float Game::EnemySpeed = 0.5f;
const float Game::ProjectileSpeed = 0.5f;



Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "Noxxaz - Best Game ever")
	, mIsPaused(false)
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
	mTBoss.loadFromFile("Media/Sprites/Boss/frame_00_delay-0.08s.png");
	_TextureEnemy.loadFromFile("Media/Sprites/enemy.png");
	mFont.loadFromFile("Media/Fonts/MonsterFriendFore.otf");


	initSprites();

	loadSounds();
	setMusic("Media/Music/Monkey Island 2020.ogg");
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

	//
	//Background
	//
	mBackground.setTexture(mTBackground);
	mBackground.scale(2, 2);

	mPause.setTexture(mTPause);
	mPause.setPosition((mWindow.getSize().x / 2) - mTPause.getSize().x /2, (mWindow.getSize().y / 4) - mTPause.getSize().y / 2 );


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


	//
	//Player
	//
	mShip.setTexture(mTShip);
	mShip.setPosition((mTShip.getSize().x / 2) * 0.3, mWindow.getSize().y / 2 - (mTShip.getSize().y / 2) * 0.1);

	mShip.scale(0.1, 0.1);
	mShip.rotate(90.0);


	//
	//Boss
	//
	mBoss.setTexture(mTBoss);
	mBoss.setPosition((mWindow.getSize().x * 2) - mTBoss.getSize().x, mWindow.getSize().y / 2 - mTBoss.getSize().y / 2);


	setPlayer();
	setWaves();
	setBoss();

	lifeText.setFont(mFont);
	lifeText.setCharacterSize(70);
	lifeText.setPosition(0,mWindow.getSize().y - lifeText.getCharacterSize());
}


void Game::setBoss()
{
	std::shared_ptr<Entity> boss = std::make_shared<Entity>();
	boss->m_sprite = mBoss;
	boss->m_type = EntityType::boss;
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
	player->life = 50;
	EntityManager::m_Entities.push_back(player);
}

void Game::setWaves(int waves)
{

	float ecart = mWindow.getSize().x / waves;
	std::cout << "Debut spawn " + std::to_string(mWindow.getSize().x + ecart) << std::endl;
	std::cout << "fin d'ecran spawn " + std::to_string(mWindow.getSize().x *2 ) << std::endl;
	std::srand(time(0));

	for (int i = 0; i < waves; i++) {
		std::cout << "Vague  :" + std::to_string(i) + " start spawn : " + std::to_string(mWindow.getSize().x + (ecart * i)) << std::endl;
		setWave(mWindow.getSize().x + (ecart * i), std::rand() % SIZENEMY);
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
		std::cout << "Enemy :" + std::to_string(i) + " postition: "+ std::to_string(_Enemy[i].getPosition().x) << std::endl;

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
    	if (!mIsPaused)
    	{
				animate();
			handleCollisions();
    	} else
    	{
			pause();
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
		lifeText.setFillColor(sf::Color::Yellow);
		lifeText.setString("CHEH !");
	}

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
	mWindow.draw(lifeText);
	mWindow.display();
}


void Game::animate()
{
	float bgMove = mBackground.getPosition().x <= - float(mTBackground.getSize().x - 10) ? 0 : BackgroundSpeed;
	
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	//mShip.move(movement);
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		else if (entity->m_type == EntityType::weapon)
		{
			sf::Vector2f movement_weapon(ProjectileSpeed, 0.f);

			movement_weapon.x += 15;
			_IsPlayerWeaponFired = false;

			entity->m_sprite.move(movement_weapon);
		}

		else if (entity->m_type == EntityType::enemy)
		{
			if (entity->m_sprite.getPosition().x > mWindow.getSize().x) {
				sf::Vector2f movement2(-BackgroundSpeed, 0.f);
				entity->m_sprite.move(movement2);
			}
			else {
				sf::Vector2f movement2(-((double)std::rand() / (RAND_MAX)+2) * EnemySpeed, 0.f);
				entity->m_sprite.move(movement2);
			}

		}

		else if (entity->m_type == EntityType::boss)
		{
			entity->m_sprite.move(-bgMove, 0);
		}

		else if (entity->m_type == EntityType::player)
		{
			entity->m_sprite.move(movement);
		}

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

void Game::handle_player_input(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::Down)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::Left)
	{
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
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
			EntityManager::GetPlayer()->m_sprite.getPosition().y + EntityManager::GetPlayer()->m_sprite.getTexture()->getSize().x * 0.025);
		sw->m_type = EntityType::weapon;
		sw->damage = 5;
		EntityManager::m_Entities.push_back(sw);
		mSoundShot.setBuffer(shot1);
		mSoundShot.play();
		_IsPlayerWeaponFired = true;
	}

	if(key == sf::Keyboard::Escape)
	{
		if (!isPressed) return;
		pauseExit();
	}

}

void Game::pauseExit()
{
	mIsPaused = !mIsPaused;
	if (mIsPaused)
	{
		mMusic.pause();
	}
	else
	{
		mMusic.play();
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
		}
		else if (mVolumeOff.getGlobalBounds().contains(translated_pos) && !_IsSoundOn) // Bouton volume Off
		{
			_IsSoundOn = true;
			mMusic.setVolume(100);
			_clickIsPressed = true;
			mMusic.play();

		}
		else if (mLeave.getGlobalBounds().contains(translated_pos)) // Bouton quitter
		{
			mWindow.close();
		}
		else if (mPlayAgain.getGlobalBounds().contains(translated_pos)) // Bouton play again
		{
			ResetSprites();
			mMusic.stop();
			pauseExit();

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
		if (entity->m_type == EntityType::enemyWeapon || entity->m_type == EntityType::enemy) // Enemy hit player
		{
			if (entity->m_type == EntityType::enemy)
			{
				if (entity->m_sprite.getPosition().x < 0 - (entity->m_sprite.getTexture()->getSize().x * entity->m_sprite.getScale().x))
				{
					player->life = player->life - entity->damage;
					entity->m_enabled = false;
					break;
				}
			}
			if (boundWeapon.intersects(boundPlayer) == true)
			{
				mSoundHit.setBuffer(hitPlayer);
				mSoundHit.play();
				player->life = player->life - entity->damage;
				entity->m_enabled = false;
				break;
			}
			if (player->life <= 0) {
				mSoundHit.setBuffer(explode);
				mSoundHit.play();
				mIsPaused = true;
			}
		}
		else if (entity->m_type == EntityType::weapon) // Player shot enemy
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
				if (enemy->m_type == EntityType::enemy || enemy->m_type == EntityType::boss)
				{
					sf::FloatRect boundEnemy;
					boundEnemy = enemy->m_sprite.getGlobalBounds();
					if (boundEnemy.intersects(boundWeapon) == true)
					{
						mSoundHit.setBuffer(hitEnnemy);
						mSoundHit.play();
						if(player-> life < 70)
							player->life += (enemy->damage / 10);
						enemy->life = enemy->life - player->damage;
						if (enemy->life <= 0)
						{
							mSoundHit.setBuffer(explode);
							mSoundHit.play();
							enemy->m_enabled = false;
						}
						entity->m_enabled = false;
						break;
					}
				}
			}
		}
	}
}
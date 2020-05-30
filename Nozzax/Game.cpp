#include "pch.h"
#include "Game.h"

const std::string globalMedia = "E:\\Autre\\Ecole\\ESGI\\4AL\\c++\\noxxaz\\Media\\";
const sf::Time Game::GlobalTimer = sf::seconds(1.f / 60.f);
const float Game::PlayerSpeed = 10.0f;

Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "Noxxaz - Best Game ever")
	, mIsPaused(false)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);
	mTBackground.loadFromFile(globalMedia + "Back/retro.png");
	mTPause.loadFromFile(globalMedia + "Sprites/pause.png");
	mTVolumeOn.loadFromFile(globalMedia + "Sprites/carre_checked.png");
	mTVolumeOff.loadFromFile(globalMedia + "Sprites/carre_not_checked.png");
	mTLeave.loadFromFile(globalMedia + "Sprites/leave.png");
	mTPlayAgain.loadFromFile(globalMedia + "Sprites/play_again.png");
	mTVolumeText.loadFromFile(globalMedia + "Sprites/music.png");
	mTShip.loadFromFile(globalMedia + "Sprites/spaceship.png");
	initSprites();

	loadSounds();
	setMusic(globalMedia + "Music/Monkey Island 2020.ogg");
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
	shot1.loadFromFile(globalMedia + "Sounds/iceball.wav");
	mSound.setBuffer(shot1);
}

void Game::playSound(int name)
{
	mSound.play();
}

void Game::ResetSprites()
{
	_IsPlayerWeaponFired = false;

	EntityManager::m_Entities.clear();

	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	player->m_sprite = mShip;
	player->m_type = EntityType::player;
	player->m_size = mTShip.getSize();
	player->m_position = mShip.getPosition();
	EntityManager::m_Entities.push_back(player);

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

	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	player->m_sprite = mShip;
	player->m_type = EntityType::player;
	player->m_size = mTShip.getSize();
	player->m_position = mShip.getPosition();
	EntityManager::m_Entities.push_back(player);
	//
	// Explosion
	//
	//mWindow.getSize().y - (mTShip.getSize().y / 2) * 0.3

}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
		processEvents();
    	if (!mIsPaused)
    	{
			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			while (timeSinceLastUpdate > GlobalTimer)
			{
				timeSinceLastUpdate -= GlobalTimer;

				animate(GlobalTimer);
			}
			mBackground.move(-0.02, 0);
    	} else
    	{
			pause();
    	}
		render();
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
	mWindow.display();
}


void Game::animate(sf::Time time)
{
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

		if (entity->m_type == EntityType::weapon)
		{
			sf::Vector2f movement_weapon(1.f, 0.f);

			movement_weapon.x += 25;
			_IsPlayerWeaponFired = false;

			entity->m_sprite.move(movement_weapon);
			continue;
		}

		if (entity->m_type != EntityType::player)
		{
			continue;
		}

		

		entity->m_sprite.move(movement);
	}
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
		mTShot.loadFromFile(globalMedia + "Sprites/Missiles/pixel.png");

		sw->m_sprite.setTexture(mTShot);
		sw->m_sprite.setRotation(90);
		sw->m_sprite.setScale(0.2,0.2);
		sw->m_size = mTShot.getSize();
		sw->m_sprite.setPosition(
			EntityManager::GetPlayer()->m_sprite.getPosition().x,
			EntityManager::GetPlayer()->m_sprite.getPosition().y + EntityManager::GetPlayer()->m_sprite.getTexture()->getSize().x * 0.025);
		sw->m_type = EntityType::weapon;
		EntityManager::m_Entities.push_back(sw);
		playSound(1);
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
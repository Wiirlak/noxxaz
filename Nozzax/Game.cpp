#include "pch.h"
#include "Game.h"

const std::string globalMedia = "D:/ESGI/cpp/Nozzax/Media/";
const sf::Time Game::GlobalTimer = sf::seconds(1.f / 60.f);
const float Game::PlayerSpeed = 10.0f;

Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "Noxxax - Best Game ever")
	, mIsPaused(false)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);
	mTBackground.loadFromFile(globalMedia + "Back/retro.png");
	mTPause.loadFromFile(globalMedia + "Sprites/pause.png");
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

void Game::initSprites()
{
	//
	//Background
	//
	mBackground.setTexture(mTBackground);
	mBackground.scale(2, 2);
	mPause.setTexture(mTPause);
	mPause.setPosition((mWindow.getSize().x / 2) - mTPause.getSize().x /2, (mWindow.getSize().y / 2) - mTPause.getSize().y / 2);
	
	//
	//Player
	//
	mShip.setTexture(mTShip);
	mShip.scale(0.1, 0.1);
	mShip.setPosition((mTShip.getSize().x / 2) * 0.3, mWindow.getSize().y / 2 - (mTShip.getSize().y / 2) * 0.1);
	mShip.rotate(90.0);
	
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
	mWindow.draw(mShip);
	if (mIsPaused)
		mWindow.draw(mPause);
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

	mShip.move(movement);
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

		mTShot.loadFromFile(globalMedia + "Sprites/Missiles/pixel.png");
		mShot.setTexture(mTShot);
		mShot.setPosition(10.0,10.0);
		playSound(1);
	}

	if(key == sf::Keyboard::Escape)
	{
		if (!isPressed) return;
		mIsPaused = !mIsPaused;
		if (mIsPaused)
		{
			mMusic.pause();
		} else
		{
			mMusic.play();
		}
	}
}
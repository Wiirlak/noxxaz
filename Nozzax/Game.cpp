#include "pch.h"
#include "Game.h"


const sf::Time Game::globalTimer = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "SFML works!")
	, mTBackground()
	, mTShip()
{
	mWindow.setFramerateLimit(160);
	mTBackground.loadFromFile("D:/ESGI/cpp/Nozzax/Media/Back/retro.png");
	mTShip.loadFromFile("D:/ESGI/cpp/Nozzax/Media/Sprites/spaceship.png");
	initSprites();
}

void Game::initSprites()
{
	//
	//Background
	//
	mBackground.setTexture(mTBackground);
	mBackground.scale(2, 2);
	
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
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > globalTimer)
		{
			timeSinceLastUpdate -= globalTimer;

			animate(globalTimer);
		}
		mBackground.move(-0.02, 0);
		processEvents();
		render();
    }
}


void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mShip);
	mWindow.display();
}


void Game::animate(sf::Time time)
{
	
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


void Game::handle_player_input(sf::Keyboard::Key key, bool cond)
{
	if (key == sf::Keyboard::Up)
		mShip.setPosition(mShip.getPosition().x, mShip.getPosition().y - 10);
	else if (key == sf::Keyboard::Down)
		mShip.setPosition(mShip.getPosition().x, mShip.getPosition().y + 10);
	else if (key == sf::Keyboard::Left)
		mShip.setPosition(mShip.getPosition().x - 10, mShip.getPosition().y);
	else if (key == sf::Keyboard::Right)
		mShip.setPosition(mShip.getPosition().x + 10, mShip.getPosition().y);

	if (key == sf::Keyboard::Space)
	{
		std::cout << "SOTER";
	}
}
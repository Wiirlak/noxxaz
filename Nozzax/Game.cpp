#include "pch.h"
#include "Game.h"


Game::Game()
	: mWindow(sf::VideoMode(1280, 720), "SFML works!")
	, mTShip()
{
	mWindow.setFramerateLimit(160);
	mTShip.loadFromFile("D:/ESGI/cpp/Nozzax/Media/Sprites/spaceship.png");
	initSprites();
}

void Game::initSprites()
{

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
    while (mWindow.isOpen())
    {
		processEvents();
		render();
    }
}


void Game::render()
{
	mWindow.clear();
	mWindow.draw(mShip);
	mWindow.display();
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
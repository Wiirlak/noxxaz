#pragma once

class Game
{
public:
	Game();
	~Game() { };
	void run();
	void initSprites();

private:
	void processEvents();
	void render();
	void handle_player_input(sf::Keyboard::Key key, bool cond);

private:
	sf::RenderWindow	mWindow;
	sf::Texture			mTShip;
	sf::Sprite			mShip;
};
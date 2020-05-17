#pragma once

class Game
{
public:
	Game();
	~Game() { };
	void animate(sf::Time time);
	void run();
	void initSprites();

private:
	void processEvents();
	void render();
	void handle_player_input(sf::Keyboard::Key key, bool cond);

private:
	static const sf::Time	globalTimer;
	
	sf::RenderWindow	mWindow;
	sf::Texture			mTBackground;
	sf::Sprite			mBackground;
	sf::Texture			mTShip;
	sf::Sprite			mShip;
};
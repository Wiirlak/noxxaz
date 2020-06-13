#pragma once

enum EntityType
{
	player,
	weapon,
	enemyWeapon,
	enemyMasterWeapon,
	enemy,
	boss,
	block
};

class Entity
{
public:
	Entity() { };
	~Entity() { };

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	EntityType m_type;
	bool m_enabled = true;
	int life;
	int damage;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;
};


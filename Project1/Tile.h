#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"

enum class TileType { AIR, GRASS, WATER, FOREST, DIRT, BRICK };

class Tile
{
public:
	sf::Sprite m_TileSprite;
	sf::Vector2f m_TilePos;
	Animation m_TileAnimation;
	AnimatedSprite m_TileAnimatedSprite;
	int m_TileSize;
	TileType m_TileType;
	void draw(sf::RenderWindow& window, float dt);
	void update();
	Tile() {}
	Tile(Animation& tileAnimation, const TileType tileType);
	bool isSolid;
};

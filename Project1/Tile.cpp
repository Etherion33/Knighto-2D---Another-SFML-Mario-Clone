#include "Tile.h"

void Tile::draw(sf::RenderWindow & window, float dt)
{
	this->m_TileAnimatedSprite.play(m_TileAnimation);
	this->m_TileAnimatedSprite.update(sf::seconds(dt));

	window.draw(this->m_TileAnimatedSprite);
	//window.draw(this->m_TileSprite);
}

void Tile::update()
{
}

Tile::Tile(Animation& tileAnimation, const TileType tileType)
{
	this->m_TileSize = 8;
	this->m_TileType = tileType;
	this->m_TileAnimation = tileAnimation;

	this->m_TileAnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
}
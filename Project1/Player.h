#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>
#include <map>
#include "AnimatedSprite.h"
#include "Texture_Manager.h"
#include "EntityBase.h"

enum class DIRECTION { LEFT, RIGHT, UP, DOWN };

class Player : public EntityBase
{
private:
	sf::Vector2f direction;
	sf::Vector2f velocity;
	bool IsMoving = false;
public:
	void update(float dt);
	void draw(sf::RenderWindow & window, float dt);
	void move(float speedX, float speedY);
	void stop();
	bool isCollide() { return false; }

	Player() {}
	Player(const sf::Texture& texture, const sf::Texture& spritesheet);


	Animation getAnimation() { return currentAnimation; }
	sf::Vector2f getPlayerPos() { return this->m_Pos; }

	~Player();
};

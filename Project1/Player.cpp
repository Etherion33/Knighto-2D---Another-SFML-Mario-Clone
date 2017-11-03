#include "Player.h"
#include <iostream>

Player::Player(const sf::Texture& texture, const sf::Texture& spritesheet)
{
	this->m_Velocity = { 80.f , 80.f };
	this->m_Animations["idle"].setSpriteSheet(spritesheet);
	this->m_Animations["idle"].addFrame(sf::IntRect(24, 0, 24, 24));

	this->m_Sprite.setTexture(texture);
	this->m_Animations["left"].setSpriteSheet(spritesheet);
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(168, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(144, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));

	this->m_Animations["right"].setSpriteSheet(spritesheet);
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["up"].setSpriteSheet(spritesheet);
	this->m_Animations["up"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["down"].setSpriteSheet(spritesheet);
	this->m_Animations["down"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->currentAnimation = m_Animations["idle"];

	m_Pos.x = 50.f;
	m_Pos.y = 50.f;

	this->m_AnimatedSprite =  AnimatedSprite(sf::seconds(0.2), true, false);
	//m_PlayerSprite.setPosition(m_PlayerPos);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

void Player::draw(sf::RenderWindow& window, float dt)
{
	//movement.x = 0.0f;
	//movement.y = 0.0f;

	window.draw(this->m_AnimatedSprite);
	window.draw(this->m_Sprite);
	return;
}

void Player::move(float speedX, float speedY)
{
	if (speedX < 0 && speedY == 0)
	{
		this->currentAnimation = m_Animations["left"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX > 0 && speedY == 0)
	{
		this->currentAnimation = m_Animations["right"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX == 0 && speedY < 0)
	{
		this->currentAnimation = m_Animations["up"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX == 0 && speedY > 0)
	{
		this->currentAnimation = m_Animations["down"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
}

void Player::stop()
{
	this->m_AnimatedSprite.stop();
}

void Player::update(float dt)
{
	sf::Time frameTime = sf::seconds(dt);
	m_AnimatedSprite.play(currentAnimation);
	m_AnimatedSprite.move(this->velocity * frameTime.asSeconds());
	m_Pos = m_AnimatedSprite.getPosition();
	velocity = { 0.0f, 0.0f };
	m_AnimatedSprite.update(frameTime);

	//m_PlayerSprite.setPosition(m_PlayerPos);
}

Player::~Player()
{
}
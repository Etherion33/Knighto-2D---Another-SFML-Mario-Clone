#pragma once
#include <SFML\Graphics.hpp>

class Collision
{
public:
	Collision(sf::RectangleShape& rect);
	~Collision();

	void Move(float dx, float dy) { rect.move(dx, dy); }

	bool Collision::CheckCollision(Collision& other, float push);
	sf::Vector2f GetPosition() { return rect.getPosition(); }
	sf::Vector2f GetHalfSize() { return rect.getSize() / 2.0f; }

private:
	sf::RectangleShape& rect;
};

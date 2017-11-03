#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include <SFML\Graphics.hpp>
#include <vector>

class Animation
{
public:

	unsigned int startFrame;
	unsigned int endFrame;

	float duration;

	Animation(unsigned int startFrame, unsigned int endFrame, float duration)
		:startFrame(startFrame), endFrame(endFrame), duration(duration) {}

	unsigned int getLength() { return endFrame - startFrame + 1; }
};

class Animation_Handler
{
private:
	std::vector <Animation> animations;

	float t;

	int currentAnim;
public:
	void addAnim(Animation& anim);
	void update(const float dt);
	void changeAnim(unsigned int animNum);

	sf::IntRect bounds;
	sf::IntRect frameSize;

	Animation_Handler()
	{
		this->t = 0.0f;
		this->currentAnim = -1;
	}
	Animation_Handler(const sf::IntRect& frameSize)
	{
		this->frameSize = frameSize;
		this->t = 0.0f;
		this->currentAnim = -1;
	}
};


#endif // !ANIMATION_HANDLER_H

#include "Animation_Handler.h"

void Animation_Handler::update(const float dt)
{
	if (currentAnim >= this->animations.size() || currentAnim < 0) return;

	float duration = this->animations[currentAnim].duration;

	if (int((t + dt) / duration) > int(t / duration))
	{
		int frame = int((t + dt) / duration);

		frame %= this->animations[currentAnim].getLength();

		sf::IntRect rect = this->frameSize;
		rect.left = rect.width*frame;
		rect.top = rect.height * this->currentAnim;
		this->bounds = rect;
	}

	this->t += dt;
	if (this->t > duration * this->animations[currentAnim].getLength())
	{
		this->t = 0.0f;
	}
}

void Animation_Handler::addAnim(Animation& anim)
{
	this->animations.push_back(anim);
}

void Animation_Handler::changeAnim(unsigned int animID)
{
	if (this->currentAnim == animID || animID >= this->animations.size() || animID < 0) return;

	this->currentAnim = animID;

	sf::IntRect rect = this->frameSize;
	rect.top = rect.height * animID;
	this->bounds = rect;
	this->t = 0.0;
}
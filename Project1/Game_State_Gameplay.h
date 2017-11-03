#ifndef GAME_STATE_GAMEPLAY_H
#define GAME_STATE_GAMEPLAY_H

#include <SFML\Graphics.hpp>

#include "Game_State.h"
#include "Level.h"
#include "Player.h"

enum class ActionState { NONE, PANNING };

class Game_State_Gameplay : public Game_State
{
private:

	ActionState actionState;

	sf::View gameView;
	sf::View guiView;

	Level level;
	Player player;
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	Game_State_Gameplay(Game* game, std::string level);
};
#endif // !GAME_STATE_GAMEPLAY_H

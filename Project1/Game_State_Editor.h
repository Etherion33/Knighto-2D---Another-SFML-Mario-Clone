#ifndef GAME_STATE_EDITOR_H
#define GAME_STATE_EDITOR_H

#include <SFML\Graphics.hpp>
#include "Game_State.h"
#include "EntityBase.h"
#include "Player.h"
#include "Level.h"

class Game_State_Editor : public Game_State
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	void load_level(bool* p_open);
	void edit_level(Game* game, bool* p_open);
	Game_State_Editor(Game* game);
private:
	sf::View view;
	Player m_Player;
	Level m_Level;
};

#endif
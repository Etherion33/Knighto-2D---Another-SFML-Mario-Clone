#ifndef GAME_STATE_MENU_H
#define GAME_STATE_MENU_H

#include <SFML\Graphics.hpp>

#include "Game_State.h"

class Game_State_Menu : public Game_State
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	Game_State_Menu(Game* game);

private:
	sf::View view;
	void loadgame(std::string filename);
	void editLevel();
};

#endif // !GAME_STATE_MENU_H

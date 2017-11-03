#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Texture_Manager.h"
#include "Entity_Manager.h"
#include "Tile.h"
//#include "Player.h"

class Game_State;

class Game
{
private:
	void loadTextures();
	void loadTiles();
	void loadPlayer();

public:
	const static int tileSize = 16;
	std::stack<Game_State*> states;

	sf::RenderWindow window;
	Texture_Manager texmgr;
	Entity_Manager entmgr;
	sf::Sprite background;

	std::map<std::string, Tile> tileAtlas;
	//std::map<std::string, Player> playerAtlas;

	void pushState(Game_State* state);
	void popState();
	void changeState(Game_State* state);
	Game_State* peekState();

	void run();

	Game();
	~Game();
};

#endif // !GAME_H

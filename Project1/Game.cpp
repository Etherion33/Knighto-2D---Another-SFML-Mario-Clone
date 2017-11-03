#include <stack>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Game.h"
#include "Game_State.h"
#include "Player.h"

void Game::loadTextures()
{
	texmgr.load("grass", "Res/Textures/grass.png");
	texmgr.load("wood", "Res/Textures/wood.png");

	texmgr.load("knight", "Res/Textures/wood.png");
	texmgr.load("orc", "Res/Textures/orc.png");
	texmgr.load("knightSS", "Res/Textures/knight_outline.png");
	texmgr.load("orcSS", "Res/Textures/orc_middle_outline.png");
	texmgr.load("tileset", "Res/Textures/tileset.png");
	texmgr.load("background", "Res/Textures/bg.png");
}

void Game::loadTiles()
{
	std::map<std::string, Animation> staticAnim;
	staticAnim["air"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["air"].addFrame(sf::IntRect(56, 0, 8, 8));
	staticAnim["grass"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["grass"].addFrame(sf::IntRect(0, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(8, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(16, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(24, 0, 8, 8));
	staticAnim["dirt"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["dirt"].addFrame(sf::IntRect(0, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(8, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(16, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(24, 24, 8, 8));
	staticAnim["forest"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["forest"].addFrame(sf::IntRect(0, 48, 8, 8));
	staticAnim["water"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["water"].addFrame(sf::IntRect(0, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(8, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(16, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(24, 104, 8, 8));

	staticAnim["brick"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["brick"].addFrame(sf::IntRect(8, 168, 8, 8));

	this->tileAtlas["air"] = Tile(staticAnim["air"], TileType::AIR);
	this->tileAtlas["grass"] = Tile(staticAnim["grass"], TileType::GRASS);
	this->tileAtlas["dirt"] = Tile(staticAnim["dirt"], TileType::DIRT);
	this->tileAtlas["forest"] = Tile(staticAnim["forest"], TileType::FOREST);
	this->tileAtlas["water"] = Tile(staticAnim["water"], TileType::WATER);
	this->tileAtlas["brick"] = Tile(staticAnim["brick"], TileType::BRICK);
}

void Game::pushState(Game_State* state)
{
	this->states.push(state);
	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();
}

void Game::changeState(Game_State* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);
}

Game_State* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::run()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::Black);
		peekState()->draw(dt);
		ImGui::SFML::Render(this->window);
		this->window.display();
	}
}

Game::Game()
{
	this->loadTextures();
	this->loadTiles();
	//this->loadFonts();	//TODO
	//this->loadSounds();

	this->window.create(sf::VideoMode(1024, 768), "Knighto - 2D Platformer");
	this->window.setFramerateLimit(60);
	ImGui::SFML::Init(this->window);

	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty()) popState();
	ImGui::SFML::Shutdown();
}
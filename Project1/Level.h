#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <vector>

#include "Tile.h"
#include "Player.h"

class Level
{
private:
	std::vector<Tile> tiles;
	std::vector<Player> entities;
	std::vector <sf::Rect <int> > solidTiles;
public:

	int m_width, m_height;
	sf::Vector2f m_startPos;
	unsigned int m_TileSize;

	//void load(const std::string& filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas);

	void loadByText(const std::string & filename, std::map<std::string, Tile>& tileAtlas);

	void load(const std::string& filename, std::map<std::string, Tile>& tileAtlas);
	void save(const std::string & filename);
	void create(const std::string& filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas);
	void addEntity(Player* entity);

	void update(float dt);
	void draw(sf::RenderWindow& window, float dt);
	bool isColliding(const Player& other);
	Tile GetTile(unsigned int l_x, unsigned int l_y);
	Level()
	{
		this->m_TileSize = 8;
		this->m_width = 0;
		this->m_height = 0;
	}
	//Level(const std::string& filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas)

	Level(const std::string& filename, std::map<std::string, Tile>& tileAtlas)
	{
		this->m_TileSize = 8;
		//load(filename, width, height, tileAtlas);
		//load(filename, tileAtlas);
		loadByText(filename, tileAtlas);
	}
};

#include "Level.h"
#include <fstream>
#include <string>
//void Level::load(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas)

void Level::loadByText(const std::string & filename, std::map<std::string, Tile>& tileAtlas)
{
	std::ifstream inputFile;
	inputFile.open(filename, std::ios::in);
	if (inputFile.is_open()) {
		inputFile >> this->m_width;
		inputFile >> this->m_height;

		for (int pos = 0; pos < this->m_width * this->m_height; ++pos)
		{
			int type;
			inputFile >> type;
			switch (type)
			{
			default:
			case 0:
				this->tiles.push_back(tileAtlas.at("air"));
				break;
			case 1:
				this->tiles.push_back(tileAtlas.at("grass"));
				break;
			case 2:
				this->tiles.push_back(tileAtlas.at("forest"));
				break;
			case 3:
				this->tiles.push_back(tileAtlas.at("water"));
				break;
			case 4:
				this->tiles.push_back(tileAtlas.at("dirt"));
				break;
			case 5:
				this->tiles.push_back(tileAtlas.at("brick"));
				break;
			}
			Tile& tile = this->tiles.back();
		}
	}
	inputFile.close();
}

void Level::load(const std::string & filename, std::map<std::string, Tile>& tileAtlas)
{
	std::ifstream inputFile;
	inputFile.open(filename, std::ios::in | std::ios::binary);

	//this->width = width;
	//this->height = height;

	inputFile.read((char*)&this->m_width, sizeof(int));
	inputFile.read((char*)&this->m_height, sizeof(int));

	for (int pos = 0; pos < this->m_width * this->m_height; ++pos)
	{
		TileType tileType;
		inputFile.read((char*)&tileType, sizeof(int));
		switch (tileType)
		{
		default:
		case TileType::AIR:
			this->tiles.push_back(tileAtlas.at("air"));
			break;
		case TileType::GRASS:
			this->tiles.push_back(tileAtlas.at("grass"));
			break;
		case TileType::FOREST:
			this->tiles.push_back(tileAtlas.at("forest"));
			break;
		case TileType::WATER:
			this->tiles.push_back(tileAtlas.at("water"));
			break;
		case TileType::DIRT:
			this->tiles.push_back(tileAtlas.at("dirt"));
			break;
		case TileType::BRICK:
			this->tiles.push_back(tileAtlas.at("brick"));
			break;
		}
		Tile& tile = this->tiles.back();
	}

	inputFile.close();
}

void Level::create(const std::string& filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas)

{
	std::ofstream outputFile;
	std::ofstream outputFileText;

	this->m_width = width;
	this->m_height = height;

	for (unsigned int y = 0; y < this->m_height; ++y)
	{
		for (unsigned int x = 0; x < this->m_width; ++x)
		{
			sf::Vector2f pos;
			pos.x = x * this->m_TileSize;
			pos.y = y * this->m_TileSize;
			if(y==0){
				this->tiles.push_back(tileAtlas.at("brick"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::BRICK;
			}
			else if(y == (this->m_height - 1)){
				this->tiles.push_back(tileAtlas.at("brick"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::BRICK;
				this->tiles[y*this->m_width + x].isSolid = true;
			}
			else {
				this->tiles.push_back(tileAtlas.at("air"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::AIR;
				this->tiles[y*this->m_width + x].isSolid = false;

			}
		}
	}

	outputFile.open(filename, std::ios::out | std::ios::binary);
	outputFileText.open("testtext.dat", std::ios::out);
	outputFile.write((char*)&width, sizeof(int));
	outputFile.write((char*)&height, sizeof(int));
	outputFileText << width << std::endl;
	outputFileText << height << std::endl;
	for (auto tile : this->tiles)
	{
		outputFile.write((char*)&tile.m_TileType, sizeof(int));
		outputFileText <<(int)tile.m_TileType;
	}
	outputFile.close();
	outputFileText.close();
}

void Level::addEntity(Player * entity)
{
	this->entities.push_back(*entity);
}

void Level::save(const std::string & filename)
{
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::out | std::ios::binary);
	outputFile.write((char*)&m_width, sizeof(int));
	outputFile.write((char*)&m_height, sizeof(int));
	for (auto tile : this->tiles)
	{
		outputFile.write((char*)&tile.m_TileType, sizeof(int));
	}
	outputFile.close();
}

void Level::update(float dt)
{
}

void Level::draw(sf::RenderWindow& window, float dt)
{
	for (int y = 0; y < this->m_height; ++y)
	{
		for (int x = 0; x < this->m_width; ++x)
		{
			sf::Vector2f pos;
			pos.x = x * this->m_TileSize;
			pos.y = y * this->m_TileSize;
			//this->tiles[y*this->width + x].m_TileSprite.setPosition(pos);
			this->tiles[y*this->m_width + x].m_TileAnimatedSprite.setPosition(pos);

			/* Draw the tile */
			this->tiles[y*this->m_width + x].draw(window, dt);
		}
	}
}

bool Level::isColliding(const Player & other)
{
	return false;
}

Tile Level::GetTile(unsigned int l_x, unsigned int l_y)
{
	return this->tiles[l_y* this->m_width + l_x];
}

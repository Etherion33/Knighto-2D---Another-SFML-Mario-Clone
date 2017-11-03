#include "Texture_Manager.h"

void Texture_Manager::load(const std::string& name, const std::string& filename)
{
	/*	Load the texture	*/
	sf::Texture tex;
	tex.loadFromFile(filename);
	/* Add it to the list of textures */
	this->textures[name] = tex;
}

sf::Texture& Texture_Manager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}
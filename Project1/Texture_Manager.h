#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SFML\Graphics.hpp>

#include <string>
#include <map>

#include "Resource_Manager.h"

class Texture_Manager : public Resource_Manager
{
private:
	std::map<std::string, sf::Texture> textures;
public:
	void load(const std::string& name, const std::string& filename);

	sf::Texture& getRef(const std::string& texture);

	Texture_Manager() {}
};
#endif // !TEXTURE_MANAGER_H

#include "Font_Manager.h"

void Font_Manager::load(const std::string & name, const std::string & filename)
{
	sf::Font font;
	font.loadFromFile(filename);
	this->fonts[name] = font;
}

sf::Font & Font_Manager::getRef(const std::string & font)
{
	return this->fonts.at(font);
}
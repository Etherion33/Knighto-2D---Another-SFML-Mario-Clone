#pragma once
#include "Resource_Manager.h"

class Font_Manager : public Resource_Manager
{
private:
	std::map<std::string, sf::Font> fonts;
public:
	void load(const std::string& name, const std::string& filename);
	sf::Font& getRef(const std::string& font);

	Font_Manager() {}
};

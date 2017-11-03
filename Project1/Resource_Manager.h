#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>

class Resource_Manager
{
protected:
	virtual void load(const std::string& name, const std::string& filename) = 0;
	~Resource_Manager() {}
};
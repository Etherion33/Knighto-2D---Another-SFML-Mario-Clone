#include "Sound_Manager.h"

void Sound_Manager::load(const std::string & name, const std::string & filename)
{
	sf::SoundBuffer sound;
	sound.loadFromFile(filename);
	this->sounds[name] = sound;
}

sf::SoundBuffer & Sound_Manager::getRef(const std::string & sound)
{
	return this->sounds.at(sound);
}
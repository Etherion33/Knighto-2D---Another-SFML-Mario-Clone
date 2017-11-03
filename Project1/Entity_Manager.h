#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include "Player.h"

using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map < EntityType, std::function<EntityBase*(void)>>;
using EnemyTypes = std::unordered_map<std::string, std::string>;

class Entity_Manager
{
public:
	Entity_Manager();
	~Entity_Manager();

	int add(const EntityType& enType, const std::string& Name = "");
	EntityBase* getById(unsigned int id);
	EntityBase* getByName(const std::string& name);
	void Remove(unsigned int id);

private:
	EntityContainer m_entities;
};


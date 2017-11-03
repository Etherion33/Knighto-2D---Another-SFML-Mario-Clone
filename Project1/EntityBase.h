#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"

enum class EntityType{Base , Enemy, Player};
enum class EntityState{Idle, Walking, Jumping, Attacking, Hurt, Dying};

struct TileInfo;

struct CollisionElement {
	CollisionElement(float f_area, TileInfo* tileInfo, const sf::FloatRect& fr_Bounds)
		:m_area(f_area),m_tile(tileInfo), m_tileBounds(fr_Bounds){}
		float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;

class Entity_Manager;
class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase();

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	EntityState getState() const;
	std::string getName() const;
	unsigned int getId() const;
	EntityType getType() const;

	sf::Vector2f getSpeed() { return m_Velocity; }

	void setPosition(float f_X, float f_Y);
	void setPosition(const sf::Vector2f& pos);
	void setSize(float f_X, float f_Y);
	void setState(const EntityState& en_State);
	void setAcceleration(float l_x, float l_y);

	void move(float f_X, float f_Y);
	void addVelocity(float f_X, float f_Y);
	void accelerate(float f_X, float f_Y);
	void applyFriction(float f_X, float f_Y);

	virtual void draw(sf::RenderWindow & window, float dt) = 0;
	virtual void update(const float dt) = 0;
protected:
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();

	//virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack) = 0;

	std::string m_Name;
	EntityType m_enType;
	unsigned int m_Id;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_Speed;
	sf::Vector2f m_Acceleration;
	sf::Vector2f m_friction;
	sf::Vector2f m_Pos;
	sf::Vector2f m_oldPos;
	TileInfo* m_referenceTile;
	sf::Vector2f m_Size;
	sf::FloatRect m_AABB; // collision box
	EntityState m_enState;

	sf::Sprite m_Sprite;
	AnimatedSprite m_AnimatedSprite;
	std::map<std::string, Animation> m_Animations;
	Animation currentAnimation;

	bool m_collidingOnX;
	bool m_collidingOnY;

	Collisions m_collisions;
	Entity_Manager* m_entityManager;
};

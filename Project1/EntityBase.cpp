#include "EntityBase.h"
#include "Entity_Manager.h"
#include "Level.h"

EntityBase::EntityBase()
	:m_Name("BaseEntity"),
	m_enType(EntityType::Base), m_Id(0), m_referenceTile(nullptr),
	m_enState(EntityState::Idle),
	m_collidingOnX(false),m_collidingOnY(false){}

EntityBase::~EntityBase() {}

void EntityBase::setPosition(float l_x, float l_y) {
	m_Pos = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::setPosition(const sf::Vector2f& l_pos) {
	m_Pos = l_pos;
	UpdateAABB();
}

void EntityBase::setSize(float l_x, float l_y) {
	m_Size = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::setAcceleration(float l_x, float l_y) {
	m_Acceleration = sf::Vector2f(l_x, l_y);
}

void EntityBase::setState(const EntityState& l_state) {
	if (m_enState == EntityState::Dying) { return; }
	m_enState = l_state;
}

const sf::Vector2f& EntityBase::getSize()const { return m_Size; }
std::string EntityBase::getName()const { return m_Name; }
EntityState EntityBase::getState()const { return m_enState; }
unsigned int EntityBase::getId()const { return m_Id; }
EntityType EntityBase::getType()const { return m_enType; }
const sf::Vector2f& EntityBase::getPosition()const { return m_Pos; }


void EntityBase::move(float l_x, float l_y) {
	m_oldPos = m_Pos;
	m_Pos += sf::Vector2f(l_x, l_y);
	sf::Vector2u mapSize;
	if (m_Pos.x < 0) {
		m_Pos.x = 0;
	}
	else if (m_Pos.x >(mapSize.x + 1) * 8) {
		m_Pos.x = (mapSize.x + 1) * 8;
	}

	if (m_Pos.y < 0) {
		m_Pos.y = 0;
	}
	else if (m_Pos.y >(mapSize.y + 1) * 8) {
		m_Pos.y = (mapSize.y + 1) * 8;
		setState(EntityState::Dying);
	}

	UpdateAABB();
}

void EntityBase::addVelocity(float l_x, float l_y) {
	m_Velocity += sf::Vector2f(l_x, l_y);
	if (abs(m_Velocity.x) > m_maxVelocity.x) {
		if (m_Velocity.x < 0) { m_Velocity.x = -m_maxVelocity.x; }
		else { m_Velocity.x = m_maxVelocity.x; }
	}

	if (abs(m_Velocity.y) > m_maxVelocity.y) {
		if (m_Velocity.y < 0) { m_Velocity.y = -m_maxVelocity.y; }
		else { m_Velocity.y = m_maxVelocity.y; }
	}
}

void EntityBase::accelerate(float l_x, float l_y) {
	m_Acceleration += sf::Vector2f(l_x, l_y);
}

void EntityBase::applyFriction(float l_x, float l_y) {
	if (m_Velocity.x != 0) {
		if (abs(m_Velocity.x) - abs(l_x) < 0) { m_Velocity.x = 0; }
		else {
			if (m_Velocity.x < 0) { m_Velocity.x += l_x; }
			else { m_Velocity.x -= l_x; }
		}
	}

	if (m_Velocity.y != 0) {
		if (abs(m_Velocity.y) - abs(l_y) < 0) { m_Velocity.y = 0; }
		else {
			if (m_Velocity.y < 0) { m_Velocity.y += l_y; }
			else { m_Velocity.y -= l_y; }
		}
	}
}


void EntityBase::UpdateAABB() {
	m_AABB = sf::FloatRect(m_Pos.x - (m_Size.x / 2), m_Pos.y - m_Size.y, m_Size.x, m_Size.y);
}


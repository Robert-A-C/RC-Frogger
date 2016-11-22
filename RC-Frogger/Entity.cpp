/**
@file    Entity.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the Entity class

*/
#include "Entity.h"

namespace GEX {
	Entity::Entity(int hitpoints) : 
		_hitpoints(hitpoints),
		_velocity(),
		_angularVelocity()
	{}

	void Entity::setVelocity(sf::Vector2f velocity)		// sets velocity
	{
		_velocity = velocity;
	}	

	void Entity::setVelocity(float vx, float vy)		// sets velocity with 2 floats
	{
		_velocity = sf::Vector2f(vx, vy);
	}

	float Entity::getAngularVelocity() const		// gets the rotate velocity
	{
		return _angularVelocity;
	}

	void Entity::setAngularVelocity(float av)		// sets the rotate velocity
	{
		_angularVelocity = av;
	}

	void Entity::accelerateAngularVelocity(float r)		// accelerates rotate velocity
	{
		rotate(getAngularVelocity() + r);
	}

	void Entity::accelerate(sf::Vector2f velocity)		// increases current velocity by passed it amount
	{
		setVelocity(velocity + getVelocity());
	}

	void Entity::accelerate(float vx, float vy)			// increases current velocity by passed in floats
	{
		setVelocity(sf::Vector2f(vx, vy) + getVelocity());
	}	

	sf::Vector2f Entity::getVelocity() const		// gets velocity
	{
		return _velocity;
	}

	int Entity::getHitpoints() const		// gets hitpoints
	{
		return _hitpoints;
	}

	void Entity::repair(int points)			// increments hitpoints by passed in amount
	{
		_hitpoints += points;
	}

	void Entity::damage(int points)			// decrements hitpoints by passed in amount
	{
		_hitpoints -= points;
	}

	void Entity::destroy()					// sets hitpoints to 0
	{
		_hitpoints = 0;
	}

	bool Entity::isDestroyed() const
	{
		return _hitpoints <= 0;
	}

	

	void Entity::updateCurrent(sf::Time dt, CommandQueue& command)		// updates entity
	{
		move(_velocity * dt.asSeconds());
		rotate(_angularVelocity * dt.asSeconds());
	}
}
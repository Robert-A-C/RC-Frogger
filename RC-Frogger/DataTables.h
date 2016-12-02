/**
@file    DataTables.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the DataTables class

*/
#pragma once
#include "ResourceIdentifiers.h"
#include "Airplane.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"
#include "Frog.h"
#include "Cars.h"
#include "Logs.h"
#include <map>

namespace GEX {
	
	struct FrogData
	{
		TextureID texture;
		sf::IntRect textureRect;
		
	};

	struct CarData
	{
		TextureID texture;
		sf::IntRect textureRect;
		sf::Vector2f laneStartPos;
		sf::Vector2f velocity;
	};

	struct LogData
	{
		TextureID texture;
		sf::IntRect textureRect;
		sf::Vector2f velocity;
	};

	struct Direction	// direction table
	{
		Direction(float a, float d);
		float	angle;
		float	distance;
	};

	struct AirplaneData			// table for projectile data
	{
		int			hitpoints;
		float		speed;
		TextureID	texture;
		sf::Time	fireInterval;
		std::vector<Direction> directions;
		sf::IntRect textureRect;
	};

	struct ProjectileData		// table for Projectile data
	{
		int damage;
		float speed;
		float approachRate;
		TextureID texture;
		sf::IntRect textureRect;
	};
	
	struct PickupData
	{
		TextureID texture;
		std::function<void(Airplane&)> action;
		sf::IntRect textureRect;
	};

	struct ParticleData
	{
		TextureID texture;
		sf::Color color;
		sf::Time lifetime;

	};
	std::map<Frog::Type, FrogData> initalizeFrogData();
	std::map<Cars::Type, CarData> initalizeCarData();
	std::map<Logs::Type, LogData> initalizeLogData();

	std::map<Airplane::Type, AirplaneData> initalizeAircraftData();			// initalize all the data required for the airplane table
	std::map<Projectile::Type, ProjectileData> initalizeProjectileData();	// initaliza all the data required for the projectile table
	std::map<Pickup::Type, PickupData> initalizePickupData();	// initaliza all the data required for the projectile table
	std::map<Particle::Type, ParticleData> initalizeParticleData();
}

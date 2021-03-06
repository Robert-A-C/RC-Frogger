/**
@file    DataTables.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the DataTables class

*/
#include "DataTables.h"
#include <functional>


namespace GEX {
	std::map<Airplane::Type, AirplaneData> GEX::initalizeAircraftData()		// initalizes data in the airplane table
	{
		 std::map<Airplane::Type, AirplaneData> data;

		 data[Airplane::Type::RAPTOR].hitpoints = 20;
		 data[Airplane::Type::RAPTOR].speed = 80.f;
		 data[Airplane::Type::RAPTOR].texture = TextureID::Atlas;
		 data[Airplane::Type::RAPTOR].fireInterval = sf::seconds(1);
		 data[Airplane::Type::RAPTOR].textureRect = sf::IntRect(144,0,84,64);

		 data[Airplane::Type::AVENGER].hitpoints = 40;
		 data[Airplane::Type::AVENGER].speed = 50.f;
		 data[Airplane::Type::AVENGER].texture = TextureID::Atlas;
		 data[Airplane::Type::AVENGER].fireInterval = sf::seconds(1);
		 data[Airplane::Type::AVENGER].textureRect = sf::IntRect(228,0,60,59);

		 data[Airplane::Type::EAGLE].hitpoints = 100;
		 data[Airplane::Type::EAGLE].speed = 200.f;
		 data[Airplane::Type::EAGLE].fireInterval = sf::seconds(1);
		 data[Airplane::Type::EAGLE].texture = TextureID::Atlas;
		 data[Airplane::Type::EAGLE].textureRect = sf::IntRect(0,0,48,64);

		 data[Airplane::Type::RAPTOR].directions.push_back(Direction(+30.f, 90.f));
		 data[Airplane::Type::RAPTOR].directions.push_back(Direction(+30.f, -90.f));
		 
		 

		 return data;
	}
	std::map<Projectile::Type, ProjectileData> GEX::initalizeProjectileData()	// initalizes projectile data in projectile table
	{
		std::map<Projectile::Type, ProjectileData> data;

		data[Projectile::Type::ALLIEDBULLET].damage = 10;
		data[Projectile::Type::ALLIEDBULLET].speed = 300;
		data[Projectile::Type::ALLIEDBULLET].texture = TextureID::Atlas;
		data[Projectile::Type::ALLIEDBULLET].textureRect = sf::IntRect(178,64,3,14);

		data[Projectile::Type::MISSILE].damage = 100;
		data[Projectile::Type::MISSILE].speed = 400.f;
		data[Projectile::Type::MISSILE].approachRate = 1500.f;
		data[Projectile::Type::MISSILE].texture = TextureID::Atlas;
		data[Projectile::Type::MISSILE].textureRect = sf::IntRect(160,64,15,32);

		data[Projectile::Type::ENEMYBULLET].damage = 10;
		data[Projectile::Type::ENEMYBULLET].speed = 300;
		data[Projectile::Type::ENEMYBULLET].texture = TextureID::Atlas;
		data[Projectile::Type::ENEMYBULLET].textureRect = sf::IntRect(178, 64, 3, 14);

		return data;
	}

	std::map<Pickup::Type, PickupData> GEX::initalizePickupData()	// initalizes pickup data in pickup table
	{
		std::map<Pickup::Type, PickupData> data;

		data[Pickup::Type::FireRate].texture = TextureID::Atlas;
		data[Pickup::Type::FireRate].action = [](Airplane& a) {a.increaseFireRate(); };
		data[Pickup::Type::FireRate].textureRect = sf::IntRect(120,64,40,40);

		data[Pickup::Type::FireSpread].texture = TextureID::Atlas;
		data[Pickup::Type::FireSpread].action = [](Airplane& a) { a.increaseSpread(); };
		data[Pickup::Type::FireSpread].textureRect = sf::IntRect(80,64,40,40);

		data[Pickup::Type::HealthRefill].texture = TextureID::Atlas;
		data[Pickup::Type::HealthRefill].action = [](Airplane& a) { a.repair(25); };
		data[Pickup::Type::HealthRefill].textureRect = sf::IntRect(0,64,40,40);

		data[Pickup::Type::MissileRefill].texture = TextureID::Atlas;
		data[Pickup::Type::MissileRefill].action = [](Airplane& a) { a.collectMissiles(3); };
		data[Pickup::Type::MissileRefill].textureRect = sf::IntRect(40,64,40,40);

		return data;
	}

	std::map<Particle::Type, ParticleData> GEX::initalizeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		
		data[Particle::Type::Propellant].color = sf::Color(255, 50, 0);
		data[Particle::Type::Propellant].lifetime = sf::seconds(0.3f);
		
		
		data[Particle::Type::Smoke].color = sf::Color(50, 50, 50);
		data[Particle::Type::Smoke].lifetime = sf::seconds(2.f);

		return data;

	}

	Direction::Direction(float a, float d) : angle(a), distance(d)
	{
		
	}
}
/**
@file	 Airplane.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the airplane class

*/
#include "Airplane.h"
#include "Category.h"
#include "TextNode.h"
#include "TextureHolder.h"
#include <memory>
#include <cassert>
#include "Utility.h"
#include "DataTables.h"
#include <iostream>
#include "SoundNode.h"

namespace GEX {


	const std::map<Airplane::Type, AirplaneData> table = initalizeAircraftData();

	Airplane::Airplane(Type type) :
		Entity(table.at(type).hitpoints),
		_type(type),
		_player(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_explosion(TextureHolder::getInstance().get(TextureID::Explosion)),
		_travelDistance(0),
		_missile_ammo(1000),
		_fireRateLevel(1),
		_spreadLevel(1)	,
		_showExplosion(true),
		_playedExplosionSound(false),
		_spawnedPickup(false)

	{
		
		centerOrigin(_player);

		_explosion.setFrameSize(sf::Vector2i(256, 256));
		_explosion.setNumFrames(16);
		_explosion.setDuration(sf::seconds(1));
		centerOrigin(_explosion);
		 
		// build fire and launch commands
		_fireCommand.category = Category::SceneAirLayer;
		_fireCommand.action = [this](SceneNode& node, sf::Time dt)
		{
			this->createBullet(node);
		};
		
		_launchMissileCommand.category = Category::SceneAirLayer;
		_launchMissileCommand.action = [this](SceneNode& node, sf::Time dt)
		{
			this->createProjectile(node, Projectile::Type::MISSILE, 0.f, 0.f);
		};

		_dropPickupCommand.category = Category::SceneAirLayer;
		_dropPickupCommand.action = [this](SceneNode& node, sf::Time)
		{
			createPickup(node);
		};


		std::unique_ptr<TextNode> healthDisplay(new TextNode(std::to_string(getHitpoints()) + " HP"));
		_healthDisplay = healthDisplay.get();
		healthDisplay->setPosition(0.f, 50.f);
		attachChild(std::move(healthDisplay));


	}	

	unsigned int Airplane::getCategory() const	// Gets the category based on the type
	{
		switch (_type)
		{
		case Type::EAGLE:
			return Category::PlayerAircraft;

		case Type::RAPTOR:
			return Category::EnemyAircraft;

		case Type::AVENGER:
			return Category::EnemyAircraft;
			

		default:
			assert(0); // missing type in switch
		}
	}

	void Airplane::updateCurrent(sf::Time dt, CommandQueue& command)		// updates health display and movement
	{
		sf::Vector2f velocity = getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			setVelocity(velocity / std::sqrt(2.f));

		_healthDisplay->setText(std::to_string(getHitpoints()) + " HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());

		updateTexts();
		checkProjectileLaunch(dt, command);

		if (isDestroyed())
		{
			_isFiring = false;
			_explosion.update(dt);

			if (!_spawnedPickup)
			{
				checkPickupDrop(command);

				_spawnedPickup = true;
			}

			if (!_playedExplosionSound)
			{
				SoundEffectID soundEffect = (randomInt(2) == 0) ? SoundEffectID::Explosion1 : SoundEffectID::Explosion2;
				playLocalSound(command, soundEffect);

				_playedExplosionSound = true;
			}
			return;

			
		}

		movementUpdate(dt);
		Entity::updateCurrent(dt, command);
	}

	void Airplane::updateTexts()		// updates the Health display texts
	{
		_healthDisplay->setText(std::to_string(getHitpoints()) + " HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());
	}

	void Airplane::movementUpdate(sf::Time dt)				// updates movement based on directions otherwise autopilots
	{
		const std::vector<Direction>& directions = table.at(_type).directions;

		if (!directions.empty()) //only auto pilot plane if I have directions
		{
			float distanceToTravel = directions.at(_directionIndex).distance;
			if (_travelDistance > distanceToTravel)
			{
				_directionIndex = (_directionIndex + 1) % directions.size();
				_travelDistance = 0;
			}
			_travelDistance += getMaxSpeed() * dt.asSeconds();

			float dirAngle = directions.at(_directionIndex).angle;
			float vx = getMaxSpeed() * GEX::cos(dirAngle);
			float vy = getMaxSpeed() * GEX::sin(dirAngle);
			setVelocity(vx, vy);
		}
	}

	bool Airplane::isAllied() const	// checks if Airplane object is of type Eagle
	{
		return _type == Type::EAGLE;		
	}

	float Airplane::getMaxSpeed() const // returns speed from table
	{
		return table.at(_type).speed;
	}

	sf::FloatRect Airplane::getBoundingRect() const	// get the rectangle of the sprites shape
	{
		return getWorldTransform().transformRect(_player.getGlobalBounds());
	}

	void Airplane::fire()		// shoots bullet
	{
		//std::cout << "Fire" << std::endl;
		//only shios with none zero fire rate fire bullets
		if (table.at(_type).fireInterval != sf::Time::Zero)
			_isFiring = true;
	}

	void Airplane::launchMissile()	// launches missile
	{
		//std::cout << "Missile" << std::endl;
		// only ships with missles can fire
		if (_missile_ammo > 0)
		{
			--_missile_ammo;
			_isLaunchingMissile = true;
		}
	}

	void Airplane::checkProjectileLaunch(sf::Time dt, CommandQueue & command)	// sends fire command and then sets _isFiring/_isLaunchingMissile to false 
	{
		// enemies always fire
		if (!isAllied())
			fire();
		
		// automatic gun fire
		if (_isFiring && _fireCountdown <= sf::Time::Zero)
		{

			command.push(_fireCommand);

			playLocalSound(command, isAllied() ? SoundEffectID::AlliedGunfire : SoundEffectID::EnemyGunfire);
			//playLocalSound(command, SoundEffectID::AlliedGunfire);

			_isFiring = false;
			_fireCountdown += table.at(_type).fireInterval / (_fireRateLevel + 1.f);
		}
		else if (_fireCountdown > sf::Time::Zero)
		{
			_fireCountdown -= dt;
			_isFiring = false;
		}

		if (_isLaunchingMissile)
		{
			command.push(_launchMissileCommand);
			playLocalSound(command, SoundEffectID::LaunchMissile);
			_isLaunchingMissile = false;
		}

	}

	void Airplane::increaseFireRate()
	{
		if (_fireRateLevel < 10)
			++_fireRateLevel;
	}

	void Airplane::increaseSpread()
	{
		if (_spreadLevel < 3)
			++_spreadLevel;
	}

	void Airplane::collectMissiles(unsigned int ammo)
	{
		_missile_ammo += ammo;
	}

	bool Airplane::isMarkedForRemoval() const
	{
		return isDestroyed() && (_explosion.isFinished() || !_showExplosion);
	}

	void Airplane::playLocalSound(CommandQueue & commands, SoundEffectID effectID)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffect;
		command.action = derivedAction<SoundNode>([effectID, worldPosition](SoundNode& node, sf::Time)
		{
			node.playSound(effectID, worldPosition);
		});
		commands.push(command);
	}

	void Airplane::createBullet(SceneNode& node) const		// creates a bullet
	{	
		Projectile::Type type = isAllied() ? Projectile::Type::ALLIEDBULLET : Projectile::Type::ENEMYBULLET;
		
		switch (_spreadLevel)
		{
		case 1:
			createProjectile(node, type, 0, 0.5f);
			break;
		case 2:
			createProjectile(node, type, -0.3f, 0.33f);
			createProjectile(node, type, +0.3f, 0.33f);
			break;
		case 3:
			createProjectile(node, type, -0.3f, 0.15f);
			createProjectile(node, type, 0.0f, 0.33f);
			createProjectile(node, type, +0.3f, 0.15f);
			break;
		}
		

	}

	void Airplane::createProjectile(SceneNode& node, Projectile::Type type, float xOffSet, float yOffSet) const		// creates a projectile 
	{
		// node is the SceneAirLayer node that the command was targeted to
		std::unique_ptr<Projectile> projectile(new Projectile(type));

		sf::Vector2f offSet(xOffSet * _player.getGlobalBounds().width, yOffSet * _player.getGlobalBounds().height / 2.f);
		sf::Vector2f velocity(0, projectile->getMaxSpeed());

		float sign = isAllied() ? -1.f : 1.f;
		projectile->setPosition(getWorldPosition() + offSet * sign);
		projectile->setVelocity(velocity * sign);
		node.attachChild(std::move(projectile));
	}

	void Airplane::checkPickupDrop(CommandQueue & command)
	{
		if (!isAllied() && _spawnedPickup == false)
		{		
			int chance = randomInt(2);
			if (chance == 0)
				command.push(_dropPickupCommand);
		}
	}

	void Airplane::createPickup(SceneNode & node) const
	{
		int pickup = randomInt(4);
		

		if (pickup == 0) {
			Pickup::Type type = Pickup::Type::HealthRefill;
			std::unique_ptr<Pickup> pickup(new Pickup(type));
			pickup->setPosition(getWorldPosition());
			node.attachChild(std::move(pickup));
		}
		if (pickup == 1) {
			Pickup::Type type = Pickup::Type::MissileRefill;
			std::unique_ptr<Pickup> pickup(new Pickup(type));
			pickup->setPosition(getWorldPosition());
			node.attachChild(std::move(pickup));
		}
		if (pickup == 2) {
			Pickup::Type type = Pickup::Type::FireSpread;
			std::unique_ptr<Pickup> pickup(new Pickup(type));
			pickup->setPosition(getWorldPosition());
			node.attachChild(std::move(pickup));
		}
		if (pickup == 3) {
			Pickup::Type type = Pickup::Type::FireRate;
			std::unique_ptr<Pickup> pickup(new Pickup(type));
			pickup->setPosition(getWorldPosition());
			node.attachChild(std::move(pickup));
		}
	}

	void Airplane::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const		// draws the sprite _player
	{
		if (isDestroyed() && _showExplosion)
			target.draw(_explosion, state);
		else
			target.draw(_player, state);
	}

}
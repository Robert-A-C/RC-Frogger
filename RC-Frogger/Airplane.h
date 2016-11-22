/**
@file	 Airplane.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the Airplane class

*/
#pragma once
#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Projectile.h"
#include "Animation.h"

namespace GEX {

	
	class TextNode;
	class Airplane : public Entity
	{
	public:
		enum class Type { EAGLE, RAPTOR, AVENGER };

	public:
		Airplane(Type type = Type::EAGLE);						
		
		virtual ~Airplane() {};

		unsigned int getCategory() const override;				// Gets the category based on the type

		float getMaxSpeed() const;								// returns speed from table
		sf::FloatRect  getBoundingRect() const override;		// get the rectangle of the sprites shape

		bool isAllied() const;													// checks if Airplane object is of type Eagle
		void fire();															// shoots bullets
		void launchMissile();													// launches missile
		void checkProjectileLaunch(sf::Time dt, CommandQueue& command);			// sends fire command and then sets _isFiring/_isLaunchingMissile to false
		
		void increaseFireRate();
		void increaseSpread();
		void collectMissiles(unsigned int ammo);


		bool isMarkedForRemoval() const override;

		void playLocalSound(CommandQueue& commands, SoundEffectID effect);

	private:
		void updateCurrent(sf::Time dt, CommandQueue& command) override;			// updates health display and movement
		void movementUpdate(sf::Time dt);											// updates movement based on directions otherwise autopilots
		void drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;	// draws the sprite _player

		void updateTexts();															// updates the Health display texts
	
		void createBullet(SceneNode& node) const;															// creates a bullet
		void createProjectile(SceneNode& node, Projectile::Type type, float xOffSet, float yOffSet) const;	// creates a projectile

		void checkPickupDrop(CommandQueue& command);
		void createPickup(SceneNode& node) const;

	private:
		
		Type			_type;
		sf::Sprite		_player;
		TextNode*		_healthDisplay;
		int				_directionIndex;
		float			_travelDistance;

		Animation		_explosion;
		bool			_showExplosion;

		Command			_fireCommand;
		Command			_launchMissileCommand;
		bool			_isMarkedForRemoval;

		bool			_isFiring;
		bool			_isLaunchingMissile;
		bool			_playedExplosionSound;

		Command			_dropPickupCommand;
		bool			_spawnedPickup;

		sf::Time		_fireCountdown;

		float			_fireRateLevel;
		std::size_t		_missile_ammo;
		std::size_t		_spreadLevel;
	};
}
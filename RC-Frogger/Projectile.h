/**
@file    Projectile.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the Projectile class

*/
#pragma once
#include "Entity.h"
#include "TextureHolder.h"

namespace GEX {
	class Projectile : public Entity
	{

	public:
		enum class Type
		{
			ALLIEDBULLET,
			ENEMYBULLET,
			MISSILE

		};

		Projectile(Type type);
		
		unsigned int	getCategory() const override;		// getscategory
		float			getMaxSpeed() const;				// gets speed
		bool			isGuided() const;
		void			guideTowards(sf::Vector2f position);
		sf::FloatRect  getBoundingRect() const override;		// get the rectangle of the sprites shape

	private:
		void updateCurrent(sf::Time dt, CommandQueue& command) override;			// updates entity
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;  // draws the sprite


	private:
		Type _type;
		sf::Sprite _sprite;
		sf::Vector2f _targetDirection;	///<unit vector pointing at closes enemy plane
	};
}

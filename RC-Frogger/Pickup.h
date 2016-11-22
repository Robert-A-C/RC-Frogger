/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#pragma once



#include "Entity.h"
#include "Command.h"
#include "TextureHolder.h"

#include <SFML/Graphics/Sprite.hpp>


namespace GEX
{
	class Airplane;

	class Pickup : public Entity
	{
	public:
		/**
		Use old style enums to easily convert to and from 
		int to use with random 
		*/
		enum Type
		{
			HealthRefill,
			MissileRefill,
			FireSpread,
			FireRate,
			TypeCount
		};

	public:
									Pickup(Type type);

		virtual unsigned int		getCategory() const;
		sf::FloatRect				getBoundingRect() const override;

		void 						apply(Airplane& player) const;

	protected:
		virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		Type 						_type;
		sf::Sprite					_sprite;
	};

}
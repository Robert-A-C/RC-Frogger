/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "Pickup.h"
#include "DataTables.h"
#include "Category.h"
#include "CommandQueue.h"
#include "Utility.h"
#include "TextureHolder.h"
#include <map>

#include <SFML/Graphics/RenderTarget.hpp>


namespace GEX
{
	namespace
	{
		const std::map <Pickup::Type, PickupData > Table = initalizePickupData();
	}

	Pickup::Pickup(Type type) :
		Entity(1),  // hitpoints = 1
		_type(type),
		_sprite(TextureHolder::getInstance().get(Table.at(type).texture), Table.at(type).textureRect)
	{
		centerOrigin(_sprite);
	}

	unsigned int Pickup::getCategory() const
	{
		return Category::Pickup;
	}

	sf::FloatRect Pickup::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Pickup::apply(Airplane& player) const   // will be called from handle collision in World::update
	{
		Table.at(_type).action(player);
	}

	void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

}
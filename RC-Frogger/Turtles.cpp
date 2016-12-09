#include "Turtles.h"
#include "TextureHolder.h"
#include "DataTables.h"
#include "Utility.h"

namespace GEX {

	const std::map<Turtles::Type, TurtleData> table = initalizeTurtleData();

	Turtles::Turtles(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		centerOrigin(_sprite);

	}

	unsigned int Turtles::getCategory() const
	{
		switch (_type)
		{
		case Type::Turtles2:
		case Type::Turtles3:
			return Category::Turtle;

		default:
			assert(0);

		}
	}

	sf::FloatRect Turtles::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	

	

	void Turtles::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Turtles::updateCurrent(sf::Time dt, CommandQueue & command)
	{
		setVelocity(table.at(_type).velocity);

		switch (_type)
		{
		case Type::Turtles2:
			if (getPosition().x < -120.f)
				setPosition(580.f, getPosition().y);
			break;
		case Type::Turtles3:
			if (getPosition().x < -120.f)
				setPosition(580.f, getPosition().y);
			break;
		

		default:
			break;
		}

		Entity::updateCurrent(dt, command);
	}



}
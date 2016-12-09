#include "Logs.h"
#include "TextureHolder.h"
#include "DataTables.h"
#include "Utility.h"

namespace GEX {

	const std::map<Logs::Type, LogData> table = initalizeLogData();

	Logs::Logs(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		centerOrigin(_sprite);
		setVelocity(table.at(_type).velocity);

	}

	unsigned int Logs::getCategory() const
	{
		switch (_type)
		{
		case Type::Log2:
		case Type::Log3:		
			return Category::Log;

		default:
			assert(0);

		}
	}

	sf::FloatRect Logs::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Logs::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Logs::updateCurrent(sf::Time dt, CommandQueue & command)
	{
		

		switch (_type)
		{
		case Type::Log2:
			if (getPosition().x > 640.f)
				setPosition(-120.f, getPosition().y);
			break;
		case Type::Log3:
			if (getPosition().x > 640.f)
				setPosition(-120.f, getPosition().y);
			break;


		default:
			break;
		}

		Entity::updateCurrent(dt, command);
	}



}
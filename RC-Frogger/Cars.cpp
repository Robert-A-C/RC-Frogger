#include "Cars.h"
#include "TextureHolder.h"
#include "DataTables.h"
#include "Utility.h"

namespace GEX {

	const std::map<Cars::Type, CarData> table = initalizeCarData();

	Cars::Cars(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		centerOrigin(_sprite);
		
	}

	unsigned int Cars::getCategory() const
	{
		switch (_type)
		{
		case Type::RaceCar1:
		case Type::Trackter2:
		case Type::SUV3:
		case Type::RaceCar4:
		case Type::Truck5:
			return Category::Car;

		default:
			assert(0);

		}
	}

	sf::FloatRect Cars::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Cars::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	

	void Cars::updateCurrent(sf::Time dt, CommandQueue & command)
	{
		setVelocity(table.at(_type).velocity);

		switch (_type)
		{
		case Type::RaceCar1:
			if (getPosition().x < -60.f)
				setPosition(580.f, getPosition().y);
			break;
		case Type::Trackter2:
			if (getPosition().x > 540.f)
				setPosition(-100.f, getPosition().y);
			break;
		case Type::SUV3:
			if (getPosition().x < -60.f)
				setPosition(580.f, getPosition().y);
			break;
		case Type::RaceCar4:
			if (getPosition().x > 540.f)
				setPosition(-100.f, getPosition().y);
			break;
		case Type::Truck5:
			if (getPosition().x < -60.f)
				setPosition(580.f, getPosition().y);
			break;

		default:
			break;
		}

		Entity::updateCurrent(dt, command);
	}


	
}
#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "Command.h"

namespace GEX {
	class Cars : public Entity
	{
	public:
		enum class Type { RaceCar1, Trackter2, SUV3, RaceCar4, Truck5 };

	public:
		Cars(Type type);

		virtual ~Cars() {};
		
		unsigned int getCategory() const override;
		sf::FloatRect getBoundingRect() const override;

		

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
		void updateCurrent(sf::Time dt, CommandQueue& command) override;

	private:
		Type _type;
		sf::Sprite _sprite;


	};
}

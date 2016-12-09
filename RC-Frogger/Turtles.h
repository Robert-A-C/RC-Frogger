#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "Command.h"

namespace GEX {
	class Turtles : public Entity
	{
	public:
		enum class Type { Turtles2, Turtles3 };

	public:
		Turtles(Type type);

		virtual ~Turtles() {};

		unsigned int getCategory() const override;
		sf::FloatRect getBoundingRect() const override;

		
		

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
		void updateCurrent(sf::Time dt, CommandQueue& command) override;

	private:
		Type _type;
		sf::Sprite _sprite;
		sf::Vector2f _lane;


	};
}

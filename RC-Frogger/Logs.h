#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "Command.h"

namespace GEX {
	class Logs : public Entity
	{
	public:
		enum class Type { Log2, Log3 };

	public:
		Logs(Type type);

		virtual ~Logs() {};

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

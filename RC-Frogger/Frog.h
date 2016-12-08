#pragma once
#include "Entity.h"
#include "Command.h"
#include "CommandQueue.h"
#include "ResourceIdentifiers.h"

namespace GEX {
	class Frog : public Entity
	{
	public:
		enum class Type { Frogger };

	public:
		Frog(Type type = Type::Frogger);
		
		virtual ~Frog() {};

		unsigned int getCategory() const override;
		sf::FloatRect getBoundingRect() const override;

		void playLocalSound(CommandQueue& commands, SoundEffectID effect);
		void die();

	private:
		void updateCurrent(sf::Time dt, CommandQueue& command) override;
		void movementUpdate(sf::Time dt);
		void drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		

	private:
		Type _type;
		sf::Sprite _sprite;
		int _lives;
		mutable sf::Sprite _life;



	};
}

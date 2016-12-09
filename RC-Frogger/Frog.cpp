#include "Frog.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "SoundNode.h"
#include "DataTables.h"

namespace GEX {

	const std::map<Frog::Type, FrogData> table = initalizeFrogData();

	Frog::Frog(Type type) :
		_lives(3),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect),
		_life(TextureHolder::getInstance().get(TextureID::FroggerAtlas), sf::IntRect(397, 99, 34, 41))		
	{
		centerOrigin(_sprite);

	}

	unsigned int Frog::getCategory() const
	{
		
			return Category::Player;		
		
	}

	sf::FloatRect Frog::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Frog::playLocalSound(CommandQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffect;
		command.action = derivedAction<SoundNode>([effect, worldPosition](SoundNode& node, sf::Time)
		{
			node.playSound(effect, worldPosition);
		});
		commands.push(command);
	}

	

	void Frog::updateCurrent(sf::Time dt, CommandQueue & command)
	{
		Entity::updateCurrent(dt, command);
		
	}

	void Frog::movementUpdate(sf::Time dt)
	{
		
	}

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
		
		_life.setPosition(440.f, 5.f);
		
		for (int i = 0; i < _lives; ++i)
		{			
			target.draw(_life);		
			_life.setPosition(_life.getPosition().x - 40.f, _life.getPosition().y);	
		}
	}

	void Frog::die()
	{
		_lives -= 1;		
	}



}
/**
@file    GameState.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the GameState class

*/

#pragma once


#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "World.h"
#include "PlayerControl.h"
#include "State.h"
#include "CommandQueue.h"

namespace GEX
{


	class GameState : public State
	{
	public:
		GameState(StateStack& stack, Context context);

		virtual void        draw();									// draws the world
		virtual bool        update(sf::Time dt);					// updates game
		virtual bool        handleEvent(const sf::Event& event);	// handles input


	private:
		World               _world;
		PlayerControl&      _player;

	};
}


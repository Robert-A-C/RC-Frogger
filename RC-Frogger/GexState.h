/**
@file    GexState.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the GexState class

*/
#pragma once


#include "State.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


namespace GEX
{

	class GexState : public State
	{
	public:
		GexState(StateStack& stack, Context context);

		virtual void        draw();									// draws the world
		virtual bool        update(sf::Time dt);					// returns false so the game doesn't update
		virtual bool        handleEvent(const sf::Event& event);	// handles input


	private:
		sf::Sprite          _backgroundSprite;	
		sf::Text            _pausedText;
		sf::Text            _instructionText;

	};


}
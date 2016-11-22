/**
@file    PauseState.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the PauseState class

*/
#pragma once


#include "State.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


namespace GEX
{

	class GameOverState : public State
	{
	public:
		GameOverState(StateStack& stack, Context context);

		virtual void        draw();									// draws the window
		virtual bool        update(sf::Time dt);					// returns false so game doesn't update
		virtual bool        handleEvent(const sf::Event& event);	// handles input


	private:
		sf::Time			_elaspedTime;
		sf::Text            _gameOverText;

	};


}
/**
@file    TitleState.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the TitleState class

*/
#pragma once

#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "CommandQueue.h"

namespace GEX
{

	class TitleState : public State
	{
	public:
		TitleState(StateStack& stack, Context context);

		virtual void        draw();									// draws the window
		virtual bool        update(sf::Time dt);					// updates title state
		virtual bool        handleEvent(const sf::Event& event);	// handles events


	private:
		sf::Sprite          _backgroundSprite;
		sf::Text            _text;

		bool                _showText;
		sf::Time            _textEffectTime;
	};
}
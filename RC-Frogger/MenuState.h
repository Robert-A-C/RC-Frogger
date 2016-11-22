/**
@file    MenuState.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the MenuState class

*/
#pragma once

#include "State.h"
#include "CommandQueue.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace GEX
{

	class MenuState : public State
	{
	public:
		MenuState(StateStack& stack, Context context);

		virtual void            draw();									// draws the window
		virtual bool            update(sf::Time dt);					// updates game
		virtual bool            handleEvent(const sf::Event& event);	// handles input

		void                    updateOptionText();						// changes the selected text color


	private:
		enum OptionNames
		{
			Play,
			Exit,
		};


	private:
		sf::Sprite              _backgroundSprite;

		std::vector<sf::Text>   _options;
		std::size_t             _optionIndex;
	};

}

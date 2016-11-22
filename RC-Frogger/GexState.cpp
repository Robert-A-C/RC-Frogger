/**
@file    GexState.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the GexState class

*/
#include "GexState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{


	GexState::GexState(StateStack& stack, Context context) :
		State(stack, context),

		_pausedText(),
		_instructionText()
	{
		_backgroundSprite.setTexture(TextureHolder::getInstance().get(TextureID::GexScreen));		// sets picture to sprite 
		_backgroundSprite.setColor(sf::Color(250, 250, 250, 100));									// sets color
		centerOrigin(_backgroundSprite);															// centers picture								

		sf::Font& font = FontHolder::getInstance().get(FontID::Main);	// gets font
		sf::Vector2f viewSize = context.window->getView().getSize();	// 
		_backgroundSprite.setPosition(viewSize.x / 2, viewSize.y / 2);	// sets position

		_pausedText.setFont(font);											// Sets the Pause text font, string, position, size and centers the text
		_pausedText.setString("Gex State!");								//
		_pausedText.setCharacterSize(70);									//
		centerOrigin(_pausedText);											//
		_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);		// 


		_instructionText.setFont(font);																				// Sets the instruction texts font, string position 
		_instructionText.setString("(Press Backspace to return to the main menu)\n(Press G to return to game)");	// and centers it
		centerOrigin(_instructionText);																				//
		_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);											//
	}

	void GexState::draw()									// draws the world
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(250, 0, 0, 100));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(backgroundShape);
		window.draw(_backgroundSprite);
		window.draw(_pausedText);
		window.draw(_instructionText);

	}

	bool GexState::update(sf::Time)		// Doesn't update so it pauses the game
	{
		return false;
	}

	bool GexState::handleEvent(const sf::Event& event) // handles input
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::G)
		{
			// Escape pressed, remove itself to return to the game
			requestStackPop();
		}

		if (event.key.code == sf::Keyboard::BackSpace)
		{
			// Escape pressed, remove itself to return to the game
			requestStateClear();
			requestStackPush(StateID::Menu);
		}

		return false;
	}
}
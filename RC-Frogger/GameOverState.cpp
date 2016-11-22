/**
@file    PauseState.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the PauseState class

*/
#include "GameOverState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "PlayerControl.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX
{


	GameOverState::GameOverState(StateStack& stack, Context context) :
		State(stack, context),
		_gameOverText(),
		_elaspedTime()
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f windowSize = context.window->getView().getSize();

		_gameOverText.setFont(font);
		if (context.player->getMissionStatus() == missionStatus::Failure)
		{
			_gameOverText.setString("Mission Failed!");	
			_gameOverText.setCharacterSize(100);									// sets Game over text
			centerOrigin(_gameOverText);											//
			_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);	//
		}
		else
		{
			_gameOverText.setString("Mission Succesful!");
			_gameOverText.setCharacterSize(100);
			centerOrigin(_gameOverText);
			_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
		}
	}

	void GameOverState::draw()				// draws the window
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(backgroundShape);
		window.draw(_gameOverText);
		
	}

	bool GameOverState::update(sf::Time dt)	// returns false so game doesn't update
	{
		_elaspedTime += dt;
		if (_elaspedTime > sf::seconds(3))
		{
			requestStateClear();
			requestStackPush(StateID::Menu);
		}
		return false;
	}

	bool GameOverState::handleEvent(const sf::Event& event)	// handles input
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::Escape)
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
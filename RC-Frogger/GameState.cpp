/**
@file    GameState.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the GameState class

*/
#include "GameState.h"
#include "Utility.h"
#include "MusicPlayer.h"


namespace GEX
{



	GameState::GameState(StateStack& stack, Context context) :
		State(stack, context),
		_world(*context.window, *context.soundEffect),		
		_player(*context.player)
	{
		//context.music->play(MusicID::MissionTheme);
	}

	void GameState::draw()		// draws the world
	{
		_world.draw();
	}

	bool GameState::update(sf::Time dt)		// updates the game
	{
		_world.update(dt);

		if (!_world.hasAlivePlayer())
		{
			_player.setMissionStatus(missionStatus::Failure);
			requestStackPush(StateID::GameOver);

		}
		else if(_world.hasReachedFinish())
		{
			_player.setMissionStatus(missionStatus::Success);
			requestStackPush(StateID::GameOver);
		}

		CommandQueue& commands = _world.getCommandQueue();
		_player.handleRealTimeInput(commands);

		return true;
	}

	bool GameState::handleEvent(const sf::Event& event)	// handles input
	{
		// Game input handling
		CommandQueue& commands = _world.getCommandQueue();
		_player.handleEvent(event, commands);

		// Escape pressed, trigger the pause screen
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			requestStackPush(StateID::Pause);

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			requestStackPush(StateID::Gex);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		{
			requestStackPop();
			requestStackPush(StateID::Menu);
		}
			return true;
	}

}
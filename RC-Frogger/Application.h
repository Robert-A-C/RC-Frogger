/**
@file    Application.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the application class

*/
#pragma once
#include "PlayerControl.h"
#include "StateStack.h"
#include "CommandQueue.h"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

namespace GEX {
	class Application
	{
	public:
		Application();
		void	run();		// runs the game loop

	private:
		void	processInput();						// processes event input
		void	update(sf::Time dt);				// updates the stateStack
		void	render();							// clears and redraws everthing
		void	updateStatistics(sf::Time dt);		// updates the fps and time per update
		void	registerStates();					// creates the games states

	private:
		static const sf::Time	TimePerFrame;
		sf::RenderWindow		_window;
		PlayerControl			_player;
		MusicPlayer				_music;
		SoundPlayer				_soundPlayer;
		

		StateStack				_stateStack;
		sf::Text				_statsText;
	};
}

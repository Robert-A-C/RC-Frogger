/**
@file    State.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the State class

*/
#pragma once

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include <memory>
#include "StateIdentifiers.h"

namespace sf
{
	class RenderWindow;
}

namespace GEX {
	class StateStack;
	class MusicPlayer;
	class PlayerControl;
	class SoundPlayer;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
			Context(sf::RenderWindow& window, PlayerControl& player, MusicPlayer& music, SoundPlayer& soundEffect);

			sf::RenderWindow* window;
			PlayerControl* player;
			MusicPlayer* music;
			SoundPlayer* soundEffect;
		};

	public:
		State(StateStack& stack, Context context);
		virtual ~State();
		
		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;	
	protected:
		void requestStackPush(StateID stateID);		// request stack push
		void requestStackPop();						// request stack pop
		void requestStateClear();					// request state clear

		Context getContext() const;					// returns context
	private:
		StateStack* _stack;
		Context     _context;
	};
}

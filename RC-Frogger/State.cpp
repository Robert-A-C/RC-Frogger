/**
@file    State.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the State class

*/
#include "State.h"
#include "StateStack.h"

namespace GEX 
{
	State::Context::Context(sf::RenderWindow& window, PlayerControl& player, MusicPlayer& music, SoundPlayer& soundEffect) :
		window(&window),
		player(&player),
		music(&music),
		soundEffect(&soundEffect)
	{}

	State::State(StateStack& stack, Context context) :
		_stack(&stack),
		_context(context)
	{}

	State::~State()
	{}

	void State::requestStackPush(StateID stateID)	// request push state
	{
		_stack->pushState(stateID);
	}

	void State::requestStackPop()	// request pop state
	{
		_stack->popState();
	}

	void State::requestStateClear()		// request clear state
	{
		_stack->clearStates();
	}

	State::Context State::getContext() const	// returns context
	{
		return _context;
	}
}
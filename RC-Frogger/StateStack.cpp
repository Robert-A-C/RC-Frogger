/**
@file    PlayerControl.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the PlayerControl class

*/
#include "StateStack.h"
#include <cassert>

namespace GEX
{

	StateStack::StateStack(State::Context context) :
		_stack(),
		_pendingList(),
		_context(context),
		_factories()
	{}

	void StateStack::update(sf::Time dt)		// updates
	{
		// Iterate from top to bottom, stop as soon as update() returns false
		for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr)
		{
			if (!(*itr)->update(dt))
				break;
		}

		applyPendingChanges();
	}

	void StateStack::draw()			// draws the states
	{
		// Draw all active states from bottom to top
		for (State::Ptr& state : _stack)
			state->draw();
	}

	void StateStack::handleEvent(const sf::Event& event)		// handles events
	{
		// Iterate from top to bottom, stop as soon as handleEvent() returns false
		for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr)
		{
			if (!(*itr)->handleEvent(event))
				              break;
		}

		applyPendingChanges();
	}

	void StateStack::pushState(StateID stateID)		// push state
	{
		_pendingList.push_back(PendingChange(Push, stateID));
	}

	void StateStack::popState()				// pops state
	{
		_pendingList.push_back(PendingChange(Pop));
	}

	void StateStack::clearStates()			// clears states
	{
		_pendingList.push_back(PendingChange(Clear));
	}

	bool StateStack::isEmpty() const	// checks if stack is empty
	{
		return _stack.empty();
	}

	State::Ptr StateStack::createState(StateID stateID)		// creates stack
	{
		auto found = _factories.find(stateID);
		assert(found != _factories.end());

		return found->second();
	}

	void StateStack::applyPendingChanges()		// applies changes
	{
		for (PendingChange change : _pendingList)
		{
			switch (change.action)
			{
			case Push:
				_stack.push_back(createState(change.stateID));
				break;

			case Pop:
				_stack.pop_back();
				break;

			case Clear:
				_stack.clear();
				break;
			}
		}
		_pendingList.clear();
	}

	StateStack::PendingChange::PendingChange(Action action, StateID stateID) :
		action(action),
		stateID(stateID)
	{}

}
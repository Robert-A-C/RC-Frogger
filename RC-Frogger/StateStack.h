/**
@file    StateStack.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the StateStack class

*/
#pragma once

#include "SFML/System.hpp"

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace GEX
{



	class StateStack
	{

	public:
		enum Action
		{
			Push,
			Pop,
			Clear,
		};


	public:
		explicit            StateStack(State::Context context);
		StateStack(const StateStack&) = delete;
		StateStack&         operator =(const StateStack&) = delete;

		template < typename T>
		void                registerState(StateID stateID);			// registers the states

		void                update(sf::Time dt);					// updates the stack
		void                draw();									// draws the states
		void                handleEvent(const sf::Event& event);	// handles events

		void                pushState(StateID stateID);		// pushes state
		void                popState();						// pops state	
		void                clearStates();					// clears states

		bool                isEmpty() const;	// returns if it's empty


	private:
		State::Ptr          createState(StateID stateID);	// creates states
		void                applyPendingChanges();			// applies changes


	private:
		struct PendingChange
		{
			explicit            PendingChange(Action action, StateID stateID = StateID::None);

			Action              action;
			StateID             stateID;
		};


	private:
		std::vector<State::Ptr>								_stack;
		std::vector<PendingChange>                          _pendingList;

		State::Context										_context;
		std::map<StateID, std::function<State::Ptr()>>      _factories;

	};


	template < typename T>
	void StateStack::registerState(StateID stateID)
	{
		_factories[stateID] = [this]()
		{
			return State::Ptr(new T(*this, _context));
		};
	}


}

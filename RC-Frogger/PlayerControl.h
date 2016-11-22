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
#pragma once
#include "SFML/Graphics.hpp"
#include "Command.h"
#include "CommandQueue.h"
#include <map>

namespace GEX {

	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		SpinLeft,
		SpinRight,
		FireBullet,
		LaunchMissile
	};

	enum class missionStatus
	{
		Active,
		Success,
		Failure
	};

	class PlayerControl
	{
	public:
		PlayerControl();

		void handleEvent(const sf::Event & events, CommandQueue & commands);

		void	setMissionStatus(missionStatus status);
		missionStatus getMissionStatus() const;


		void handleRealTimeInput(CommandQueue& command);					// pushes commands
	
	private:
		void	initalizeKeyBindings();				// sets the key bindings
		void	initalizaActionBindings();			// sets the action bindings
		bool	isRealTimeAction(Action action);	// returns true based on action	


	private:
		std::map<sf::Keyboard::Key, Action>		_keyBindings;
		std::map<Action, Command>				_actionBindings;
		missionStatus							_missionStatus;
	};
}

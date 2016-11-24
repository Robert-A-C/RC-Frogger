/**
@file    PlayerControl.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the PlayerControl class

*/
#include "PlayerControl.h"
#include "Airplane.h"
#include "Category.h"
#include "Frog.h"

namespace GEX
{
	struct AirplaneMover	// moves the airplane
	{
		AirplaneMover(float vx, float vy) : velocity(vx, vy) {}
		void operator()(Airplane& airplane, sf::Time) const
		{
			airplane.accelerate(velocity);
		}
		sf::Vector2f velocity;
	};

	struct FrogMover
	{
		FrogMover(float vx, float vy) : movement(vx, vy) {}
		void operator()(Frog& frog, sf::Time) const
		{
			frog.setPosition(frog.getPosition() + movement);
		}
		sf::Vector2f movement;
	};

	struct AirplaneSpinner	// spins airplanes
	{
		AirplaneSpinner(float r) : rotation(r) {}
		void operator()(Airplane& Airplane, sf::Time) const {
			Airplane.setRotation(Airplane.getRotation() + rotation);
		}
		float rotation;
	};



	PlayerControl::PlayerControl() :
		_missionStatus(missionStatus::Active)
	{
		// set initial key bindings
		initalizeKeyBindings();

		// set action bindings
		initalizaActionBindings();
	}

	void PlayerControl::handleEvent(const sf::Event& events, CommandQueue& commands)
	{
		if (events.type == sf::Event::KeyPressed)
		{
			auto found = _keyBindings.find(events.key.code);
			if (found != _keyBindings.end() && !isRealTimeAction(found->second))
			{
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::setMissionStatus(missionStatus status)
	{
		_missionStatus = status;
	}

	missionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}

	void PlayerControl::initalizaActionBindings()		// sets the action bindings
	{

		_actionBindings[Action::MoveLeft].action = derivedAction<Frog>(FrogMover(-40.f, 0.f));
		_actionBindings[Action::MoveRight].action = derivedAction<Frog>(FrogMover(+40.f, 0.f));
		_actionBindings[Action::MoveUp].action = derivedAction<Frog>(FrogMover(0.f, -40.f));
		_actionBindings[Action::MoveDown].action = derivedAction<Frog>(FrogMover(0.f, +40.f));

		/*const float playerSpeed = 200.f;
		_actionBindings[Action::MoveLeft].action = derivedAction<Airplane>(AirplaneMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action = derivedAction<Airplane>(AirplaneMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action = derivedAction<Airplane>(AirplaneMover(0.f, -playerSpeed));
		_actionBindings[Action::MoveDown].action = derivedAction<Airplane>(AirplaneMover(0.f, playerSpeed));*/
		
		/*_actionBindings[Action::FireBullet].action = derivedAction<Airplane>([](Airplane& a, sf::Time dt) {a.fire(); });
		_actionBindings[Action::LaunchMissile].action = derivedAction<Airplane>([](Airplane& a, sf::Time dt) {a.launchMissile(); });*/

		for (auto& pair : _actionBindings)
			pair.second.category = Category::Player;
		
		//const float rotationSpeed = 0.25f;
		////_actionBindings[Action::SpinLeft].action = derivedAction<Airplane>(AirplaneSpinner(-rotationSpeed));
		//_actionBindings[Action::SpinLeft].action = derivedAction<Airplane>([](Airplane& node, sf::Time dt) {node.accelerateAngularVelocity(-0.25f); });
		//_actionBindings[Action::SpinRight].action = derivedAction<Airplane>(AirplaneSpinner(rotationSpeed));


		//_actionBindings[Action::SpinLeft].category = Category::AlliedAircraft;
		//_actionBindings[Action::SpinRight].category = Category::AlliedAircraft;


	}

	void PlayerControl::initalizeKeyBindings()		// sets the key bindings
	{
		_keyBindings[sf::Keyboard::Q] = Action::SpinLeft;
		_keyBindings[sf::Keyboard::E] = Action::SpinRight;
		_keyBindings[sf::Keyboard::Left] = Action::MoveLeft;
		_keyBindings[sf::Keyboard::Right] = Action::MoveRight;
		_keyBindings[sf::Keyboard::Up] = Action::MoveUp;
		_keyBindings[sf::Keyboard::Down] = Action::MoveDown;
		_keyBindings[sf::Keyboard::Space] = Action::FireBullet;
		_keyBindings[sf::Keyboard::M] = Action::LaunchMissile;
	}

	

	void PlayerControl::handleRealTimeInput(CommandQueue& commands)		// pushes commands  
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
	}

	bool PlayerControl::isRealTimeAction(Action action)		// returns true based on action
	{
		/*switch (action)
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
		case Action::SpinLeft:
		case Action::SpinRight:
			return true;
		default:*/			
			return false;
		//}
	}
}

/**
@file    Category.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the Category class

*/

#pragma once

namespace GEX {
	namespace Category {

		enum Type
		{
			None = 0,
			SceneAirLayer =		1 << 0,
			Player =			1 << 1,
			AlliedAircraft =	1 << 2,
			EnemyAircraft =		1 << 3,
			Pickup =			1 << 4,
			Turtle =			1 << 5,
			Car =				1 << 6,
			Log =				 1 << 7,
			SoundEffect =		1 << 8,
			

			Airplane = Player | AlliedAircraft | EnemyAircraft,
			Projectile = Turtle, 
			
			PlayerCollidesWith = Pickup | EnemyAircraft,
			EnemyCollidesWith = Player | AlliedAircraft | Turtle

		};
	}
}


/**
@file    ResourceIdentifiers.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the ResourceIdentifiers class

*/
#pragma once


namespace GEX
{
	enum class FontID {
		Main

	};


	enum class TextureID {
		Eagle,
		Raptor,
		Avenger,
		Jungle,
		FinishLine,
		Airplane,
		Missile,
		TitleScreen,
		MenuScreen,
		GexScreen,
		Bullet,
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		Particle,
		Atlas,
		Explosion

	};

	enum class SoundEffectID {
		AlliedGunfire,
		EnemyGunfire,
		Explosion1,
		Explosion2,
		LaunchMissile,
		CollectPickup,
		Button
	};
}


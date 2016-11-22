/**
@file    StateIdentifiers.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the PlayerControl class

*/
#pragma once

enum class StateID
{
	None,
	Title,
	Menu,
	Game,
	Loading,
	Pause,
	Gex,
	GameOver
};


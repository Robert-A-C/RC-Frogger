/**
@file    Particle.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the Particle class

*/
#pragma once
#include <SFML/Graphics.hpp>


namespace GEX {
	
	struct Particle {
		enum class Type {
			Propellant,
			Smoke
		};

		sf::Vector2f position;
		sf::Color	color;
		sf::Time	lifetime;
	};
}

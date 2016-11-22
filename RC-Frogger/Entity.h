/**
@file    Entity.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the Entity class

*/
#pragma once
#include "SceneNode.h"

namespace GEX {
	class Entity :
		public SceneNode
		

	{
	public:
						Entity(int hitpoints = 20);				// defaults hitpoints to 20

		void			setVelocity(sf::Vector2f velocity);		// sets velocity
		void			setVelocity(float vx, float vy);		// sets velocity with floats

		float			getAngularVelocity() const;				// gets rotate velocity
		void			setAngularVelocity(float av);			// sets rotate velocity
		void			accelerateAngularVelocity(float r);		// increments rotate velocity
		void			accelerate(sf::Vector2f velocity);		// increments velocity
		void			accelerate(float vx, float vy);			// increments velocity with floats	
		sf::Vector2f	getVelocity() const;					// gets velocity

		int getHitpoints() const;		// returns hitpoints
		void repair(int points);		// increments hitpoints by passed in value
		void damage(int points);		// decrements hitpoints by passed in value
		void destroy();					// sets hitpoints to 0
		bool isDestroyed() const override;
		


	protected:
		void			updateCurrent(sf::Time dt, CommandQueue& command) override;			// updates entity

	private:
		
		sf::Vector2f	_velocity;
		float			_angularVelocity;
		int				_hitpoints;
	};
}

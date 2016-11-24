/**
@file    World.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the World class

*/
#pragma once
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include <array>
#include <vector>
#include "CommandQueue.h"
#include "Airplane.h"
#include "SoundPlayer.h"
#include "Frog.h"

namespace GEX 
{
	
	class Airplane;
	
	class World
	{
	private:
		struct SpawnPoint
		{
			SpawnPoint(Airplane::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y)
			{}

			Airplane::Type	type;
			float			x;
			float			y;
		};

	public:
		explicit	World(sf::RenderWindow& window, SoundPlayer& soundPlayer);

		void update(sf::Time);	// updates everything
		void guideMissiles();
		void draw();			// draws the window
		
		CommandQueue&		getCommandQueue();

		bool hasAlivePlayer() const;
		bool hasReachedFinish() const;

		

	private:
		
		void			buildScene();						// builds the scene
		sf::FloatRect	getViewBounds() const;				// gets view bounds
		sf::FloatRect	getBattleFieldBounds() const;		// gets battlefield bounds

		void	spawnEnemies();												// spawns enemies
		void	addEnemies();												//
		void	addEnemy(Airplane::Type type, float relX, float relY);		//
		void	addEnemy(SpawnPoint point);									//

		void			updateSounds();

		void handleCollisions();
		void destroyEntitiesOutsideView();


	private:
		enum Layer
		{
			
			Background,
			FinishLine,
			Air,
			LayerCount			
		};

		

	private:
		sf::RenderWindow&						_window;
		sf::View								_worldView;
		sf::FloatRect							_worldBounds;
		
		SceneNode								_sceneGraph;
		std::array<SceneNode*, LayerCount>		_sceneLayers;
		CommandQueue							_commandQueue;
		SoundPlayer&							_soundPlayer;
		
		sf::Vector2f							_spawnPosition;
		float									_scrollSpeed;
		Airplane*								_playerAirplane;
		Frog*									_playerFrog;
		std::vector<SpawnPoint>					_enemieSpawnPoints;
		std::vector<Airplane*>					_activeEnemies;
	};
}
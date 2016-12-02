/**
@file    World.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the World class

*/
#include "World.h"
#include "Airplane.h"
#include "Pickup.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include <algorithm>
#include "SoundNode.h"
#include "ParticleNode.h"
#include "Frog.h"

namespace GEX {

	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_worldView(window.getDefaultView()),
		_soundPlayer(soundPlayer),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(-300.f, 0.f, _worldView.getSize().x + 600.f, _worldView.getSize().y),
		_spawnPosition((_worldView.getSize().x / 2.f), (_worldBounds.height - 20.f)),
		_scrollSpeed(0.0f),
		_playerAirplane(nullptr)
	{


		buildScene();

		// start the view at the spawn
		//_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time dt)		// updates everything
	{
		


		

		while (!_commandQueue.isEmpty())
			_sceneGraph.onCommand(_commandQueue.pop(), dt);

		//handleCollisions();

		//_sceneGraph.removeWrecks();
		//spawnEnemies();
		spawnCars();
		spawnLogs();
		spawnTurtles();
		//apply  movements 
		_sceneGraph.update(dt, getCommandQueue());
		// stay in bounds
		adaptPlayerPostition();
	}

	void World::guideMissiles()
	{
		// set up command to get a list of all enemy planes
		Command enemyCollector;
		enemyCollector.category = Category::EnemyAircraft;
		enemyCollector.action = derivedAction<Airplane>([this](Airplane& enemy, sf::Time dt)
		{
			if (!enemy.isDestroyed())
				this->_activeEnemies.push_back(&enemy);
		});

		Command missileGuider;
		missileGuider.category = Category::AlliedProjectile;
		missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt)
		{
			if (!missile.isGuided())
				return;

			float minDistance = std::numeric_limits<float>::max();
			Airplane* closestEnemy = nullptr;

			for (Airplane* enemy : this->_activeEnemies)
			{
				float enemyDistance = distance(missile, *enemy);

				if (enemyDistance < minDistance)
				{
					closestEnemy = enemy;
					minDistance = enemyDistance;
				}
			}
			if (closestEnemy)
			{
				missile.guideTowards(closestEnemy->getWorldPosition());

			}
		});
		// clear enemy list
		_activeEnemies.clear();

		// push commands
		_commandQueue.push(enemyCollector);
		_commandQueue.push(missileGuider);

	}



	void World::draw()				// draws the window
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);
	}

	CommandQueue & World::getCommandQueue()		// returns command queue
	{
		return _commandQueue;
	}

	bool World::hasAlivePlayer() const
	{
		//return !_playerAirplane->isMarkedForRemoval();
		return true;
	}

	bool World::hasReachedFinish() const
	{
		//return !_worldBounds.contains(_playerAirplane->getPosition());
		return false;
	}

	sf::FloatRect World::getViewBounds() const	// gets view bounds
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}
	
	sf::FloatRect World::getBattleFieldBounds() const		// gets battlefield bounds 
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.width -= 1000;
		bounds.height += 100;
		return bounds;
	}

	void World::adaptPlayerPostition()
	{
		// Keep player's position inside the screen bounds, 
		// at least borderDistance units from the border

		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 20.f;

		sf::Vector2f position = _playerFrog->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerFrog->setPosition(position);
	}

	void World::spawnEnemies()	// spawns enemies
	{
		while (!_enemieSpawnPoints.empty() && _enemieSpawnPoints.back().y > getBattleFieldBounds().top)
		{
			auto spawn = _enemieSpawnPoints.back();
			std::unique_ptr<Airplane> enemy(new Airplane(spawn.type));
			enemy->setPosition(spawn.x, spawn.y);
			enemy->setRotation(180.f);
			_sceneLayers[Air]->attachChild(std::move(enemy));
			_enemieSpawnPoints.pop_back();
		}
	}

	void World::addEnemies()		// adds the enemies at certain points
	{
		addEnemy(Airplane::Type::RAPTOR, -250.f, 200.f);
		addEnemy(Airplane::Type::RAPTOR, 250.f, 200.f);
		addEnemy(Airplane::Type::RAPTOR, -350.f, 400.f);
		addEnemy(Airplane::Type::RAPTOR, 350.f, 400.f);
		
		addEnemy(Airplane::Type::RAPTOR, -250.f, 800.f);
		addEnemy(Airplane::Type::RAPTOR, 250.f, 800.f);
		addEnemy(Airplane::Type::RAPTOR, -350.f, 1000.f);
		addEnemy(Airplane::Type::RAPTOR, 350.f, 1000.f);
		
		std::sort(_enemieSpawnPoints.begin(), _enemieSpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {return lhs.y < rhs.y; });
		
	}

	void World::addEnemy(Airplane::Type type, float relX, float relY)	// spawn enemy function
	{
		addEnemy(SpawnPoint(type, relX, relY));
	}
		
	void World::addEnemy(SpawnPoint point)		// spawn enemy to spawn points 
	{
		point.x = _spawnPosition.x + point.x;
		point.y = _spawnPosition.y - point.y;
		_enemieSpawnPoints.push_back(point);
	}

	

	void World::updateSounds()
	{
		_soundPlayer.setListenerPosition(_playerAirplane->getWorldPosition());

		_soundPlayer.removeStoppedSounds();
	}

	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();
	
		if (type1 & category1 && type2 & category2)
		{
			return true;
		}
		else if (type1 & category2 && type2 & category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
		{
			return false;
		}
	
	
	}

	void World::handleCollisions()
	{
		std::set<SceneNode::Pair> collisionPairs;
		_sceneGraph.checkSceneNodeCollision(_sceneGraph, collisionPairs);

		for (SceneNode::Pair pair : collisionPairs)
		{
			if (matchesCategories(pair, Category::Player, Category::EnemyAircraft))
			{
				auto& player = static_cast<Airplane&>(*pair.first);
				auto& enemy = static_cast<Airplane&>(*pair.second);

				player.damage(enemy.getHitpoints());
				enemy.destroy();
			}

			if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile) || (matchesCategories(pair, Category::Player, Category::Car)))
			{
				auto& enemyPlane = static_cast<Airplane&>(*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

				enemyPlane.damage(projectile.getHitpoints());
				projectile.destroy();
			}

			if (matchesCategories(pair, Category::Player, Category::Car))
			{
				auto& player = static_cast<Airplane&>(*pair.first);
				auto& enemyProjectile = static_cast<Projectile&>(*pair.second);

				player.damage(enemyProjectile.getHitpoints());
				enemyProjectile.destroy();
			}

			if (matchesCategories(pair, Category::Player, Category::Pickup))
			{
				auto& player = static_cast<Airplane&>(*pair.first);
				auto& pickup = static_cast<Pickup&>(*pair.second);

				pickup.apply(player);
				pickup.destroy();
				player.playLocalSound(_commandQueue, SoundEffectID::CollectPickup);
			}

		}
	}
	void World::destroyEntitiesOutsideView()
	{
		/*Command command;
		command.category = Category::Car;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattleFieldBounds().intersects(e.getBoundingRect()))
				e.setPosition();
		});

		_commandQueue.push(command);*/
	}

	

	void World::spawnCars()
	{
		while (!_carSpawnpoints.empty())
		{
			auto spawn = _carSpawnpoints.back();
			std::unique_ptr<Cars> Car(new Cars(spawn.type));
			Car->setPosition(spawn.x, spawn.y);
			
			_sceneLayers[Air]->attachChild(std::move(Car));
			_carSpawnpoints.pop_back();
		}
	}

	void World::addCars()
	{
		addCar(Cars::Type::RaceCar1, 350.f, _worldView.getSize().y - 60.f);
		addCar(Cars::Type::RaceCar1, 250.f, _worldView.getSize().y - 60.f);
		addCar(Cars::Type::RaceCar1, 450.f, _worldView.getSize().y - 60.f);

		addCar(Cars::Type::Trackter2, 150.f, _worldView.getSize().y - 100.f);
		addCar(Cars::Type::Trackter2, 250.f, _worldView.getSize().y - 100.f);
		addCar(Cars::Type::Trackter2, 350.f, _worldView.getSize().y - 100.f);

		addCar(Cars::Type::SUV3, 250.f, _worldView.getSize().y - 140.f);
		addCar(Cars::Type::SUV3, 350.f, _worldView.getSize().y - 140.f);
		addCar(Cars::Type::SUV3, 450.f, _worldView.getSize().y - 140.f);

		addCar(Cars::Type::RaceCar4, 50.f, _worldView.getSize().y - 180.f);
		addCar(Cars::Type::RaceCar4, 150.f, _worldView.getSize().y - 180.f);
		addCar(Cars::Type::RaceCar4, 250.f, _worldView.getSize().y - 180.f);

		addCar(Cars::Type::Truck5, 200.f, _worldView.getSize().y - 220.f);
		addCar(Cars::Type::Truck5, 300.f, _worldView.getSize().y - 220.f);
		addCar(Cars::Type::Truck5, 400.f, _worldView.getSize().y - 220.f);

		std::sort(_carSpawnpoints.begin(), _carSpawnpoints.end(), [](CarSpawn lhs, CarSpawn rhs) {return lhs.y < rhs.y; });
	}

	void World::addCar(Cars::Type type, float x, float y)
	{
		addCar(CarSpawn(type, x, y));
	}

	void World::addCar(CarSpawn point)
	{
		_carSpawnpoints.push_back(point);
	}

	void World::spawnLogs()
	{
		while (!_logSpawnPoints.empty())
		{
			auto spawn = _logSpawnPoints.back();
			std::unique_ptr<Logs> Log(new Logs(spawn.type));
			Log->setPosition(spawn.x, spawn.y);

			_sceneLayers[Air]->attachChild(std::move(Log));
			_logSpawnPoints.pop_back();
		}
	}

	void World::addLogs()
	{
		addLog(Logs::Type::Log2, 450.f, _worldView.getSize().y - 360.f);
		addLog(Logs::Type::Log2, 250.f, _worldView.getSize().y - 360.f);
		addLog(Logs::Type::Log2, 50.f, _worldView.getSize().y - 360.f);

		addLog(Logs::Type::Log3, 450.f, _worldView.getSize().y - 440.f);
		addLog(Logs::Type::Log3, 250.f, _worldView.getSize().y - 440.f);
		addLog(Logs::Type::Log3, 50.f, _worldView.getSize().y - 440.f);

		std::sort(_logSpawnPoints.begin(), _logSpawnPoints.end(), [](LogSpawn lhs, LogSpawn rhs) {return lhs.y < rhs.y; });
	}

	void World::addLog(Logs::Type type, float x, float y)
	{
		addLog(LogSpawn(type, x, y));
	}

	void World::addLog(LogSpawn point)
	{
		_logSpawnPoints.push_back(point);
	}

	void World::spawnTurtles()
	{
		while (!_turtleSpawnPoints.empty())
		{
			auto spawn = _turtleSpawnPoints.back();
			std::unique_ptr<Turtles> Turtle(new Turtles(spawn.type));
			Turtle->setPosition(spawn.x, spawn.y);

			_sceneLayers[Air]->attachChild(std::move(Turtle));
			_turtleSpawnPoints.pop_back();
		}
	}

	void World::addTurtles()
	{
		addTurtle(Turtles::Type::Turtles2, 450.f, _worldView.getSize().y - 400.f);
		addTurtle(Turtles::Type::Turtles2, 150.f, _worldView.getSize().y - 400.f);

		addTurtle(Turtles::Type::Turtles3, 450.f, _worldView.getSize().y - 480.f);
		addTurtle(Turtles::Type::Turtles3, 450.f, _worldView.getSize().y - 480.f);

		addTurtle(Turtles::Type::Turtles2, 450.f, _worldView.getSize().y - 320.f);
		addTurtle(Turtles::Type::Turtles2, 450.f, _worldView.getSize().y - 320.f);

		std::sort(_turtleSpawnPoints.begin(), _turtleSpawnPoints.end(), [](TurtleSpawn lhs, TurtleSpawn rhs) {return lhs.y < rhs.y; });
	}

	void World::addTurtle(Turtles::Type type, float x, float y)
	{
		addTurtle(TurtleSpawn(type, x, y));
	}

	void World::addTurtle(TurtleSpawn point)
	{
		_turtleSpawnPoints.push_back(point);
	}

	void World::resetCars()
	{
		Command command;
		command.category = Category::Car;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
		
			
			if (!getBattleFieldBounds().intersects(e.getBoundingRect()))
				e.destroy();
		});

		_commandQueue.push(command);
	}

	void World::buildScene()		// builds the scene
	{
		// build layer nodes for scene graph
		for (std::size_t i = 0; i < LayerCount; ++i)
		{
			Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attachChild(std::move(layer));
		}

		// add soundNode
		std::unique_ptr<SoundNode> soundEffectsNode(new SoundNode(_soundPlayer));
		_sceneGraph.attachChild(std::move(soundEffectsNode));


		//prepare tiled background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(0,0, 480, 600);
		texture.setRepeated(false);

		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		background->setPosition(_worldView.getViewport().left, _worldView.getViewport().top);
		_sceneLayers[Background]->attachChild(std::move(background));

		//add finishLine
		/*sf::Texture& finish = TextureHolder::getInstance().get(TextureID::FinishLine);
		sf::IntRect FinishRect(0,0,1024,76);
		std::unique_ptr<SpriteNode> finishLine(new SpriteNode(finish, FinishRect));
		_sceneLayers[FinishLine]->attachChild(std::move(finishLine));*/

		// particle system smoke
		/*std::unique_ptr<ParticleNode>smokeNode(new ParticleNode(Particle::Type::Smoke));
		_sceneLayers[Air]->attachChild(std::move(smokeNode));*/

		// particle system fire
		/*std::unique_ptr<ParticleNode>fireNode(new ParticleNode(Particle::Type::Propellant));
		_sceneLayers[Air]->attachChild(std::move(fireNode));*/

		// add planes
		/*std::unique_ptr<Airplane> plane(new Airplane(Airplane::Type::EAGLE));
		plane->setPosition(_spawnPosition);
		plane->setVelocity(40.f, _scrollSpeed);
		_playerAirplane = plane.get();
		_sceneLayers[Air]->attachChild(std::move(plane));*/

		std::unique_ptr<Frog> frog(new Frog(Frog::Type::Frogger));
		frog->setPosition(_spawnPosition);
		_playerFrog = frog.get();
		_sceneLayers[Air]->attachChild(std::move(frog));


		addCars();
		addLogs();
		addTurtles();
		//addEnemies();

		
	}

}
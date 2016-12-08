/**
@file    SceneNode.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the SceneNode class

*/
#pragma once
#include "SFML/Graphics.hpp"
#include <cassert>
#include <vector>
#include <memory>
#include "Command.h"
#include "Category.h"
#include "CommandQueue.h"
#include <set>


namespace GEX {
	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
		typedef std::pair<SceneNode*, SceneNode*> Pair;

	public:
		SceneNode(Category::Type type = Category::None);
		
		
		//non-copyable
		SceneNode(const SceneNode&) = delete;
		SceneNode& operator=(const SceneNode&) = delete;

		void								attachChild(Ptr);						// attachs Children
		Ptr									detachChild(const SceneNode& node);		// detachs Children
		
		void								onCommand(const Command& command, sf::Time dt);		
		virtual unsigned int				getCategory() const;								// gets Category

		sf::Vector2f						getWorldPosition() const;		// gets world position
		sf::Transform						getWorldTransform() const;		// gets transform
		virtual	sf::FloatRect				getBoundingRect() const;		// gets bounding rect
		

		void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
		void checkSceneNodeCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);

		void removeWrecks();
		
		virtual bool isMarkedForRemoval() const;
		virtual bool isDestroyed() const;

		void								update(sf::Time dt, CommandQueue& command);		// updates everything
	
	private:
		
		virtual void						updateCurrent(sf::Time dt, CommandQueue& command);		// does nothing by default
		void								updateChildren(sf::Time dt, CommandQueue& command);		// updates children

		void								draw(sf::RenderTarget& target, sf::RenderStates state) const override final;	// calls all the draw functions
		virtual void						drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;			// does nothing by default
		void								drawChildren(sf::RenderTarget& target, sf::RenderStates state) const;			// draws children
		void								drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;		// draws collision rectangle
		
	private:
		SceneNode*							_parent;
		std::vector<Ptr>					_children;
		Category::Type						_defaultCategory;
	};

	float		distance(const SceneNode& lhs, const SceneNode& rhs);
	bool		collision(const SceneNode& lhs, const SceneNode& rhs);
}


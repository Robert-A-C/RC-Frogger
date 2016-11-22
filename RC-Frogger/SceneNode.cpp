/**
@file    SceneNode.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the SceneNode class

*/
#include "SceneNode.h"
#include "Category.h"
#include "Utility.h"


namespace GEX {

	float distance(const SceneNode& lhs, const SceneNode& rhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}

	bool collision(const SceneNode & lhs, const SceneNode & rhs)
	{
		return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}

	SceneNode::SceneNode(Category::Type cat) :
	_parent(nullptr),
	_defaultCategory(cat)
	{}
	

	void SceneNode::attachChild(Ptr child) // attachs children
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}
	
	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) // detachs children
	{
		auto found = std::find_if(_children.begin(), _children.end(), [&](Ptr& p)->bool {return p.get() == &node; });

		assert(found == _children.end()); // crash if not found

		Ptr result = std::move(*found);
		result->_parent = nullptr;
		_children.erase(found);
		return result;
	}

	void SceneNode::onCommand(const Command & command, sf::Time dt)	
	{
		if(command.category & getCategory())
			command.action(*this, dt);

		for (auto& child : _children)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const	// gets category
	{
		return _defaultCategory;
	}

	sf::Vector2f SceneNode::getWorldPosition() const	// gets world position
	{
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const	// gets transform
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
		{
			transform = node->getTransform() * transform;
		}
		return transform;
	}

	sf::FloatRect SceneNode::getBoundingRect() const	// gets bounding rect
	{
		return sf::FloatRect();
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed()) { collisionPairs.insert(std::minmax(this, &node)); }
		for (auto& child : _children)
			child->checkNodeCollision(node, collisionPairs);
	}

	void SceneNode::checkSceneNodeCollision(SceneNode & node, std::set<Pair>& collisionPairs)
	{
		this->checkNodeCollision(node, collisionPairs);

		for (auto& child : node._children)
			this->checkSceneNodeCollision(*child, collisionPairs);
	}

	void SceneNode::removeWrecks()
	{
		auto wreckFieldBegin = std::remove_if(_children.begin(), _children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));

		_children.erase(wreckFieldBegin, _children.end());

		std::for_each(_children.begin(), _children.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	
	
	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates state) const	// calls all the draw funtions
	{
		// apply transform
		state.transform *= getTransform();

		// draw current, then draw children
		drawCurrent(target, state);
		drawBoundingRect(target, state);
		drawChildren(target, state);

		
	}

	void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const //do nothing by default
	{
		

	}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates state) const	// draws children
	{
		for (const Ptr& child : _children)
		{
			child->draw(target,state);
		}
	}

	void SceneNode::drawBoundingRect(sf::RenderTarget & target, sf::RenderStates states) const	// Draws the rectangle for collision detection
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);

		target.draw(shape);
	}
	
	void SceneNode::update(sf::Time dt, CommandQueue& command)		// updates everything
	{
		// update current then all children with changed transform
		updateCurrent(dt, command);
		updateChildren(dt, command);
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& command)
	{

	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& command) // updates all the children
	{
		for (const Ptr& child : _children)
		{
			child->update(dt, command);
		}
	}
	
}
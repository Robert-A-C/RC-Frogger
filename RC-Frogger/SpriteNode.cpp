/**
@file    SpriteNode.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the SpriteNode class

*/
#include "SpriteNode.h"

namespace GEX {

	SpriteNode::SpriteNode( sf::Texture& texture):	
		_sprite(texture)
	{}


	SpriteNode::SpriteNode( sf::Texture& texture, sf::IntRect textRect):	
		_sprite(texture, textRect)
	{}

	void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const // draws current sprite
	{
		target.draw(_sprite, states);
	}
}
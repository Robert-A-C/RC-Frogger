/**
@file    SpriteNode.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the SpriteNode class

*/
#pragma once
#include "SceneNode.h"
namespace GEX {
	class SpriteNode : public SceneNode
	{
	public:
		SpriteNode (sf::Texture&);
		SpriteNode(sf::Texture&, sf::IntRect);

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;		// draws sprite

	private:
		sf::Sprite _sprite;
		
	};
}


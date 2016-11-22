/**
@file    TextNode.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the TextNode class

*/
#pragma once

#include "SceneNode.h"
#include <string>

namespace GEX {
	class TextNode : public SceneNode
	{
	
	public:
		explicit TextNode(const std::string& text);
		void setText(const std::string& text);		// sets the text

	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; // draws the text

	private:
		sf::Text _text;
	};
}

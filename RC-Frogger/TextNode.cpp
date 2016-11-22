/**
@file    TextNode.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the TextNode class

*/
#include "TextNode.h"
#include "FontHolder.h"
#include "Utility.h"


namespace GEX {
	TextNode::TextNode(const std::string& text) :
		_text(text, FontHolder::getInstance().get(FontID::Main), 20)	
	{
		centerOrigin(_text);
	}

	void TextNode::setText(const std::string & text)	// sets the text
	{
		_text.setString(text);
		centerOrigin(_text);
	}

	

	void TextNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const	// draws the text
	{
		target.draw(_text, states);
	}

	
}
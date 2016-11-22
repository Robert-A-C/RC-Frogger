/**
@file    TextureHolder.cpp
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Declaration for the TextureHolder class

*/
#include "TextureHolder.h"
#include <iostream>
#include <cassert>
#include <memory>

namespace GEX {
	TextureHolder* TextureHolder::_instance = nullptr;
	TextureHolder::TextureHolder()
	{

	}

	TextureHolder & TextureHolder::getInstance()	// gets instance
	{
		if (!TextureHolder::_instance) // lazy instantiation only constructs when called for
			TextureHolder::_instance = new TextureHolder();

		return *TextureHolder::_instance;
	}

	void TextureHolder::load(TextureID id, const std::string & path)	// loads textures
	{
		std::unique_ptr<sf::Texture> texture(new sf::Texture);

		if (!texture->loadFromFile(path))
		{
			std::cout << "load failed!" << std::endl;
			assert(0);
		}
		auto rc = _textures.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0);
	}

	sf::Texture& GEX::TextureHolder::get(TextureID tID)
	{

		auto found = _textures.find(tID);
		assert(found != _textures.end());

		return *found->second;
	}
}
/**
@file    TextureHolder.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the TextureHolder class

*/
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "ResourceIdentifiers.h"

namespace GEX
{
	

	class TextureHolder
	{
	public:
		static TextureHolder& getInstance();			// gets instance



		void load(TextureID id, const std::string& path);	// loads texture
		sf::Texture& get(TextureID);						// gets texture


	private:
		TextureHolder();
		static TextureHolder* _instance;

		std::map<TextureID, std::unique_ptr<sf::Texture>> _textures;
	};
}
/**
@file    ParticleNode.h
@author  Robert Carll Robert-a-c@live.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Definition for the ParticleNode class

*/
#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"
#include "Entity.h"
#include "Particle.h"
#include <deque>

namespace GEX {
	class ParticleNode : public SceneNode
	{
	public:
		explicit						ParticleNode(Particle::Type tyoe);
		
		void							addParticle(sf::Vector2f position);
		Particle::Type					getParticleType() const;
		unsigned int					getCategory() const override;

	private:

		void							updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void							drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

		void							addVertex(float worldx, float worldy, float texu, float texv, const sf::Color& color) const;
		void							computeVerticies() const;

	private:
		std::deque<Particle>			_particles;
		const sf::Texture&				_texture;
		Particle::Type					_type;

		mutable sf::VertexArray			_vertexArray;
		mutable bool					_needsVertexUpdate;

	};
}


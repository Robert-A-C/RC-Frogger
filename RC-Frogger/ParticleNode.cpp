#include "ParticleNode.h"
#include "TextureHolder.h"
#include "ResourceIdentifiers.h"
#include "DataTables.h"

namespace GEX {
	namespace {   // anonymous namespace
		const std::map<Particle::Type, ParticleData> table = initalizeParticleData();
	}
	
	
	ParticleNode::ParticleNode(Particle::Type type) : 
		SceneNode(),
		_particles(),
		_texture(TextureHolder::getInstance().get(TextureID::Particle)),
		_type(type),
		_vertexArray(sf::Quads),
		_needsVertexUpdate(true)
	{

	}
	

	void GEX::ParticleNode::addParticle(sf::Vector2f position)
	{
		Particle particle;
		particle.position = position;
		particle.color = table.at(_type).color;
		particle.lifetime = table.at(_type).lifetime;
		_particles.push_back(particle);
	}

	Particle::Type GEX::ParticleNode::getParticleType() const
	{
		return _type;
	}

	unsigned int GEX::ParticleNode::getCategory() const
	{
		return Category::ParticleSystem;
	}

	void GEX::ParticleNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		//Remove Expired particles
		while (!_particles.empty() && _particles.front().lifetime <= sf::Time::Zero)
			_particles.pop_front();

		//Update
		for (auto& particle : _particles)
			particle.lifetime -= dt;

		// mark particles as dirty
		_needsVertexUpdate = true;

	}

	void GEX::ParticleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (_needsVertexUpdate)
		{
			computeVerticies();
			_needsVertexUpdate = false;		
		}
		states.texture = &_texture;
		target.draw(_vertexArray, states);
	}

	void ParticleNode::addVertex(float worldx, float worldy, float texu, float texv, const sf::Color & color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(worldx, worldy);
		vertex.texCoords = sf::Vector2f(texu, texv);
		vertex.color = color;

		_vertexArray.append(vertex);

	}

	void ParticleNode::computeVerticies() const
	{
		sf::Vector2f size(_texture.getSize());
		sf::Vector2f half = size / 2.f;

		_vertexArray.clear();
		for (const Particle& particle : _particles)
		{
			sf::Vector2f pos = particle.position;
			sf::Color color = particle.color;
			
			float ratio = particle.lifetime.asSeconds() / table.at(_type).lifetime.asSeconds();

			color.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

			//add 4 vertices to make up a rectangle primative for particle
			addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
			addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);

		}
	}
}
#pragma once
#include "SceneNode.h"
#include "Particle.h"
#include "ParticleNode.h"

namespace GEX {
	class Emitters : public SceneNode
	{
	public:
		explicit Emitters(Particle::Type type);
		
	private:
		void updateCurrent(sf::Time dt, CommandQueue& commands) override;

		void emitParticles(sf::Time dt);

	private:
		sf::Time		_accumulatedTime;
		Particle::Type	_type;
		ParticleNode*   _particleSystem;
	};
}

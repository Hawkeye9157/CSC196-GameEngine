#include "Particle.h"

void Particle::update(float dt)
{
	if (lifespan != 0) {
		lifespan -= dt;
	}
	position = position + (velocity * dt);
}

void Particle::draw(Renderer& renderer)
{
	if (lifespan >= 0) {
		renderer.DrawPoint(position.x, position.y);
	}
}

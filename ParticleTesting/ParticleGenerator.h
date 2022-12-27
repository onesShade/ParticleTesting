#pragma once
#include <list>
#include "Particle.h"
#include <SFML/Graphics.hpp>

class ParticleGenerator : public sf::Drawable
{
public:
	std::list<Particle*> particles;
	ParticleGenerator(int x, int y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float dt);
	int X;
	int Y;
	Particle Partical;
};



#include "Particle.h"

Particle::Particle(ParticleArgs args)
{
	startColor = args.start_color;
	endColor = args.end_color;
	size = args.size;
	lifespan = args.lifespan;
	currentTime = 0;
	dead = false;
	Speed = args.speed;
	rect.setFillColor(startColor);
	rect.setSize({ (float)size, (float)size });
	rect.setOrigin({ size / 2.f, size / 2.f });
	rect.setPosition(args.x, args.y);

}
Particle::Particle()
{

}
void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect);
}
void Particle::Update(float dt)
{
	currentTime += dt;
	if (currentTime >= lifespan)
		dead = true;

	rect.setFillColor(sf::Color::Color(
		(endColor.r - startColor.r) * currentTime / lifespan + startColor.r,
		(endColor.g - startColor.g) * currentTime / lifespan + startColor.g,
		(endColor.b - startColor.b) * currentTime / lifespan + startColor.b,
		(endColor.a - startColor.a) * currentTime / lifespan + startColor.a
		));
	rect.move(Speed * dt);

}

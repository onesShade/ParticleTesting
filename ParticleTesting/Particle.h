#pragma once
#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable
{
public:
	struct ParticleArgs
	{
		float lifespan;
		int x;
		int y;
		int size;
		sf::Color start_color;
		sf::Color end_color;
		sf::Vector2f speed;
	};

	Particle(ParticleArgs args);
	Particle();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(float dt);
	sf::Color startColor;
	sf::Color endColor;
	int size;
	float currentTime;
	float lifespan;
	sf::RectangleShape rect;
	bool dead;

private:
	sf::Vector2f Speed;

};

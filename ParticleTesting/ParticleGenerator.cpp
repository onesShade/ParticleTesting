#include "ParticleGenerator.h"


ParticleGenerator::ParticleGenerator(int x, int y)
{
	X = x;
	Y = y;
}
void ParticleGenerator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Particle *d : particles)
    {
        if (d != NULL)
            target.draw(*d);
    }
}
static sf::Vector2f Normalize(sf::Vector2f& vec)
{
    float len = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
    return { vec.x / len, vec.y / len };
}

void ParticleGenerator::Update(float dt)
{
    Particle::ParticleArgs args;
    args.lifespan = 1;
    args.start_color = sf::Color(0x1100FFFF);
    args.end_color = sf::Color(0xFF00FF00);
    args.size = 5;
    args.x = X;
    args.y = Y;
    args.speed = sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50);
    args.speed = Normalize(args.speed) * 60.f;


    Particle* par = new Particle(args);
    particles.push_back(par);

   std::list<Particle*>::iterator i = particles.begin();
   while (i != particles.end())
   {
       (*i)->Update(dt);
       if ((*i)->dead)
       {
            delete(*i);
            i = particles.erase(i);
       }          
       else
           i++;
   }
}
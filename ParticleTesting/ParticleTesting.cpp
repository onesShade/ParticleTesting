#include "ParticleGenerator.h"
#include <SFML/Graphics.hpp>
#include "FpsCounter.h"
#include "vector"
#include "list"
#include "Particle.h"
#include <iostream>
#include <random>
#include <string>

void Update(float);
void UpdateParticles(float);
void UpdateGenerators(float);
static sf::Vector2f Normalize(sf::Vector2f&);

static FpsCounter fpsCounter;

static std::list<Particle*> particlesDrawList;
static std::list<ParticleGenerator*> particlesGeneratorList;

sf::RenderWindow window(sf::VideoMode(1280, 720), "Particles");

int main()
{
    sf::Clock clock;

    float delta_time = 0;
    srand(time(NULL));

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                for (ParticleGenerator *d : particlesGeneratorList)
                {
                    for (Particle *b : d->particles)
                    {
                        delete(b);
                    }
                    d->particles.clear();
                    delete(d);
                }
                particlesGeneratorList.clear();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2i absoute_mouse_position = sf::Mouse::getPosition(window);
                sf::Vector2f relative_mouse_position = window.mapPixelToCoords(absoute_mouse_position);
                
                std::cout << "\npresed " << particlesGeneratorList.size();

                ParticleGenerator* temp = new ParticleGenerator(relative_mouse_position.x, relative_mouse_position.y );
                particlesGeneratorList.push_back(temp);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                sf::Vector2i absoute_mouse_position = sf::Mouse::getPosition(window);
                sf::Vector2f relative_mouse_position = window.mapPixelToCoords(absoute_mouse_position);

                std::cout << "\npresed " << particlesGeneratorList.size();
                if (particlesGeneratorList.size() > 0)
                    std::cout << " " << particlesGeneratorList.front()->particles.size();

                ParticleGenerator* temp = new ParticleGenerator(relative_mouse_position.x, relative_mouse_position.y);
                particlesGeneratorList.push_back(temp);
            }
        }

        delta_time = clock.restart().asSeconds();


        Update(delta_time);

        window.clear(sf::Color::White);

        for (Particle *d : particlesDrawList)
        {
            if(d != NULL)
                window.draw(*d);
        }

        for (ParticleGenerator *d : particlesGeneratorList)
        {
            window.draw(*d);
        }

        window.draw(fpsCounter);
        window.display();
    }

    

    return 0;
}

void Update(float delta_time)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        sf::Vector2i absoute_mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f relative_mouse_position = window.mapPixelToCoords(absoute_mouse_position);
        Particle::ParticleArgs args;
        args.lifespan = 1;
        args.start_color = sf::Color(0x1100FFFF);
        args.end_color = sf::Color(0xFF00FF00);
        args.size = 5;
        args.x = relative_mouse_position.x;
        args.y = relative_mouse_position.y;
        args.speed = sf::Vector2f( rand() % 100 - 50, rand() % 100 - 50 );
        args.speed = Normalize(args.speed) * 60.f;

        Particle* par = new Particle(args);
        particlesDrawList.push_back(par);

    }
    UpdateGenerators(delta_time);
    UpdateParticles(delta_time);


    fpsCounter.Update(delta_time);
    fpsCounter.externalInfo.clear();
    fpsCounter.externalInfo.push_back("Partical Generators : " +std::to_string(particlesGeneratorList.size()));

    int particlseCount = particlesDrawList.size();
    for (ParticleGenerator* d : particlesGeneratorList)
    {
        particlseCount += d->particles.size();
    }

    fpsCounter.externalInfo.push_back("Total particles: " + std::to_string(particlseCount));
}
void UpdateGenerators(float delta_time) 
{
    std::list<ParticleGenerator*>::iterator i = particlesGeneratorList.begin();
    while (i != particlesGeneratorList.end())
    {
        (*i)->Update(delta_time);
        i++;
    }
}
void UpdateParticles(float delta_time)
{
    std::list<Particle*>::iterator i = particlesDrawList.begin();
    while (i != particlesDrawList.end())
    {
        (*i)->Update(delta_time);
        if ((*i)->dead)
        {
            delete(*i);
            i = particlesDrawList.erase(i);
        }
        else
            i++;
    }
}

static sf::Vector2f Normalize(sf::Vector2f& vec)
{
    float len = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
    return { vec.x / len, vec.y / len };
}
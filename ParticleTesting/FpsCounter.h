#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <queue>

class FpsCounter : public sf::Drawable
{
public:
	std::vector<std::string> externalInfo;
	std::queue<int> fpsQueue;

	const int size = 16;
	const int averageSize = 5;

	FpsCounter() 
	{
		second_dt = 0;
		full_dt = 0;
		fps = 0;

		if (!main_font.loadFromFile("./Resourses/Retro Gaming.ttf"))
			throw("font not loaded");

		for (int i = 0; i < averageSize; i++)
		{
			fpsQueue.push(0);
		}
	}
	
	void Update(float dt)
	{
		second_dt += dt;
		full_dt += dt;

		frames_for_second++;

		if (second_dt >= 1.f)
		{
			fps = frames_for_second;
			total_frames += frames_for_second;

			fpsQueue.push(frames_for_second);

			total_frames -= fpsQueue.front();
			fpsQueue.pop();

			average_fps = float(total_frames) / averageSize;

			frames_for_second = 0;
			second_dt -= 1;



		}


	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sf::RectangleShape background(sf::Vector2f(size * 24, size * (2 + externalInfo.size())));
		background.setFillColor(sf::Color(0x22222222));
		target.draw(background, states);

		sf::Text text;
		text.setFont(main_font);
		text.setFillColor(sf::Color::Blue);
		text.setCharacterSize(size);


		text.setString("fps : " + std::to_string(fps));
		target.draw(text, states);


		text.setPosition(0, size);
		text.setString("average fps : " + std::to_string(average_fps));
		target.draw(text, states);

		for (int i = 0; i < externalInfo.size(); i++)
		{
			text.setString(std::to_string(i + 1) + "." + externalInfo[i]);
			text.setPosition(0,  (2 + i) * size);
			target.draw(text, states);
		}


	}

private:

	sf::Font main_font;

	float second_dt;
	float full_dt;
	int frames_for_second;
	int fps;
	int total_frames;
	int average_fps;
};


#include "GameCycle.h"

GameCycle::GameCycle()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 720), "MyDoom");

	Frame frame = Frame();

	window->setFramerateLimit(60);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		frame.next();
		window->draw(frame);

		window->display();
	}
}

